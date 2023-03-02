/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_to_str1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 19:40:06 by danpark           #+#    #+#             */
/*   Updated: 2023/01/02 16:05:40 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	change_from_char(va_list ap)
{
	char	ch;
	int		i;

	ch = (char)va_arg(ap, int);
	i = ft_putchar(ch);
	if (i == -1)
		return (-1);
	return (1);
}

int	change_from_str(va_list ap)
{
	char	*str;
	int		len;

	str = ((char *)va_arg(ap, char *));
	if (!str)
	{
		if (ft_putstr("(null)") == -1)
			return (-1);
		return (6);
	}
	len = ft_putstr(str);
	return (len);
}

int	change_from_dec(va_list ap)
{
	char	*str;
	int		len;

	str = ft_itoa(va_arg(ap, int));
	if (!str)
		return (-1);
	len = ft_putstr(str);
	free(str);
	return (len);
}

int	change_from_int(va_list ap)
{
	char	*str;
	int		len;

	str = ft_itoa(va_arg(ap, int));
	if (!str)
		return (-1);
	len = ft_putstr(str);
	free(str);
	return (len);
}

int	change_from_pct(void)
{
	int	i;

	i = ft_putchar('%');
	return (i);
}
