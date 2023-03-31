/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:03:46 by danpark           #+#    #+#             */
/*   Updated: 2023/03/31 17:33:06 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_echo(char **cmd)
{
	int	cnt;

	cnt = count_exist_option(++cmd);
	cmd += cnt;
	while (*cmd)
	{
		printf("%s", *cmd);
		cmd++;
		if (*cmd)
			printf(" ");
	}
	if (cnt == 0)
		printf("\n");
	g_exit_code = 0;
}

int	count_exist_option(char **cmd)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	if (*cmd != NULL && **cmd == '-')
	{
		while ((*cmd)[++i])
			if ((*cmd)[i] != 'n')
				return (cnt);
		cnt++;
	}
	else
		return (cnt);
	cmd++;
	while (**cmd == '-')
	{
		i = 0;
		while ((*cmd)[++i])
			if ((*cmd)[i] != 'n')
				return (cnt);
		cmd++;
		cnt++;
	}
	return (cnt);
}
