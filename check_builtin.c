/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:24:32 by danpark           #+#    #+#             */
/*   Updated: 2023/03/30 23:05:40 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_list *cmdlst)
{
	size_t	cmdlen;
	char	*cmd;

	cmd = (char *)cmdlst->content;
	cmdlen = ft_strlen(cmd);
	if ((ft_strlen("echo") == cmdlen && !ft_strncmp("echo", cmd, cmdlen))
		|| (ft_strlen("cd") == cmdlen && !ft_strncmp("cd", cmd, cmdlen))
		|| (ft_strlen("pwd") == cmdlen && !ft_strncmp("pwd", cmd, cmdlen))
		|| (ft_strlen("export") == cmdlen && !ft_strncmp("export", cmd, cmdlen))
		|| (ft_strlen("unset") == cmdlen && !ft_strncmp("unset", cmd, cmdlen))
		|| (ft_strlen("env") == cmdlen && !ft_strncmp("env", cmd, cmdlen))
		|| (ft_strlen("exit") == cmdlen && !ft_strncmp("exit", cmd, cmdlen)))
		return (1);
	return (0);
}

void	parent_execute_command(t_token *token, t_list *e_lst)
{
	int		std[2];

	std[0] = dup(STDIN_FILENO);
	std[1] = dup(STDOUT_FILENO);
	execute_builtin_command(token, e_lst);
	dup2(std[0], STDIN_FILENO);
	dup2(std[1], STDOUT_FILENO);
	close(std[0]);
	close(std[1]);
}

void	execute_builtin_command(t_token *token, t_list *e_lst)
{
	char	**cmd;
	int		cmdlen;

	if (redirection(token->rd) == SUCCESS)
	{
		cmd = list_to_array(token->txt);
		cmdlen = ft_strlen(*cmd);
		if (ft_strncmp("echo", *cmd, cmdlen) == 0)
			execute_echo(cmd);
		else if (ft_strncmp("cd", *cmd, cmdlen) == 0)
			execute_cd(cmd, e_lst);
		else if (ft_strncmp("pwd", *cmd, cmdlen) == 0)
			execute_pwd();
		else if (ft_strncmp("export", *cmd, cmdlen) == 0)
			execute_export(cmd, e_lst);
		else if (ft_strncmp("unset", *cmd, cmdlen) == 0)
			execute_unset(cmd, e_lst);
		else if (ft_strncmp("env", *cmd, cmdlen) == 0)
			execute_env(e_lst);
		else
			execute_exit(token);
		free_array(cmd, -1);
	}
}

int	is_valid_name(char *name)
{
	int	res;

	res = 1;
	if ((ft_isalpha(*name) || *name == '_') == FALSE)
		res = 0;
	name++;
	while (*name)
	{
		if ((ft_isalnum(*name) || *name == '_') == FALSE)
			res = 0;
		name++;
	}
	return (res);
}
