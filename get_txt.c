/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_txt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 12:44:24 by danpark           #+#    #+#             */
/*   Updated: 2023/03/03 21:51:06 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//this function will change and return only literal in double quotation, and increase input pointer
void	change_double_quote(char **input, int **quote, char *txt)
{
	int		i;
	int		start;
	char	*env;//expanded env

	i = 0;
	*input++;//start after $
	start = i;
	while (*quote[F_DQ] == UNCLOSED)//it will recur until quotation open
	{
		if (*input[i] == DQ)//if double quotation appear, it will closed and recursion is finished.
			*quote[F_DQ] = CLOSED;
		if (*input[i] == '$')//if '$' sign appear, it will expand.
		{
			if (i - start > 0)//previous characters are newly assigned.
				txt = ft_substrjoin(txt, input, start, i - start);//txt will free in ft_substrjoin.
			env = get_expanded_env(input, &i);//index increase as length of environment name.
			txt = ft_substrjoin(txt, env, 0, ft_strlen_md(env));//add expanded env to txt.
			start = i;//updates the index after the environment name.
		}
		i++;
	}
	if (start != i)//if there are no environs or string remain after envivorn, add string to txt. 
		txt = ft_substrjoin(txt, input, start, i - start);
	(*input) += ++i;//increase input pointer after double quotation.
}

//this function will change and return only literal in single quotation
void	change_single_quote(char **input, int **quote, char *txt)
{
	int		i;
	int		start;
	char	*env;//expanded env

	i = 0;
	start = i;
	while (*quote[F_SQ] == UNCLOSED)//it will recur until quotation open
	{
		if (*input[i] == SQ)//if double quotation appear, it will closed and recursion is finished.
			*quote[F_SQ] = CLOSED;
		i++;
	}
	if (start != i)//if there are no environs or string remain after envivorn, add string to txt. 
		txt = ft_substrjoin(txt, input, start, i - start);
	(*input) += ++i;//increase input pointer after single quotation.
}

//this function will change and return literal to space character
void	change_string(char **input, int **quote, char *txt)
{
	int		i;
	int		start;
	char	*env;//expanded env

	i = 0;
	start = i;
	while (**input == ' ')
		(*input)++;
	while (*input[i] != ' ' || *input[i] != '\0' || *input[i] != DQ || *input[i] != SQ)//it will recur to end of string.
	{
		if (*input[i] == '$')//if '$' sign appear, env will be expanded.
		{
			if (i - start > 0)//previous characters are newly assigned.
				txt = ft_substrjoin(txt, input, start, i - start);//txt will free in ft_substrjoin.
			env = get_expanded_env(input, &i);//index increase as length of environment name.
			txt = ft_substrjoin(txt, env, 0, ft_strlen_md(env));//add expanded env to txt.
			start = i;//updates the index after the environment name.
		}
		i++;
	}
	if (start != i)//if there are no environs or string remain after envivorn, add string to txt. 
		txt = ft_substrjoin(txt, input, start, i - start);
	(*input) += i;//increase input pointer.
	return (txt);
}

//get_txt will return one string argument
char	*get_txt(char **input)
{
	int		i;
	int		start;
	char	*txt;
	char	*env;
	int		quote[3];

	i = -1;
	while (++i < 3)
		quote[i] = 0;
	txt = 0;
	while (**input == ' ' || **input == '\n')
		(*input)++;
	while (**input)
	{
		if (**input == DQ)
		{
			quote[F_DQ] == UNCLOSED;
			change_double_quote(input, &quote, txt);
		}
		else if (**input == SQ)
		{
			quote[F_SQ] == UNCLOSED;
			change_single_quote(input, &quote, txt);
		}
		else
		{
			quote[F_LT] == 1;
			change_string(input, &quote, txt);
		}
		if (*input[i] == ' ')
			break ;
	}
	return (txt);
}

//get_expanded_env will expand environment and return it
char	*get_expanded_env(char **input, int *i)
{
	int		start;
	char	*env;
	char	*tmp;

	start = ++(*i);
	while (ft_isalnum(*input[*i]))
		*i++;
	if (*i - start == 0)
		return (0);
	env = ft_substr(input, start, *i - start);
	if (!env)
		exit(1);
	tmp = env;
	env = getenv(env);
	if (!env)
		return (tmp);
	free (tmp);
	return (env);
}
