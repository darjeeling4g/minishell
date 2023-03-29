/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:07:41 by danpark           #+#    #+#             */
/*   Updated: 2023/03/30 04:57:03 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_filename(char *input)
{
	char	*msg;

	msg = NULL;
	while (*input == ' ')
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
		msg = ft_substrjoin(msg, "'", 0 ,1);
		put_customized_error_message(2, NULL, msg);
		return (FALSE);
	}
	return (TRUE);
}

int	check_token_syntax(t_list *tokens)
{
	t_token	*token;
	t_list	*rds;
	t_rd	*rd;
	int		flag;

	while (tokens)
	{
		flag = 0;
		token = (t_token *)tokens->content;
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

//int	is_valid_redirection_token_syntax(char *str)
//{
//	int	i;
//	int	rd_cnt;
//
//	i = 0;
//	rd_cnt = 0;
//	while (str[i] == ' ')
//		i++;
//	rd_cnt = count_contained_redirection(&str[i]);
//	if (str[i] != DQ && str[i] != SQ && rd_cnt > 0)
//	{
//		put_redirection_syntax_error_message(&str[i]);
//		return (FALSE);
//	}
//	return (TRUE);
//}
//
//int	count_contained_redirection(char *str)
//{
//	int	cnt;
//
//	cnt = 0;
//	while (str[cnt] == '<' | str[cnt] == '>')
//		cnt++;
//	return (cnt);
//}
//
//void	put_redirection_syntax_error_message(char *str)
//{
//	int	i;
//	int	err_token_len;
//	char	*err_token;
//
//	i = 0;
//	if (str == NULL)
//		put_customized_error_message(2, 0, get_syntax_error_message(NULL));
//	err_token_len = count_contained_redirection(str);
//	if (err_token_len == 1)
//		err_token = ft_substr(str, 0, 1);
//	else
//		err_token = ft_substr(str, 0, 2);
//	put_customized_error_message(2, 0, get_syntax_error_message(err_token));
//	free(err_token);
//	// else if (str[i] == '<')
//	// {
//	// 	if (str[i + 1] && str[i + 1] == '<')
//	// 		put_customized_error_message(2, 0, \
//	// 		"syntax error near unexpected token `<<'");
//	// 	else
//	// 		put_customized_error_message(2, 0, \
//	// 		"syntax error near unexpected token `<'");
//	// }
//	// else if (str[i] == '>')
//	// {
//	// 	if (str[i + 1] && str[i + 1] == '>')
//	// 		put_customized_error_message(2, 0, \
//	// 		"syntax error near unexpected token `>>'");
//	// 	else
//	// 		put_customized_error_message(2, 0, \
//	// 		"syntax error near unexpected token `>'");
//	// }
//}
//
//char	*get_syntax_error_message(char *str)
//{
//	char	*error_msg;
//	char	*tmp;
//
//	if (str == NULL)
//		error_msg = ft_strdup("syntax error near unexpected token `newline'");
//	else
//	{
//		error_msg = ft_strjoin("syntax error near unexpected token `", str);
//		if (!error_msg)
//			exit(1);
//		tmp = error_msg;
//		error_msg = ft_strjoin(error_msg, "'");
//		free(tmp);
//	}
//	if (!error_msg)
//		exit(1);
//	return (error_msg);
//}
