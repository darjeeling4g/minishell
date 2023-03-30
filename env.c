/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:07:00 by siyang            #+#    #+#             */
/*   Updated: 2023/03/30 19:07:24 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_env(t_list *e_lst)
{
	char	*env;

	while (e_lst)
	{
		env = (char *)e_lst->content;
		if (ft_strchr(env, '='))
			printf("%s\n", env);
		e_lst = e_lst->next;
	}
	g_exit_code = 0;
}
