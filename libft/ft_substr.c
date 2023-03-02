/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:33:10 by danpark           #+#    #+#             */
/*   Updated: 2022/11/18 12:46:07 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
