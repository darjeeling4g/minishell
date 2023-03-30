/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:10:30 by danpark           #+#    #+#             */
/*   Updated: 2023/03/30 19:49:34 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substrjoin(char *s1, char *s2, unsigned int s2_start, size_t s2_len)
{
	char	*str;
	char	*sub_str;

	sub_str = ft_substr(s2, s2_start, s2_len);
	if (!s1)
		return (sub_str);
	str = ft_strjoin(s1, sub_str);
	free (s1);
	free (sub_str);
	return (str);
}

char	**list_to_array(t_list *lst)
{
	char	**res;
	char	*str;
	int		size;
	int		i;

	size = ft_lstsize(lst);
	if (!size)
		return (NULL);
	res = malloc(sizeof(char *) * (size + 1));
	res[size] = NULL;
	i = 0;
	while (i < size)
	{
		str = ft_strdup((char *)lst->content);
		res[i] = str;
		lst = lst->next;
		i++;
	}
	return (res);
}

t_list	*array_to_list(char **arr)
{
	t_list	*res;
	t_list	*new;
	char	*str;

	res = NULL;
	while (*arr)
	{
		str = ft_strdup(*arr);
		if (!str)
			put_error_message(1, NULL);
		new = ft_lstnew(str);
		ft_lstadd_back(&res, new);
		arr++;
	}
	return (res);
}

void	join_input(char **input, int flag)
{
	char	*tmp;
	char	*add_input;

	while (flag != 1)
	{
		rl_on_new_line();
		add_input = readline("> ");
		tmp = *input;
		*input = ft_strjoin(*input, "\n");
		free(tmp);
		tmp = *input;
		*input = ft_strjoin(*input, add_input);
		flag = is_complete_command(*input);
		free(tmp);
		free(add_input);
	}
}

int	is_complete_command(char *input)
{
	int	i;
	int	flag;

	i = -1;
	flag = 1;
	while (input[++i])
	{
		if (input[i] == DQ && flag == 1)
			flag = DQ;
		else if (input[i] == SQ && flag == 1)
			flag = SQ;
		else if (input[i] == DQ && flag == DQ)
			flag = 1;
		else if (input[i] == SQ && flag == SQ)
			flag = 1;
	}
	return (flag);
}
