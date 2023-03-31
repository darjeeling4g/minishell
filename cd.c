/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:31:06 by danpark           #+#    #+#             */
/*   Updated: 2023/03/31 18:27:26 by danpark          ###   ########.fr       */
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
		path = ft_strdup(*cmd);
	set_pwd(e_lst, path, cmd);
	free (path);
}

void	set_pwd(t_list *e_lst, char *path, char **cmd)
{
	t_list	*old_pwd;
	t_list	*pwd;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (!chdir(path))
	{
		pwd = get_env_node("PWD", e_lst);
		old_pwd = get_env_node("OLDPWD", e_lst);
		if (old_pwd)
			change_old_pwd(old_pwd, tmp);
		free(tmp);
		if (pwd)
			change_pwd(pwd);
		g_exit_code = 0;
	}
	else
	{
		free(tmp);
		put_error_message(1, *cmd);
	}
}

void	change_old_pwd(t_list *old_pwd, char *tmp)
{
	free(old_pwd->next->content);
	old_pwd->next->content = ft_strjoin("OLDPWD=", tmp);
}

void	change_pwd(t_list *pwd)
{
	char	*tmp;

	free(pwd->next->content);
	tmp = getcwd(NULL, 0);
	pwd->next->content = ft_strjoin("PWD=", tmp);
	free(tmp);
}
