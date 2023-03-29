/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 20:06:41 by danpark           #+#    #+#             */
/*   Updated: 2023/03/30 05:38:32 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_echo(char **cmd)
{
	int	option;

	option = 0;
	cmd++;
	if (!*cmd)
	{
		printf("\n");
		return ;
	}
	if (ft_strlen(*cmd) == ft_strlen("-n") && \
	ft_strncmp("-n", *cmd, ft_strlen(*cmd)) == 0)
	{
		cmd++;
		option = 1;
	}
	while (*cmd)
	{
		printf("%s", *cmd);
		cmd++;
		if (*cmd)
			printf(" ");
		else if (!option)
			printf("\n");
	}
}

void	execute_cd(char **cmd, t_list *e_lst)
{
	t_list	*old_pwd;
	t_list	*pwd;
	char	*path;
	char	*tmp;

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
	if (!chdir(path))
	{
		pwd = get_env_node("PWD", e_lst);
		old_pwd = get_env_node("OLDPWD", e_lst);
		if (old_pwd)
		{
			free(old_pwd->next->content);
			old_pwd->next->content = ft_strjoin("OLDPWD=", get_env(e_lst, "PWD"));
		}
		if (pwd)
		{
			free(pwd->next->content);
			tmp = getcwd(NULL, 0);
			pwd->next->content = ft_strjoin("PWD=", tmp);
			free(tmp);
		}
	}
	else
		put_error_message(1, *cmd);
}

void	execute_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
		printf("%s\n", pwd);
	free(pwd);
}

void	execute_exit(t_token *token)
{
	t_list	*rd;
	t_list	*txt;
	char	*exitcode;
	int		i;

	rd = token->rd;
	txt = token->txt;
	if (!txt->next)
		exit(0);
	exitcode = (char *)txt->next->content;
	i = -1;
	if (exitcode[0] == '+' && exitcode[0] == '-' && exitcode[1])
		i++;
	while (exitcode[++i])
		if (!ft_isdigit(exitcode[i]))
		{
			g_exit_code = 255;
			printf("exit: %s: numeric argument required\n", exitcode);
			exit((int)g_exit_code);
		}
	if (txt->next->next)
	{
		g_exit_code = 1;
		printf("exit: too many arguments\n");
	}
	else
	{
		g_exit_code = (unsigned char)ft_atoi(exitcode);
		exit((int)g_exit_code);
	}
}
