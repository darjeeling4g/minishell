/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 20:10:18 by danpark           #+#    #+#             */
/*   Updated: 2023/03/09 23:04:57 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_env(t_list *e_lst)
{
	char *env;

	while (e_lst)
	{
		env = (char *)e_lst->content;
		if (ft_strchr(env, '=')) 
			printf("%s\n", env);
		e_lst = e_lst->next;
	}
	return (0);
}

int	execute_export(char** cmd, t_list *e_lst)
{
	t_list	*new;
	t_list	*tmp;
	char	**str;

	cmd++;
	if (*cmd)
		print_sorted_envp(e_lst);
	else
	{
		while (cmd)
		{
			str = ft_split(*cmd, '=');
			if (!is_valid_cmd(str[0]))
			{
				free_array(str, -1);
				return (-1);
			}
			new = ft_lstnew(*cmd);
			if (!new)
				return (-1);
			tmp = get_env_node(str[0], e_lst);
			free_array(str, -1);
			if (tmp)
			{
				new->next = tmp->next->next;
				free(tmp->next);
				tmp->next = new;
			}
			else
				ft_lstadd_back(&e_lst, new);
			cmd++;
		}
	}
	return (0);
}

int	execute_unset(char **cmd, t_list *e_lst)
{
	t_list	*env;
	t_list	*tmp;

	cmd++;
	while (*cmd)
	{
		if (!is_valid_cmd(*cmd))
			return (-1);
		env = get_env_node(*cmd, e_lst);
		if (env)
		{
			tmp = env->next;
			env->next = env->next->next;
			free(tmp);
		}
		cmd++;
	}
	return (0);
}

void	print_sorted_envp(t_list *e_lst)
{
	char	**arr;
	char	*tmp;
	int		i;
	int		j;

	arr = list_to_array(e_lst);
	i = -1;
    while (arr[++i])
	{
		j = i + 1;
        while (arr[j++]) 
		{
            if (ft_strncmp(arr[i], arr[j], 1) > 0) 
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
        }
    }
	i = -1;
	while (arr[++i])
		printf("declare -x %s\n", arr[i]);
	free_array(arr, -1);
}

t_list	*get_env_node(char *cmd, t_list *e_lst)
{
	char 	*env;
	size_t	size;

	while (e_lst->next)
	{
		env = (char *)e_lst->next->content;
		size = -1;
		while (env[++size] != '=');
		if (size == ft_strlen(cmd) && !ft_strncmp(cmd, env, size))
			return (e_lst);
		e_lst = e_lst->next;
	}	
	return (NULL);
}