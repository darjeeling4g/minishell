/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:54:09 by danpark           #+#    #+#             */
/*   Updated: 2023/03/24 20:03:38 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	interpret_token(t_list *tokens, t_list *e_lst)
{
	pid_t	pid;
	int		fds[2][2];
	t_token	*token;

	token = (t_token *)tokens->content;
	if (token->txt && ft_lstsize(tokens) == 1 && is_builtin(token->txt))
		execute_builtin_command(token, e_lst);
	else
	{
		if (pipe(fds[0]) == -1)
			put_error_message(EXIT);
		pid = fork();
		if (pid == -1)
			put_error_message(EXIT);
		else if (pid != 0)
			parent_do(tokens, pid, fds, e_lst);
		else
			execute_command(tokens, fds, 1, e_lst);
	}
}

void	parent_do(t_list *tokens, pid_t pid, int (*fds)[2],  t_list *e_lst)
{
	int		stat;
	t_list	*tmp;

	close(fds[0][1]);
	tmp = tokens;
	tokens = tokens->next;
	while (tokens)
	{
		if (pipe(fds[1]) == -1)
			put_error_message(EXIT);
		pid = fork();
		if (pid == -1)
			put_error_message(EXIT);
		else if (pid == 0)
			execute_command(tokens, fds, 0, e_lst);
		dup2(fds[1][0], fds[0][0]);
		close(fds[1][0]);
		close(fds[1][1]);
		tokens = tokens->next;
	}
	while (tmp)
	{
		wait(&stat);
		tmp = tmp->next;
	}
}

void	execute_command(t_list *tokens, int (*fds)[2], int first, t_list *e_lst)
{
	t_token		*token;
	char		**envp;
	char		**cmd;
	char		*path;
	struct termios term;
	
	
	token = (t_token *)tokens->content;
	if (first)
	{
		if (tokens->next)
			dup2(fds[0][1], 1);
		close(fds[0][1]);
	}
	else
	{
		if (tokens->next)
			dup2(fds[1][1], 1);
		dup2(fds[0][0], 0);
		close(fds[1][0]);
		close(fds[1][1]);
	}
	close(fds[0][0]);
	redirection(token->rd);
	cmd = list_to_array(token->txt);
	if (!cmd)
		exit(0);
	envp = list_to_array(e_lst);
	path = find_bin(cmd[0], envp);
	if (execve(path, cmd, envp))
		put_error_message(EXIT);
}
