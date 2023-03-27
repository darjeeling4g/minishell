/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 20:06:41 by danpark           #+#    #+#             */
/*   Updated: 2023/03/10 00:19:34 by danpark          ###   ########.fr       */
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
	if (!cmd)
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
	if (!rd && !txt->next)
		exit(0);
	exitcode = (char *)txt->next->content;
	i = -1;
	while (exitcode[++i])
	{
		if (!ft_isdigit(exitcode[i]))
			exit(255);
		
	}
	if (rd || txt->next->next)
		exit(255);
	else
		exit((char *)txt->next->content);
}
