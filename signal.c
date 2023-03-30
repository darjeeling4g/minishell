/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 13:45:39 by danpark           #+#    #+#             */
/*   Updated: 2023/03/30 14:55:22 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
	g_exit_code = 1;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	set_child_exit_status(t_list *tokens)
{
	int		stat;
	char	sig_code;

	while (tokens)
	{
		wait(&stat);
		tokens = tokens->next;
	}
	sig_code = (char)stat;
	g_exit_code = (char)(sig_code + 128);
	if (sig_code == 3)
		printf("Quit: %c\n", sig_code + '0');
	else if (sig_code == 2)
		printf("\n");
	if (!sig_code)
		g_exit_code = (char)(stat >> 8);
}
