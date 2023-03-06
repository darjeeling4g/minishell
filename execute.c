/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:54:09 by danpark           #+#    #+#             */
/*   Updated: 2023/03/06 19:51:57 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	interpret_token(t_list *tokens)
{
	pid_t	pid;
	int		fds[2][2];

	if (pipe(fds[0]) == -1)
		put_error_message(errno);
	pid = fork();
	if (pid == -1)
		put_error_message(errno);
	else if (pid != 0)
		parent_do(tokens, pid, fds);
	else
		execute_first_command(tokens);
}

void	parent_do(t_list *tokens, pid_t pid, int *fds[])
{
	int	i;
	int	stat;
	t_list	*tmp;

	close(fds[0][1]);
	tmp = tokens;
	while (tokens)
	{
		if (pipe(fds[1]) == -1)
			put_error_message(errno);
		pid = fork();
		if (pid == -1)
			put_error_message(errno);
		else if (pid == 0 && !tokens->next)
			execute_last_command(exc, i);
		else if (pid == 0)
			execute_mid_command(exc, i);
		dup2(fds[1][0], fds[0][0]);
		close(fds[0][0]);
		close(fds[1][1]);
		tokens = tokens->next;
	}
	i = -1;
	while (++i < exc->num_cmd)
		wait(&stat);
	unlink("/tmp/here_doc");
}

void	execute_first_command(t_token *token, int (*fds)[2])
{
	int	fd;
	t_rd	*rd;
	char	*str;

	close(fds[0][0]);
	rd = (t_rd *)token->rd->content;
	if (rd->type == IN && access(rd->file, F_OK))
		put_error_message(errno);
	if (exc->here_doc)
		fd = open("/tmp/here_doc", O_RDONLY);
	else
		fd = open(exc->fls[0], O_RDONLY);
	if (fd == -1)
		put_error_message("Failed to open a file");
	dup2(fd, 0);
	dup2(exc->fds1[1], 1);
	close(exc->fds1[1]);
	close(fd);
	if (execve(exc->cmds[exc->here_doc][0], exc->cmds[exc->here_doc], \
	exc->ev) == -1)
	{
		dup2(2, 1);
		ft_printf("pipex: command not found: %s\n", exc->cmds[exc->here_doc][0]);
		exit(1);
	}
}

void	redirection(t_list *rds, int (*fds)[2])
{
	t_rd	*rd;
	int		file;

	while (rds)
	{
		rd = (t_rd *)rds->content;
		if (rd->type == IN)
		{
			if (!access(rd->file, F_OK))
				put_error_message(errno);
			file = open(rd->file, O_RDONLY);
			if (!file)
				put_error_message(errno);
			dup2(file, STDIN_FILENO);
			close(file);
		}
		else if (rd->type == HRDC)
			
		rds = rds->next;
	}	
}

void	get_here_doc_input(t_exc *exc)
{
	char	*input;
	size_t	str_len;
	size_t	input_len;
	char	*str;
	int		fd;

	str = exc->cmds[0][0];
	str_len = ft_strlen(str);
	fd = open("/tmp/here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		put_error_message("Failed to open a file");
	while (1)
	{
		input = get_next_line(0);
		if (!input)
			break ;
		input_len = ft_strlen(input) - 1;
		if (str_len == input_len && ft_strncmp(str, input, input_len) == 0)
			break ;
		write(fd, input, input_len + 1);
		free(input);
	}
	close(fd);
	free(input);
}