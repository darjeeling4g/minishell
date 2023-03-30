/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:07:52 by siyang            #+#    #+#             */
/*   Updated: 2023/03/30 18:43:39 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_export(char **cmd, t_list *e_lst)
{
	char	**env;

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
			update_env_list(env[0], *cmd, e_lst);
			free_array(env, -1);
			cmd++;
		}
	}
	g_exit_code = 0;
}

void	update_env_list(char *env, char *cmd, t_list *e_lst)
{
	t_list	*new;
	t_list	*tmp;
	char	*str;

	tmp = get_env_node(env, e_lst);
	str = ft_strdup(cmd);
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
}

void	sort_n_print(t_list *e_lst)
{
	char	**arr;
	int		i;
	int		j;

	arr = list_to_array(e_lst);
	i = -1;
	while (arr[++i])
	{
		j = i;
		while (arr[++j])
			sort_envp(i, j, arr);
	}
	print_sorted_envp(arr);
	free_array(arr, -1);
}

void	sort_envp(int i, int j, char **arr)
{
	char	*tmp;
	int		k;

	k = 0;
	while (arr[i][k] != '=' && arr[j][k] != '=')
	{
		if (((arr[i][k] - arr[j][k]) > 0) ||
			((arr[i][k] == arr[j][k]) && (arr[j][k + 1] == '=')))
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
