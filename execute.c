/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:54:09 by danpark           #+#    #+#             */
/*   Updated: 2023/03/28 14:38:51by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void interpret_token(t_list *tokens, t_list *e_lst, struct termios *termattr)
{
	pid_t pid;
	int fds[2][2];
	t_token *token;

	token = (t_token *)tokens->content;
	if (token->txt && ft_lstsize(tokens) == 1 && is_builtin(token->txt))
		execute_builtin_command(token, e_lst, PARENT);
	else
	{
		if (pipe(fds[0]) == -1)
			exit(1);
		pid = fork();
		if (pid == -1)
			exit(1);
		else if (pid != 0)
			parent_do(tokens, pid, fds, e_lst, termattr);
		else
			execute_command(tokens, fds, 1, e_lst, termattr);
	}
}

void parent_do(t_list *tokens, pid_t pid, int (*fds)[2], t_list *e_lst, struct termios *termattr)
{
	int stat;
	t_list *tmp;

	close(fds[0][1]);
	tmp = tokens;
	tokens = tokens->next;
	while (tokens)
	{
		if (pipe(fds[1]) == -1)
			exit(1);
		pid = fork();
		if (pid == -1)
			exit(1);
		else if (pid == 0)
			execute_command(tokens, fds, 0, e_lst, termattr);
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
	g_exit_code = (char)(stat >> 8);
}

void execute_command(t_list *tokens, int (*fds)[2], int first, t_list *e_lst, struct termios *termattr)
{
	t_token *token;
	char **envp;
	char **cmd;
	char *path;
	int std[2];

	token = (t_token *)tokens->content;
	std[0] = dup(STDIN_FILENO);
	std[1] = dup(STDOUT_FILENO);
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
	if (redirection(token->rd, std) == -1)
		exit(g_exit_code);
	cmd = list_to_array(token->txt);
	if (cmd == NULL)
		exit(0);
	envp = list_to_array(e_lst);
	path = find_bin(cmd[0], envp);
	reset_input_mode(termattr);
	if (execve(path, cmd, envp))
	{
		put_customized_error_message(127, cmd[0], "command not found");
		exit(g_exit_code);
	}
}
