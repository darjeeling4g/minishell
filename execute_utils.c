/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:41:54 by danpark           #+#    #+#             */
/*   Updated: 2023/03/09 22:46:46 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirection(t_list *rds)
{
	t_rd	*rd;
	int		file;

	while (rds)
	{
		rd = (t_rd *)rds->content;
		if (rd->type == IN)
		{
			if (!access(rd->file, F_OK))
				put_error_message();
			file = open(rd->file, O_RDONLY);
			if (file == -1)
				put_error_message();
			dup2(file, STDIN_FILENO);
			close(file);
		}
		else if (rd->type == HRDC)
			get_here_doc_input(rd);
		else
		{
			if (rd->type == OUT)
				file = open(rd->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			else if (rd->type == APND)
				file = open(rd->file, O_CREAT | O_APPEND | O_WRONLY, 0644);
			if (file == -1)
				put_error_message();
			dup2(file, STDOUT_FILENO);
			close(file);
		}
		rds = rds->next;
	}	
}

void	get_here_doc_input(t_rd *rd)
{
	char	*input;
	size_t	str_len;
	size_t	input_len;
	char	*str;

	str = rd->file;
	str_len = ft_strlen(str);
	while (1)
	{
		input = readline("> ");
		if (!input)
			break ;
		input_len = ft_strlen(input) - 1;
		if (str_len == input_len && ft_strncmp(str, input, input_len) == 0)
			break ;
		write(0, input, input_len + 1);
		free(input);
	}
	if (input)
		free(input);
}

char	*get_env(t_list *e_lst, const char *name)
{
	char	*str;
	size_t	size;

	while (e_lst)
	{
		str = (char *)e_lst->content;
		size = -1;
		while (str[++size] != '=');
		if (size == ft_strlen(name) && !ft_strncmp(str, name, size))
			break;
		e_lst = e_lst->next;
	}
	if (!e_lst)
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
		if (access(path, F_OK) == 0)
			break ;
		free(temp);
		free(path);
		i++;
	}
	i = -1;
	while (path_group[++i])
		free(path_group[i]);
	free(path_group);
	return (path);
}