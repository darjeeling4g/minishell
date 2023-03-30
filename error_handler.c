/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:38:13 by danpark           #+#    #+#             */
/*   Updated: 2023/03/30 22:39:20 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	put_error_message(unsigned char code, char *cmd)
{
	g_exit_code = code;
	if (cmd)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(cmd);
	}
	else
		perror("minishell");
	return (-1);
}

int	put_customized_error_message(unsigned char code, char *cmd, char *custom)
{
	g_exit_code = code;
	if (cmd)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(custom, 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putendl_fd(custom, 2);
	}
	return (-1);
}

void	free_array(char **arr, int idx)
{
	int	i;

	i = -1;
	if (idx == -1)
		while (arr[++i])
			free(arr[i]);
	else
		while (++i < idx)
			free(arr[i]);
	free(arr);
}

void	free_token_list(t_list *tokens)
{
	t_list	*head;
	t_token	*token;
	t_list	*rds;
	t_rd	*rd;

	head = tokens;
	while (tokens)
	{
		token = (t_token *)(tokens->content);
		rds = token->rd;
		while (rds)
		{
			rd = (t_rd *)rds->content;
			if (rd->file)
				free(rd->file);
			rds = rds->next;
		}
		if (token->rd)
			ft_lstclear(&token->rd, delete_list_content);
		if (token->txt)
			ft_lstclear(&token->txt, delete_list_content);
		tokens = tokens->next;
	}
	if (head)
		ft_lstclear(&head, delete_list_content);
}

void	delete_list_content(void *content)
{
	if (content)
		free (content);
}
