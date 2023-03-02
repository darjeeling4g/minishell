/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:38:32 by danpark           #+#    #+#             */
/*   Updated: 2022/11/18 12:43:37 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		size;
	int		i;

	size = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * size + 1);
	if (!str)
		return (0);
	i = 0;
	str[size] = '\0';
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	return (str);
}
