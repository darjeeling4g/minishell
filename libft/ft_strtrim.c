/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:56:35 by danpark           #+#    #+#             */
/*   Updated: 2022/11/17 22:32:22 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char ch, char const *set)
{
	while (*set)
	{
		if (ch == *set)
			return (1);
		set++;
	}
	return (0);
}

static char	*get_str(char *s1, char *set, size_t size, size_t start)
{
	char	*p;
	size_t	i;

	i = 0;
	if (size == start)
	{
		p = (char *)malloc(sizeof(char));
		if (!p)
			return (0);
		p[0] = 0;
		return (p);
	}
	while (is_set(s1[size - 1], set))
		size--;
	p = (char *)malloc(sizeof(char) * (size - start + 1));
	if (!p)
		return (0);
	p[size - start] = 0;
	while (start < size)
		p[i++] = s1[start++];
	return (p);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size;
	size_t	start;
	char	*p;

	start = 0;
	if (s1 == 0)
		return (0);
	if (set == 0)
		return ((char *)s1);
	size = ft_strlen(s1);
	while (s1[start] && is_set(s1[start], set))
		start++;
	p = get_str((char *)s1, (char *)set, size, start);
	return (p);
}
