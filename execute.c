/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:54:09 by danpark           #+#    #+#             */
/*   Updated: 2023/04/03 00:10:07 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	interpret_token(t_list *tokens, t_list *e_lst)
{
	pid_t	pid;
	int		fds[2][2];
	t_token	*token;

	token = (t_token *)tokens->content;
	if (creat_here_doc_fd(token->rd, 0) == FAIL)
		return (close_here_doc_fd(token->rd));
	if (token->txt && ft_lstsize(tokens) == 1 && is_builtin(token->txt))
		parent_execute_command(token, e_lst);
	else
	{
		if (pipe(fds[0]) == -1)
			exit(1);
		pid = fork();
		if (pid == -1)
			exit(1);
		else if (pid != 0)
		{
			close_here_doc_fd(token->rd);
			parent_do(tokens, fds, e_lst);
		}
		else
			execute_command(tokens, fds, 1, e_lst);
	}
}

void	parent_do(t_list *tokens, int (*fds)[2], t_list *e_lst)
{
	t_token	*token;
	t_list	*tmp;
	int		cnt;

	close(fds[0][1]);
	tmp = tokens;
	tokens = tokens->next;
	cnt = 0;
	while (tokens)
	{
		if (pipe(fds[1]) == -1)
			exit(1);
		token = (t_token *)tokens->content;
		if (creat_here_doc_fd(token->rd, ++cnt) == FAIL)
			return (close_here_doc_fd(token->rd));
		creat_exe_process(tokens, fds, e_lst);
		close_here_doc_fd(token->rd);
		tokens = tokens->next;
	}
	close(fds[0][0]);
	set_child_exit_status(tmp);
}

void	creat_exe_process(t_list *tokens, int (*fds)[2], t_list *e_lst)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(1);
	else if (pid == 0)
		execute_command(tokens, fds, 0, e_lst);
	dup2(fds[1][0], fds[0][0]);
	close(fds[1][0]);
	close(fds[1][1]);
}

void	execute_command(t_list *tokens, int (*fds)[2], int first, t_list *e_lst)
{
	t_token	*token;
	char	**envp;
	char	**cmd;
	char	*path;

	token = (t_token *)tokens->content;
	signal(SIGINT, SIG_DFL);
	change_stream(tokens, fds, first);
	cmd = list_to_array(token->txt);
	if (cmd == NULL)
		exit(0);
	envp = list_to_array(e_lst);
	path = find_bin(cmd[0], envp);
	set_input_mode(CHILD);
	signal(SIGQUIT, SIG_DFL);
	if (is_builtin(token->txt))
	{
		execute_builtin_command(token, e_lst);
		exit(g_exit_code);
	}
	else if (execve(path, cmd, envp))
		handle_execute_fail(e_lst, cmd[0]);
}

void	change_stream(t_list *tokens, int (*fds)[2], int first)
{
	t_token	*token;

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
	if (redirection(token->rd) == -1)
		exit(g_exit_code);
}
