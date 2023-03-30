/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:03:46 by danpark           #+#    #+#             */
/*   Updated: 2023/03/30 19:07:11 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_echo(char **cmd)
{
	int	option;

	cmd++;
	option = is_exist_option(cmd);
	while (*cmd)
	{
		printf("%s", *cmd);
		cmd++;
		if (*cmd)
			printf(" ");
	}
	if (option == FALSE)
		printf("\n");
	g_exit_code = 0;
}

int	is_exist_option(char **cmd)
{
	if (*cmd == NULL)
		return (FALSE);
	else if (ft_strlen(*cmd) == ft_strlen("-n") && \
	ft_strncmp("-n", *cmd, ft_strlen(*cmd)) == 0)
	{
		cmd++;
		return (TRUE);
	}
	return (FALSE);
}
