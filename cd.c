/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:31:06 by danpark           #+#    #+#             */
/*   Updated: 2023/03/30 19:35:34 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cd(char **cmd, t_list *e_lst)
{
	char	*path;

	cmd++;
	if (!(*cmd) || !ft_strncmp("~", *cmd, ft_strlen(*cmd)))
	{
		path = get_env(e_lst, "HOME");
		if (!path)
		{
			put_customized_error_message(1, *(cmd - 1), "HOME not set");
			return ;
		}
	}
	else if (!ft_strncmp("-", *cmd, ft_strlen(*cmd)))
	{
		path = get_env(e_lst, "OLDPWD");
		if (!path)
		{
			put_customized_error_message(1, *(cmd - 1), "OLDPWD not set");
			return ;
		}
	}
	else
		path = *cmd;
	set_pwd(e_lst, path, cmd);
}

void	set_pwd(t_list *e_lst, char *path, char **cmd)
{
	t_list	*old_pwd;
	t_list	*pwd;
	char	*tmp;

	if (!chdir(path))
	{
		pwd = get_env_node("PWD", e_lst);
		old_pwd = get_env_node("OLDPWD", e_lst);
		if (old_pwd)
		{
			free(old_pwd->next->content);
			old_pwd->next->content = ft_strjoin("OLDPWD=", \
			get_env(e_lst, "PWD"));
		}
		if (pwd)
		{
			free(pwd->next->content);
			tmp = getcwd(NULL, 0);
			pwd->next->content = ft_strjoin("PWD=", tmp);
			free(tmp);
		}
		g_exit_code = 0;
	}
	else
		put_error_message(1, *cmd);
}
