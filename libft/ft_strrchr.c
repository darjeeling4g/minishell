/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:40:09 by danpark           #+#    #+#             */
/*   Updated: 2022/11/13 20:37:15 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	ch;

	ch = c;
	if (ft_strlen(s) == 0 && ch != 0)
		return (0);
	i = ft_strlen(s);
	if (ch == '\0')
		return (&((char *)s)[i]);
	while (s[i] != ch)
	{
		i--;
		if (i == 0 && s[i] != ch)
			return (0);
	}
	return (&((char *)s)[i]);
}
