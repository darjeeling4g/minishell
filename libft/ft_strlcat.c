/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:49:43 by danpark           #+#    #+#             */
/*   Updated: 2022/11/18 12:44:08 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *rest, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dst_size;
	size_t	rest_size;

	i = 0;
	dst_size = ft_strlen((const char *)dst);
	j = dst_size;
	rest_size = ft_strlen(rest);
	if (dstsize <= dst_size)
		return (rest_size + dstsize);
	else
	{
		while (i + j + 1 < dstsize && rest[i])
		{
			dst[j + i] = rest[i];
			i++;
		}
		dst[j + i] = '\0';
		return (dst_size + rest_size);
	}
}
