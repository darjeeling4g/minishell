/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:10:30 by danpark           #+#    #+#             */
/*   Updated: 2023/03/10 02:39:52 by danpark          ###   ########.fr       */
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

// size_t	ft_strlen_md(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	if (!s)
// 		return (0);
// 	while (s[i])
// 	{
// 		i++;
// 	}
// 	return (i);
// }

char	**list_to_array(t_list *lst)
{
	char	**res;
	char	*str;
	int		size;
	int		i;

	size = ft_lstsize(lst);
	if (!size)
		return (NULL);
	res = malloc(sizeof(char *) * size + 1);
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
			put_error_message(EXIT);
		new = ft_lstnew(str);
		ft_lstadd_back(&res, new);
		arr++;
	}
	return (res);
}