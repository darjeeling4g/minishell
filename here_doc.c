/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:24:29 by danpark           #+#    #+#             */
/*   Updated: 2023/03/30 15:25:49 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	creat_here_doc_pipe(t_list *rds)
{
	char	*input;
	int		fds[2];
	t_rd	*rd;

	while (rds)
	{
		rd = (t_rd *)rds->content;
		if (rd->type == HRDC)
		{
			if (pipe(fds) == -1)
				exit(1);
			input = get_here_doc_input(rd);
			write(fds[1], input, ft_strlen(input));
			close(fds[1]);
			free(input);
			rd->read = fds[0];
		}
		rds = rds->next;
	}
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

void	close_here_doc_pipe(t_list *rds)
{
	t_rd	*rd;

	while (rds)
	{
		rd = (t_rd *)rds->content;
		if (rd->type == HRDC)
			close(rd->read);
		rds = rds->next;
	}
}
