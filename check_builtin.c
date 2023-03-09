/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:24:32 by danpark           #+#    #+#             */
/*   Updated: 2023/03/09 23:44:41 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_list *cmdlst)
{
	size_t	cmdlen;
	char	*cmd;

	cmd = (char *)cmdlst->content;
	cmdlen = ft_strlen(cmd);
	if ((ft_strlen("echo") == cmdlen && !ft_strncmp("echo", cmd, cmdlen)) || \
	(ft_strlen("cd") == cmdlen && !ft_strncmp("cd", cmd, cmdlen)) || \
	(ft_strlen("export") == cmdlen && !ft_strncmp("export", cmd, cmdlen)) || \
	(ft_strlen("unset") == cmdlen && !ft_strncmp("unset", cmd, cmdlen)) || \
	(ft_strlen("env") == cmdlen && !ft_strncmp("env", cmd, cmdlen)) || \
	(ft_strlen("exit") == cmdlen && !ft_strncmp("exit", cmd, cmdlen)))
		return (1);
	return (0);
}

void	execute_builtin_command(t_token *token, t_list *e_lst)
{
	char	**cmd;
	int		cmdlen;

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
}

int	is_valid_cmd(char *cmd)
{
	int		res;

	res = 1;
	if (!ft_isalpha(*(cmd++)))
		res = 0;
	while (cmd)
	{
		if (!ft_isalnum(*cmd))
			res = 0;
		cmd++;
	}
	return (res);
}