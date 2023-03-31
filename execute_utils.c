/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:41:54 by danpark           #+#    #+#             */
/*   Updated: 2023/03/31 22:36:54 by danpark          ###   ########.fr       */
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
		while (str[size] && str[size] != '=')
			size++;
		if (size == ft_strlen(name) && !ft_strncmp(str, name, size))
			break ;
		e_lst = e_lst->next;
	}
	if (e_lst == NULL)
		return (NULL);
	str += (ft_strlen(name) + 1);
	str = ft_strdup(str);
	if (!str)
		exit(1);
	return (str);
}

char	*find_bin(char *arg, char **envp)
{
	int			i;
	char		*path;
	char		**path_group;
	struct stat	sb;

	stat(arg, &sb);
	if ((sb.st_mode & S_IFMT) == S_IFDIR)
		return (arg);
	while (*envp && ft_strnstr(*envp, "PATH", 4) == 0)
		envp++;
	if (!*envp)
		return (arg);
	path_group = ft_split(*envp + 5, ':');
	i = -1;
	while (path_group[++i])
	{
		path = get_complete_path(arg, path_group[i]);
		if (path)
			return (path);
	}
	free(path_group);
	return (arg);
}

char	*get_complete_path(char *arg, char *path_group)
{
	char	*path;
	char	*temp;

	temp = ft_strjoin(path_group, "/");
	path = ft_strjoin(temp, arg);
	free(temp);
	if (access(path, F_OK) == 0)
		return (path);
	free(path);
	free(path_group);
	return (NULL);
}
