/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:32:28 by danpark           #+#    #+#             */
/*   Updated: 2022/12/02 22:45:49 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*ft_strjoin_md(char const *s1, char const *s2, int s2_len)
{
	char	*p;
	int		s1_len;
	int		i;

	i = -1;
	if (!s1 && !s2_len)
		return (NULL);
	s1_len = ft_strlen_md(s1);
	p = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!p)
		return (NULL);
	while (++i < s1_len)
		p[i] = s1[i];
	i--;
	while (++i < s2_len + s1_len)
		p[i] = s2[i - s1_len];
	p[i] = '\0';
	return (p);
}
