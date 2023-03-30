/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:24:29 by danpark           #+#    #+#             */
/*   Updated: 2023/03/30 21:31:10 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	creat_here_doc_fd(t_list *rds)
{
	int		fds[2];
	t_rd	*rd;
	pid_t	pid;

	while (rds)
	{
		rd = (t_rd *)rds->content;
		if (rd->type == HRDC)
		{
			if (pipe(fds) == -1)
				exit(1);
			pid = fork();
			if (handle_here_doc_process(pid, fds, rd) == FAIL)
				return (-1);
		}
		rds = rds->next;
	}
	return (0);
}

int	handle_here_doc_process(pid_t pid, int *fds, t_rd *rd)
{
	char	*input;
	int		stat;
	char	sig_code;

	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		input = get_here_doc_input(rd);
		write(fds[1], input, ft_strlen(input));
		close(fds[1]);
		close(fds[0]);
		free(input);
		exit(0);
	}
	close(fds[1]);
	rd->read = fds[0];
	wait(&stat);
	sig_code = (char)stat;
	if (sig_code != 0)
	{
		printf("\n");
		return (-1);
	}
	return (0);
}

char	*get_here_doc_input(t_rd *rd)
{
	char	*input;
	char	*rd_line;
	size_t	rd_len;
	size_t	lmt_len;

	input = ft_strdup("");
	lmt_len = ft_strlen(rd->file);
	while (1)
	{
		write(1, "> ", 3);
		rd_line = get_next_line(0);
		if (!rd_line)
			break ;
		rd_len = ft_strlen(rd_line) - 1;
		if (lmt_len == rd_len && ft_strncmp(rd->file, rd_line, rd_len) == 0)
			break ;
		input = ft_substrjoin(input, rd_line, 0, ft_strlen(rd_line));
		free(rd_line);
	}
	return (input);
}

void	close_here_doc_fd(t_list *rds)
{
	t_rd	*rd;

	while (rds)
	{
		rd = (t_rd *)rds->content;
		if (rd->type == HRDC && rd->read > 0)
			close(rd->read);
		rds = rds->next;
	}
}
