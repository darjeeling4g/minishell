/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_txt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 12:44:24 by danpark           #+#    #+#             */
/*   Updated: 2023/03/30 14:31:35 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_txt(char **input, t_list *e_lst)
{
	char	*txt;

	txt = NULL;
	while (**input)
	{
		if (**input == DQ)
			txt = get_changed_double_quote(input, UNCLOSED, txt, e_lst);
		else if (**input == SQ)
			txt = get_changed_single_quote(input, UNCLOSED, txt);
		else
			txt = get_changed_string(input, txt, e_lst);
		if (**input == ' ' || **input == '|')
			break ;
	}
	return (txt);
}

char	*get_expanded_env(char **input, int *i, t_list *e_lst, int plain)
{
	int		start;
	char	*env;
	char	*tmp;

	if (plain && ((*input)[*i + 1] == DQ || (*input)[*i + 1] == SQ))
		return (0);
	start = ++(*i);
	if ((*input)[*i] == '?')
		return (ft_itoa((int)g_exit_code));
	while (ft_isalnum((*input)[*i]) || (*input)[*i] == '_')
		(*i)++;
	if (*i - start == 0)
	{
		(*i)--;
		return (ft_strdup("$"));
	}
	env = ft_substr(*input, start, *i - start);
	if (!env)
		exit(1);
	tmp = env;
	env = get_env(e_lst, env);
	free (tmp);
	(*i)--;
	return (env);
}

char	*get_changed_double_quote(char **input, int quote, char *txt, \
t_list *e_lst)
{
	int		i;
	int		start;
	char	*env;

	i = 0;
	(*input)++;
	start = i;
	while (quote == UNCLOSED)
	{
		if ((*input)[i] == DQ)
			quote = CLOSED;
		if ((*input)[i] == '$')
		{
			if (i - start > 0)
				txt = ft_substrjoin(txt, *input, start, i - start);
			env = get_expanded_env(input, &i, e_lst, 0);
			txt = ft_substrjoin(txt, env, 0, ft_strlen_md(env));
			start = i + 1;
		}
		i++;
	}
	if (start != i)
		txt = ft_substrjoin(txt, *input, start, i - start - 1);
	(*input) += i;
	return (txt);
}

char	*get_changed_single_quote(char **input, int quote, char *txt)
{
	int		i;
	int		start;

	i = 0;
	(*input)++;
	start = i;
	while (quote == UNCLOSED)
	{
		if ((*input)[i] == SQ)
			quote = CLOSED;
		i++;
	}
	if (start != i)
		txt = ft_substrjoin(txt, *input, start, i - start - 1);
	(*input) += i;
	return (txt);
}

char	*get_changed_string(char **input, char *txt, t_list *e_lst)
{
	int		i;
	int		start;
	char	*env;

	i = 0;
	start = i;
	while (**input == ' ')
		(*input)++;
	while ((*input)[i] != ' ' && (*input)[i] != '\0' && (*input)[i] != '|' && \
	(*input)[i] != DQ && (*input)[i] != SQ)
	{
		if ((*input)[i] == '$')
		{
			if (i - start > 0)
				txt = ft_substrjoin(txt, *input, start, i - start);
			env = get_expanded_env(input, &i, e_lst, 1);
			txt = ft_substrjoin(txt, env, 0, ft_strlen_md(env));
			start = i + 1;
		}
		i++;
	}
	if (start != i)
		txt = ft_substrjoin(txt, *input, start, i - start);
	(*input) += i;
	return (txt);
}
