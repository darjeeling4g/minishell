/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:08:37 by siyang            #+#    #+#             */
/*   Updated: 2023/03/30 19:06:20 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_unset(char **cmd, t_list *e_lst)
{
	t_list	*env;
	t_list	*tmp;

	cmd++;
	while (*cmd)
	{
		if (!is_valid_name(*cmd))
		{
			put_customized_error_message(1, *cmd, "not a valid identifier");
			return ;
		}
		env = get_env_node(*cmd, e_lst);
		if (env)
		{
			if (ft_strncmp(*cmd, "_", ft_strlen(*cmd)))
			{
				tmp = env->next;
				env->next = env->next->next;
				free(tmp->content);
				free(tmp);
			}
		}
		cmd++;
	}
	g_exit_code = 0;
}

t_list	*get_env_node(char *name, t_list *e_lst)
{
	char	*env;
	size_t	size;

	while (e_lst->next)
	{
		env = (char *)e_lst->next->content;
		size = 0;
		while (env[size] != '=' && env[size] != '\0')
			size++;
		if (size == ft_strlen(name) && !ft_strncmp(name, env, size))
			return (e_lst);
		e_lst = e_lst->next;
	}
	return (NULL);
}
