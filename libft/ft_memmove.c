/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:32:23 by danpark           #+#    #+#             */
/*   Updated: 2022/11/18 12:42:42 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dst1;
	unsigned char	*src1;

	if (dst == src || len == 0)
		return (dst);
	dst1 = (unsigned char *)dst;
	src1 = (unsigned char *)src;
	i = 0;
	while (i < len && dst1 < src1)
	{
		*(dst1 + i) = *(src1 + i);
		i++;
	}
	while (len > 0 && dst1 > src1)
	{
		*(dst1 + len - 1) = *(src1 + len - 1);
		len--;
	}
	return (dst1);
}
