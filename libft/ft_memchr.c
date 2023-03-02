/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:01:55 by danpark           #+#    #+#             */
/*   Updated: 2022/11/18 14:43:48 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	ch;

	ch = c;
	while (n > 0)
	{
		if (*(unsigned char *)s == ch)
			return ((void *)s);
		s++;
		n--;
	}
	return (0);
}
