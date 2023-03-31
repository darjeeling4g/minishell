/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 22:38:46 by danpark           #+#    #+#             */
/*   Updated: 2023/03/31 22:40:41 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_a_directory(char *path)
{
	struct stat	sb;

	stat(path, &sb);
	if ((sb.st_mode & S_IFMT) == S_IFDIR)
	{
		put_customized_error_message(126, path, "is a directory");
		return (TRUE);
	}
	return (FALSE);
}

void	handle_execute_fail(t_list *e_lst, char *cmd)
{
	if (is_a_directory(cmd) == FALSE)
	{
		if (get_env_node("PATH", e_lst))
			put_customized_error_message(127, cmd, "command not found");
		else
		{
			if (errno == 13)
				put_error_message(126, cmd);
			else
				put_error_message(127, cmd);
		}
	}
	exit(g_exit_code);
}
