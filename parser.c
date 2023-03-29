/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:58:53 by danpark           #+#    #+#             */
/*   Updated: 2023/03/29 20:14:42 by danpark          ###   ########.fr       */
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
		while (*input == ' ')
			input++;
		if (*input == '<' || *input == '>')
		{
			if (add_redirection_struct(token, &input, e_lst) < 0)
			{
				free(token);
				free_token_list(tokens);
				return (NULL);
			}
		}
		else if (*input != '|')
			add_text_struct(token, &input, e_lst);
		else if (*input == '|')
		{
			new = ft_lstnew(token);
			ft_lstadd_back(&tokens, new);
			token = init_token();
			input++;
		}
	}
	new = ft_lstnew(token);
	ft_lstadd_back(&tokens, new);
	return (tokens);
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
	int		rd_cnt;

	rd_cnt = count_contained_redirection(*input);
	if (rd_cnt > 2)
	{
		put_redirection_syntax_error_message((*input)+=rd_cnt);
		return (-1);
	}
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
	if (is_valid_redirection_token_syntax(*input))
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
