/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:26:26 by danpark           #+#    #+#             */
/*   Updated: 2022/11/18 12:42:50 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	void			*p;
	unsigned char	*bf;

	p = b;
	bf = (unsigned char *)b;
	while (len > 0)
	{
		*(bf++) = c;
		len--;
	}
	return (p);
}
