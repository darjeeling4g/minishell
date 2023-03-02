/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:28:23 by danpark           #+#    #+#             */
/*   Updated: 2022/11/18 12:44:57 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	size;
	char			*p;

	i = 0;
	if (s == 0)
		return (0);
	size = (unsigned int)ft_strlen(s);
	p = (char *)malloc(sizeof(char) * (size + 1));
	if (!p)
		return (0);
	p[size] = 0;
	while (i < size)
	{
		p[i] = f(i, s[i]);
		i++;
	}
	return (p);
}
