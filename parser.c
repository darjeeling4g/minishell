/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:58:53 by danpark           #+#    #+#             */
/*   Updated: 2023/03/30 22:43:20 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*tokenizer(char *input, t_list *e_lst)
{
	t_list	*tokens;
	t_list	*new;
	t_token	*token;

	token = init_token();
	tokens = NULL;
	while (*input)
	{
		while (*input == ' ' || *input == '\t')
			input++;
		if (add_token_content(&input, e_lst, tokens, token) == FAIL)
			return (NULL);
		if (*input == '|')
		{
			new = ft_lstnew(token);
			ft_lstadd_back(&tokens, new);
			token = init_token();
			input++;
		}
	}
	new = ft_lstnew(token);
	ft_lstadd_back(&tokens, new);
	if (tokens == NULL)
		ft_lstdelone(new, delete_list_content);
	return (tokens);
}

int	add_token_content(char **input, t_list *e_lst, t_list *tokens, \
t_token *token)
{
	if (**input == '<' || **input == '>')
	{
		if (add_redirection_struct(token, input, e_lst) < 0)
		{
			free(token);
			free_token_list(tokens);
			return (-1);
		}
	}
	else if (**input != '|')
		add_text_struct(token, input, e_lst);
	return (0);
}

void	add_text_struct(t_token *token, char **input, t_list *e_lst)
{
	t_list	*new;
	char	*txt;

	txt = get_txt(input, e_lst);
	if (txt)
	{
		new = ft_lstnew(txt);
		ft_lstadd_back(&token->txt, new);
	}
}

int	add_redirection_struct(t_token *token, char **input, t_list *e_lst)
{
	t_list	*new;
	t_rd	*rd;

	rd = (t_rd *)malloc(sizeof(t_rd) * 1);
	if (!rd)
		exit(1);
	rd->read = -1;
	add_rd_type(rd, input);
	if (is_valid_filename(*input))
		rd->file = get_txt(input, e_lst);
	else
	{
		free(rd);
		return (-1);
	}
	new = ft_lstnew(rd);
	ft_lstadd_back(&(token->rd), new);
	return (0);
}

void	add_rd_type(t_rd *rd, char **input)
{
	if (**input == '<')
	{
		(*input)++;
		if (**input == '<')
		{
			rd->type = HRDC;
			(*input)++;
		}
		else
			rd->type = IN;
	}
	else if (**input == '>')
	{
		(*input)++;
		if (**input == '>')
		{
			rd->type = APND;
			(*input)++;
		}
		else
			rd->type = OUT;
	}
}
