/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:41:54 by danpark           #+#    #+#             */
/*   Updated: 2023/03/10 16:54:01 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void redirection(t_list *rds, int fd)
{
	t_rd *rd;
	int file;

	while (rds)
	{
		rd = (t_rd *)rds->content;
		if (rd->type == IN)
		{
			file = open(rd->file, O_RDONLY);
			if (file == -1)
				put_error_message(EXIT);
			dup2(file, STDIN_FILENO);
			close(file);
		}
		else if (rd->type == HRDC)
			get_here_doc_input(rd, fd);
		else
		{
			if (rd->type == OUT)
				file = open(rd->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			else if (rd->type == APND)
				file = open(rd->file, O_CREAT | O_APPEND | O_WRONLY, 0644);
			if (file == -1)
				put_error_message(EXIT);
			dup2(file, STDOUT_FILENO);
			close(file);
		}
		rds = rds->next;
	}
}

void get_here_doc_input(t_rd *rd, int infd)
{
	char *input;
	char *rd_line;
	size_t rd_len;
	size_t lmt_len;
	int fd[2];

	if (pipe(fd) == -1)
		put_error_message(EXIT);
	input = 0;
	lmt_len = ft_strlen(rd->file);
	while (1)
	{
		write(1, "> ", 3);
		rd_line = get_next_line(fd[1]);
		if (!rd_line)
			break;
		rd_len = ft_strlen(rd_line) - 1;
		if (lmt_len == rd_len && ft_strncmp(rd->file, rd_line, rd_len) == 0)
			break;
		input = ft_substrjoin(input, rd_line, 0, ft_strlen(rd_line));
		free(rd_line);
	}
	free(rd->file);
	rd->file = input;
	write(fd[1], input, ft_strlen(input));
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
}

char *get_env(t_list *e_lst, const char *name)
{
	char *str;
	size_t size;

	while (e_lst)
	{
		str = (char *)e_lst->content;
		size = -1;
		while (str[++size] != '=')
			;
		if (size == ft_strlen(name) && !ft_strncmp(str, name, size))
			break;
		e_lst = e_lst->next;
	}
	if (!e_lst)
		return (NULL);
	str += (ft_strlen(name) + 1);
	return (str);
}

char *find_bin(char *arg, char **envp)
{
	int i;
	char **path_group;
	char *path;
	char *temp;

	while (ft_strnstr(*envp, "PATH", 4) == 0)
		envp++;
	path_group = ft_split(*envp + 5, ':');
	i = 0;
	while (path_group[i])
	{
		temp = ft_strjoin(path_group[i], "/");
		path = ft_strjoin(temp, arg);
		if (access(path, F_OK) == 0)
			break;
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
