/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:24:32 by danpark           #+#    #+#             */
/*   Updated: 2023/03/28 16:55:18 by siyang           ###   ########.fr       */
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

void execute_builtin_command(t_token *token, t_list *e_lst, int parent)
{
	char	**cmd;
	int		cmdlen;
	int		std[2];

	std[0] = dup(STDIN_FILENO);
	std[1] = dup(STDOUT_FILENO);
	if (!redirection(token->rd, std))
	{
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
			execute_exit(token);
	}
	dup2(std[0], STDIN_FILENO);
	dup2(std[1], STDOUT_FILENO);
	close(std[0]);
	close(std[1]);
	if (!parent)
		exit((int)g_exit_code);
}
//added checking under bar
int is_valid_name(char *name)
{
	int res;

	res = 1;
	if (!ft_isalpha(*name) || *name != '_')
		res = 0;
	name++;
	while (*name)
	{
		if (!ft_isalnum(*name) || *name != '_')
			res = 0;
		name++;
	}
	return (res);
}
