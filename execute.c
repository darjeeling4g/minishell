/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:54:09 by danpark           #+#    #+#             */
/*   Updated: 2023/03/05 20:17:16 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	interpret_token(t_list *tokens)
{
	t_list	*addr;
	int		fd[2];
	int		pid;
	int		*stat;

	addr = tokens;
	pipe(fd);
	pid = fork();
	while (addr->next)
	{
		if (pid == -1)
		{
			strerror(errno);
			exit(1);
		}
		else if (pid == 0)
		{
			close(fd[1]);
			pipe(fd);
			pid = fork();
		}
		else
		{
			close(fd[0]);
			
		}
		addr = addr->next;
	}
	addr = tokens;
	while (addr)
	{
		wait(stat);
		addr = addr->next;
	}
}

