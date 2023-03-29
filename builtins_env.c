/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 20:10:18 by danpark           #+#    #+#             */
/*   Updated: 2023/03/30 06:32:25 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_env(t_list *e_lst)
{
	char *env;

	while (e_lst)
	{
		env = (char *)e_lst->content;
		if (ft_strchr(env, '=')) 
			printf("%s\n", env);
		e_lst = e_lst->next;
	}
	g_exit_code = 0;
}

void	execute_export(char **cmd, t_list *e_lst)
{
	t_list	*new;
	t_list	*tmp;
	char	**env;
	char	*str;

	cmd++;
	if (!*cmd)
		sort_n_print(e_lst);
	else
	{
		while (*cmd)
		{
			env = ft_split(*cmd, '=');
			if (!is_valid_name(env[0]))
			{
				free_array(env, -1);
				put_customized_error_message(1, *cmd, "not a valid identifier");
				return ;
			}
			tmp = get_env_node(env[0], e_lst);
			free_array(env, -1);
			str = ft_strdup(*cmd);
			if (!str)
				exit(1);
			if (tmp)
			{
				free(tmp->next->content);
				tmp->next->content = str;
			}
			else
			{
				new = ft_lstnew(str);
				if (!new)
					exit(1);
				ft_lstadd_back(&e_lst, new);
			}
			cmd++;
		}
	}
	g_exit_code = 0;
}

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

void	sort_n_print(t_list *e_lst)
{
	char	**arr;
	char	*tmp;
	int		i;
	int		j;
	int		k;

	arr = list_to_array(e_lst);
	i = -1;
	while (arr[++i])
	{
		j = i;
		while (arr[++j])
		{
			k = 0;
			while (arr[i][k] != '=' && arr[j][k] != '=')
			{
				if (((arr[i][k] - arr[j][k]) > 0) || ((arr[i][k] == arr[j][k]) && (arr[j][k + 1] == '=')))
				{
					tmp = arr[i];
					arr[i] = arr[j];
					arr[j] = tmp;
					break ;
				}
				else if ((arr[i][k] - arr[j][k]) < 0)
					break ;
				k++;
			}
		}
	}
	print_sorted_envp(arr);
	free_array(arr, -1);
}

void	print_sorted_envp(char **arr)
{
	int		i;
	char	*equal;

	i = -1;
	while (arr[++i])
	{
		if (ft_strncmp("_=", arr[i], 2))
		{
			equal = ft_strchr(arr[i], '=');
			if (equal)
			{
				*equal = '\0';
				printf("declare -x %s=\"%s\"\n", arr[i], equal + 1);
			}
			else
				printf("declare -x %s\n", arr[i]);
		}
	}
}

t_list	*get_env_node(char *name, t_list *e_lst)
{
	char 	*env;
	size_t	size;

	while (e_lst->next)
	{
		env = (char *)e_lst->next->content;
		size = -1;
		while (env[++size] != '=' && env[size] != '\0');
		if (size == ft_strlen(name) && !ft_strncmp(name, env, size))
			return (e_lst);
		e_lst = e_lst->next;
	}
	return (NULL);
}
