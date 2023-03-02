/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:53:34 by danpark           #+#    #+#             */
/*   Updated: 2022/11/13 21:04:31 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	nd_size;
	size_t	i;
	size_t	j;
	size_t	index;

	if ((*needle == 0))
		return ((char *)haystack);
	nd_size = ft_strlen(needle);
	i = 0;
	while (i < len && haystack[i])
	{
		index = i;
		j = 0;
		while (haystack[i] && needle[j] && i < len)
		{
			if (haystack[i] != needle[j])
				break ;
			i++;
			j++;
		}
		if (j == nd_size)
			return (&((char *)haystack)[index]);
		i = index + 1;
	}
	return (0);
}
