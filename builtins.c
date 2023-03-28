/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 20:06:41 by danpark           #+#    #+#             */
/*   Updated: 2023/03/29 02:14:45 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_echo(char **cmd)
{
	int	option;

	option = 0;
	cmd++;
	if (!*cmd)
	{
		printf("\n");
		return(0);
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
	return(0);
}

int	execute_cd(char **cmd, t_list *e_lst)
{
	cmd++;
	if (!(*cmd) || !ft_strncmp("~", *cmd, ft_strlen(*cmd)))
		return (chdir(get_env(e_lst, "HOME")));
	return (chdir(*cmd));
}

int	execute_pwd(t_list *e_lst)
{
	char	*pwd;

	pwd = get_env(e_lst, "PWD");
	if (pwd != NULL)
		printf("%s\n", pwd);
	else
		return (-1);
	exit(0);
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
