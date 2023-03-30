/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:55:01 by danpark           #+#    #+#             */
/*   Updated: 2023/03/30 19:03:10 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_exit(t_token *token)
{
	t_list	*txt;
	char	*exitcode;

	txt = token->txt;
	if (!txt->next)
	{
		g_exit_code = 0;
		exit(0);
	}
	exitcode = (char *)txt->next->content;
	check_exit_error(exitcode, txt);
	if (txt->next->next == NULL)
	{
		g_exit_code = (unsigned char)ft_atoi(exitcode);
		exit((int)g_exit_code);
	}
}

void	check_exit_error(char *exitcode, t_list *txt)
{
	int	i;

	i = -1;
	if (exitcode[0] == '+' && exitcode[0] == '-' && exitcode[1])
		i++;
	while (exitcode[++i])
	{
		if (!ft_isdigit(exitcode[i]))
		{
			g_exit_code = 255;
			printf("exit: %s: numeric argument required\n", exitcode);
			exit((int)g_exit_code);
		}
	}
	if (txt->next->next)
	{
		g_exit_code = 1;
		printf("exit: too many arguments\n");
	}
}
