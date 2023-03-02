/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_to_str2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 20:20:42 by danpark           #+#    #+#             */
/*   Updated: 2023/01/13 14:52:54 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_numlen_base(size_t num, unsigned int base)
{
	unsigned int	i;

	i = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num /= base;
		i++;
	}
	return (i);
}

int	change_from_ptr(va_list ap)
{
	char	*str;
	char	*hex;
	size_t	num;
	int		size;

	hex = "0123456789abcdef";
	num = (size_t)va_arg(ap, void *);
	size = ft_numlen_base(num, 16);
	str = (char *)malloc(sizeof(char) * size + 3);
	if (!str)
		return (-1);
	str[size + 2] = 0;
	while (--size >= 0)
	{
		str[size + 2] = hex[num % 16];
		num /= 16;
	}
	str[0] = '0';
	str[1] = 'x';
	size = ft_putstr(str);
	free(str);
	return (size);
}

int	change_from_hex_s(va_list ap)
{
	char			*str;
	char			*hex;
	unsigned int	num;
	int				size;

	hex = "0123456789abcdef";
	num = va_arg(ap, unsigned int);
	size = ft_numlen_base(num, 16);
	str = (char *)malloc(sizeof(char) * size + 1);
	if (!str)
		return (-1);
	str[size] = 0;
	while (--size >= 0)
	{
		str[size] = hex[num % 16];
		num /= 16;
	}
	size = ft_putstr(str);
	free(str);
	return (size);
}

int	change_from_hex_l(va_list ap)
{
	char			*str;
	char			*hex;
	unsigned int	num;
	int				size;

	hex = "0123456789ABCDEF";
	num = va_arg(ap, unsigned int);
	size = ft_numlen_base(num, 16);
	str = (char *)malloc(sizeof(char) * size + 1);
	if (!str)
		return (-1);
	str[size] = 0;
	while (--size >= 0)
	{
		str[size] = hex[num % 16];
		num /= 16;
	}
	size = ft_putstr(str);
	free(str);
	return (size);
}
