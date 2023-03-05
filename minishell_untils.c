/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_untils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:10:30 by danpark           #+#    #+#             */
/*   Updated: 2023/03/03 21:51:07 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;

	if (s == 0)
		return (0);
	if (ft_strlen(s) < start + len)
		len = ft_strlen(s) - start;
	if (ft_strlen(s) <= start)
		len = 0;
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		return (0);
	i = 0;
	while (i < len)
	{
		p[i] = s[start + i];
		i++;
	}
	p[len] = 0;
	return (p);
}

char	*ft_substrjoin(char *s1, char *s2, unsigned int s2_start, size_t s2_len)
{
	char	*str;
	char	*sub_str;

	sub_str = ft_substr(s2, s2_start, s2_len);
	free (s2);
	if (!s1)
		return (sub_str);
	str = ft_strjoin(s1, sub_str);
	free (s1);
	free (sub_str);
	return (str);
}

size_t	ft_strlen_md(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		i++;
	}
	return (i);
}
