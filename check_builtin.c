/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:24:32 by danpark           #+#    #+#             */
/*   Updated: 2023/03/24 22:01:01 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(t_list *cmdlst)
{
	size_t cmdlen;
	char *cmd;

	cmd = (char *)cmdlst->content;
	cmdlen = ft_strlen(cmd);
	if ((ft_strlen("echo") == cmdlen && !ft_strncmp("echo", cmd, cmdlen)) ||
		(ft_strlen("cd") == cmdlen && !ft_strncmp("cd", cmd, cmdlen)) ||
		(ft_strlen("export") == cmdlen && !ft_strncmp("export", cmd, cmdlen)) ||
		(ft_strlen("unset") == cmdlen && !ft_strncmp("unset", cmd, cmdlen)) ||
		(ft_strlen("env") == cmdlen && !ft_strncmp("env", cmd, cmdlen)) ||
		(ft_strlen("exit") == cmdlen && !ft_strncmp("exit", cmd, cmdlen)))
		return (1);
	return (0);
}

void execute_builtin_command(t_token *token, t_list *e_lst)
{
	char	**cmd;
	int		cmdlen;
	int		org_fd[2];

	org_fd[0] = dup(STDIN_FILENO);
	org_fd[1] = dup(STDOUT_FILENO);
	redirection(token->rd);
	cmd = list_to_array(token->txt);
	cmdlen = ft_strlen(*cmd);
	if (ft_strncmp("echo", *cmd, cmdlen) == 0)
		execute_echo(cmd);
	else if (ft_strncmp("cd", *cmd, cmdlen) == 0)
		execute_cd(cmd, e_lst);
	else if (ft_strncmp("export", *cmd, cmdlen) == 0)
		execute_export(cmd, e_lst);
	else if (ft_strncmp("unset", *cmd, cmdlen) == 0)
		execute_unset(cmd, e_lst);
	else if (ft_strncmp("env", *cmd, cmdlen) == 0)
		execute_env(e_lst);
	else
		execute_exit();
	dup2(org_fd[0], STDIN_FILENO);
	dup2(org_fd[1], STDOUT_FILENO);
	close(org_fd[0]);
	close(org_fd[1]);
}

int is_valid_name(char *name)
{
	int res;

	res = 1;
	if (!ft_isalpha(*name))
		res = 0;
	name++;
	while (*name)
	{
		if (!ft_isalnum(*name))
			res = 0;
		name++;
	}
	return (res);
}
