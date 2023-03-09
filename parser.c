/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:58:53 by danpark           #+#    #+#             */
/*   Updated: 2023/03/09 22:17:40 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*tokenizer(char *input)
{
	t_list	*res;
	t_list	*new;
	t_token	*token;

	token = init_token();
	res = NULL;
	while (*input)
	{
		while (*input == ' ')
			input++;
		if (*input == '<' || *input == '>')
			add_redirection_struct(token, &input);
		else if (*input != '|')
			add_text_struct(token, &input);
		else if (*input == '|')
		{
			new = ft_lstnew(token);
			ft_lstadd_back(&res, new);
			token = init_token();
			input++;
		}
	}
	new = ft_lstnew(token);
	ft_lstadd_back(&res, new);
	return (res);
}

t_token	*init_token(void)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token) * 1);
	if (!token)
		exit(1);
	token->rd = 0;
	token->txt = 0;
	return (token);
}

void	add_text_struct(t_token *token, char **input)
{
	t_list	*new;
	char	*txt;

	txt = get_txt(input);
	if (txt)
	{
		new = ft_lstnew(txt);
		ft_lstadd_back(&token->txt, new);
	}
}

void	add_redirection_struct(t_token *token, char **input)
{
	t_list	*new;
	t_rd	*rd;

	rd = (t_rd *)malloc(sizeof(t_rd) * 1);
	if (!rd)
		exit(1);
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
	if (**input == '>')
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
	rd->file = get_txt(input);
	new = ft_lstnew(rd);
	ft_lstadd_back(&(token->rd), new);
}