/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:41:54 by danpark           #+#    #+#             */
/*   Updated: 2023/03/28 17:19:56 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_vaild_file(char *filename)
{
	if (!filename)
	{
		put_customized_error_message(2, 0, "syntax error near unexpected token `newline'");
		return (0);
	}
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

int	redirection(t_list *rds, int std[2])
{
	t_rd *rd;
	int file;

	while (rds)
	{
		rd = (t_rd *)rds->content;
		if (rd->type == IN)
		{
			if (is_vaild_file(rd->file) == FALSE)
				return (-1);
			file = open(rd->file, O_RDONLY);
			if (file == -1)
				return (put_error_message(1, 0));
			dup2(file, STDIN_FILENO);
			close(file);
		}
		else if (rd->type == HRDC)
			get_here_doc_input(rd, std);
		else
		{
			if (rd->type == OUT)
				file = open(rd->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			else if (rd->type == APND)
				file = open(rd->file, O_CREAT | O_APPEND | O_WRONLY, 0644);
			if (file == -1)
				return (put_error_message(1, 0));
			dup2(file, STDOUT_FILENO);
			close(file);
		}
		rds = rds->next;
	}
	return (0);
}

void get_here_doc_input(t_rd *rd, int std[2])
{
	char *input;
	char *rd_line;
	size_t rd_len;
	size_t lmt_len;
	int fds[2];

	if (pipe(fds) == -1)
		exit(1);
	input = 0;
	lmt_len = ft_strlen(rd->file);
	while (1)
	{
		write(std[1], "> ", 3);
		rd_line = get_next_line(std[0]);
		if (!rd_line)
			break;
		rd_len = ft_strlen(rd_line) - 1;
		if (lmt_len == rd_len && ft_strncmp(rd->file, rd_line, rd_len) == 0)
			break;
		input = ft_substrjoin(input, rd_line, 0, ft_strlen(rd_line));
		free(rd_line);
	}
	write(fds[1], input, ft_strlen(input));
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
	close(fds[1]);
}

char *get_env(t_list *e_lst, const char *name)
{
	char *str;
	size_t size;

	while (e_lst)
	{
		str = (char *)e_lst->content;
		size = -1;
		while (str[++size] != '=');
		if (size == ft_strlen(name) && !ft_strncmp(str, name, size))
			break;
		e_lst = e_lst->next;
	}
	if (e_lst == NULL)
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
		free(temp);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		free(path_group[i]);
		i++;
	}
	free(path_group);
	return (0);
}
