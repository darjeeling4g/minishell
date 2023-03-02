/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_to_str3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:23:48 by danpark           #+#    #+#             */
/*   Updated: 2023/01/13 14:47:47 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_uitoa(int n)
{
	long long	nbr;
	char		*p;
	int			size;

	nbr = (unsigned int)n;
	size = ft_numlen_base(nbr, 10);
	p = (char *)ft_calloc(size + 1, sizeof(char));
	if (!p)
		return (0);
	p[size] = 0;
	while (--size >= 0)
	{
		p[size] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (p);
}

int	change_from_uint(va_list ap)
{
	char			*str;
	int				len;
	unsigned int	i;

	i = (unsigned int)(va_arg(ap, long long));
	str = ft_uitoa(i);
	if (!str)
		return (-1);
	len = ft_putstr(str);
	free(str);
	return (len);
}
