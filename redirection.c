/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:24:00 by danpark           #+#    #+#             */
/*   Updated: 2023/03/30 19:34:13 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_input_fd(t_rd *rd)
{
	int	file;

	file = 0;
	if (rd->type == IN)
	{
		if (is_vaild_file(rd->file) == FALSE)
			return (-1);
		file = open(rd->file, O_RDONLY);
		if (file == -1)
			return (put_error_message(1, 0));
		dup2(file, STDIN_FILENO);
		close(file);
	}
	else if (rd->type == HRDC)
	{
		dup2(rd->read, STDIN_FILENO);
		close(rd->read);
	}
	return (0);
}

int	set_output_fd(t_rd *rd)
{
	int	file;

	file = 0;
	if (rd->type == OUT)
		file = open(rd->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (rd->type == APND)
		file = open(rd->file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (file == -1)
		return (put_error_message(1, 0));
	dup2(file, STDOUT_FILENO);
	close(file);
	return (0);
}

int	redirection(t_list *rds)
{
	t_rd	*rd;
	int		file;

	file = 0;
	while (rds)
	{
		rd = (t_rd *)rds->content;
		if (rd->type == IN || rd->type == HRDC)
		{
			if (set_input_fd(rd) < 0)
				return (-1);
		}
		else
		{
			if (set_output_fd(rd) < 0)
				return (-1);
		}
		rds = rds->next;
	}
	return (0);
}
