/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:41:54 by danpark           #+#    #+#             */
/*   Updated: 2023/03/30 15:25:01 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_vaild_file(char *filename)
{
	if (access(filename, F_OK) == FAIL)
	{
		put_error_message(2, filename);
		return (0);
	}
	else if (access(filename, R_OK) == FAIL)
	{
		put_error_message(126, filename);
		return (0);
	}
	return (1);
}

char	*get_env(t_list *e_lst, const char *name)
{
	char	*str;
	size_t	size;

	while (e_lst)
	{
		str = (char *)e_lst->content;
		size = 0;
		while (str[size] != '=')
			size++;
		if (size == ft_strlen(name) && !ft_strncmp(str, name, size))
			break ;
		e_lst = e_lst->next;
	}
	if (e_lst == NULL)
		return (NULL);
	str += (ft_strlen(name) + 1);
	return (str);
}

char	*find_bin(char *arg, char **envp)
{
	int		i;
	char	**path_group;
	char	*path;
	char	*temp;

	while (ft_strnstr(*envp, "PATH", 4) == 0)
		envp++;
	path_group = ft_split(*envp + 5, ':');
	i = 0;
	while (path_group[i])
	{
		temp = ft_strjoin(path_group[i], "/");
		path = ft_strjoin(temp, arg);
		free(temp);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		free(path_group[i]);
		i++;
	}
	free(path_group);
	return (arg);
}
