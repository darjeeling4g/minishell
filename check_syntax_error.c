/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:07:41 by danpark           #+#    #+#             */
/*   Updated: 2023/03/30 21:58:07 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_filename(char *input)
{
	char	*msg;

	msg = NULL;
	while (*input == ' ' || *input == '\t')
		input++;
	if (*input == '<')
	{
		msg = ft_strdup("syntax error near unexpected token `<");
		if (*(input + 1) == '<')
			msg = ft_substrjoin(msg, "<", 0, 1);
	}
	else if (*input == '>')
	{
		msg = ft_strdup("syntax error near unexpected token `>");
		if (*(input + 1) == '>')
			msg = ft_substrjoin(msg, ">", 0, 1);
	}
	if (msg)
	{
		msg = ft_substrjoin(msg, "'", 0, 1);
		put_customized_error_message(2, NULL, msg);
		free(msg);
		return (FALSE);
	}
	return (TRUE);
}

int	is_exist_filename(t_token *token)
{
	t_list	*rds;
	t_rd	*rd;
	int		flag;

	flag = 0;
	rds = token->rd;
	while (rds)
	{
		rd = (t_rd *)rds->content;
		if (rd->file == NULL)
		{
			flag = 1;
			break ;
		}
		rds = rds->next;
	}
	return (flag);
}

int	check_token_syntax(t_list *tokens)
{
	t_token	*token;
	int		flag;

	while (tokens)
	{
		token = (t_token *)tokens->content;
		flag = is_exist_filename(token);
		if (tokens->next)
		{
			if (flag == 1 || (!token->txt && !token->rd))
			{
				put_customized_error_message(2, NULL,
					"syntax error near unexpected token `|'");
				return (FALSE);
			}
		}
		else if (flag == 1)
		{
			put_customized_error_message(2, NULL,
				"syntax error near unexpected token `newline'");
			return (FALSE);
		}
		tokens = tokens->next;
	}
	return (TRUE);
}
