/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:46:21 by danpark           #+#    #+#             */
/*   Updated: 2023/03/08 18:48:21 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_echo(char **cmd)
{
	int	option;

	option = 0;
	(*cmd)++;
	if (ft_strlen(*cmd) == ft_strlen("-n") && \
	ft_strncmp("-n", *cmd, ft_strlen(*cmd)) == 0)
	{
		(*cmd)++;
		option = 1;
	}
	while (*cmd)
	{
		printf("%s", (*cmd)++);
		if (*cmd)
			printf(" ");
		else if (!option)
			printf("\n");
	}
	exit(1);
}

void	execute_echo(char **cmd)
{
	int	option;

	option = 0;
	cmd++;
	if (!*cmd)
	{
		printf("\n");
		exit(0);
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
	exit(0);
}