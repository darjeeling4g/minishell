/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:54:09 by danpark           #+#    #+#             */
/*   Updated: 2023/03/08 20:29:17 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	interpret_token(t_list *tokens, char **envp)
{
	pid_t	pid;
	int		fds[2][2];

	if (pipe(fds[0]) == -1)
		put_error_message(errno);
	pid = fork();
	if (pid == -1)
		put_error_message(errno);
	else if (pid != 0)
		parent_do(tokens, pid, fds, envp);
	else
		execute_command(tokens, fds, 1, envp);
}

void	parent_do(t_list *tokens, pid_t pid, int *fds[], char **envp)
{
	int		i;
	int		stat;
	t_list	*tmp;

	close(fds[0][1]);
	tmp = tokens;
	while (tokens)
	{
		if (pipe(fds[1]) == -1)
			put_error_message(errno);
		pid = fork();
		if (pid == -1)
			put_error_message(errno);
		else if (pid == 0)
			execute_command((t_token *)tokens->content, tokens->next, fds, 0);
		dup2(fds[1][0], fds[0][0]);
		close(fds[1][0]);
		close(fds[1][1]);
		tokens = tokens->next;
	}
	while (tmp)
	{
		wait(&stat);
		tmp = tmp->next;
	}
}

void	execute_command(t_list *tokens, int (*fds)[2], int first, char **envp)
{
	t_token		*token;
	char		**cmd;
	char		*path;
	
	token = (t_token *)tokens->content;
	if (first)
	{
		if (tokens->next)
			dup2(fds[0][1], 1);
		close(fds[0][1]);
	}
	else
	{
		if (tokens->next)
			dup2(fds[1][1], 1);
		dup2(fds[0][0], 0);
		close(fds[1][0]);
		close(fds[1][1]);
	}
	close(fds[0][0]);
	redirection(token->rd);
	cmd = combine_command(token->txt);
	path = find_bin(cmd[0], envp);
	if (execve(path, cmd, envp))
		put_error_message(errno);
}

char	**combine_command(t_list *txt)
{
	char	**res;
	char	*cmd;
	int		size;
	int		i;

	size = ft_lstsize(txt);
	res = malloc(sizeof(char *) * size + 1);
	res[size] = NULL;
	i = 0;
	while (i < size)
	{
		res[i] = (char *)txt->content;
		txt = txt->next;
		i++;
	}
	return (res);
}

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
				put_error_message(errno);
			file = open(rd->file, O_RDONLY);
			if (file == -1)
				put_error_message(errno);
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
				put_error_message(errno);
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

char	*get_env(t_list *envlst, const char *name)
{
	while (envlst)
	{
		if (ft_strnstr(envlst->content, name, ft_strlen(name)))
			break ;
		envlst = envlst->next;
	}
	if (!envlst)
		return (NULL);
	*(envlst->content)  += (ft_strlen(name) + 1);
	return (envlst->content);
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