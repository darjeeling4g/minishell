/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:13:25 by danpark           #+#    #+#             */
/*   Updated: 2022/11/28 15:12:42 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(long long num)
{
	int	i;

	i = 0;
	if (num < 0)
	{
		num = -num;
		i++;
	}
	while (num > 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long long	nbr;
	char		*p;
	int			size;

	nbr = (long long)n;
	size = ft_numlen(nbr);
	if (nbr == 0)
		size = 1;
	p = (char *)ft_calloc(size + 1, sizeof(char));
	if (!p)
		return (0);
	if (nbr < 0)
	{
		p[0] = '-';
		nbr *= -1;
	}
	p[size] = 0;
	while (--size >= 0)
	{
		if (p[0] == '-' && size == 0)
			break ;
		p[size] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (p);
}
