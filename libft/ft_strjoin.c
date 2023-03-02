/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:03:06 by danpark           #+#    #+#             */
/*   Updated: 2022/11/18 12:43:57 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

static size_t	ft_strlen_md(const char *s)
{
	size_t	i;

	i = 0;
	if (s == 0)
		return (0);
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	s1_len;
	size_t	s2_len;
	size_t	len;

	s1_len = ft_strlen_md(s1);
	s2_len = ft_strlen_md(s2);
	len = s1_len + s2_len;
	p = (char *)malloc(sizeof(char) *(len + 1));
	if (!p)
		return (0);
	p[0] = '\0';
	if (s1_len)
		ft_strcat(p, (char *)s1);
	if (s2_len)
		ft_strcat(p, (char *)s2);
	return (p);
}
