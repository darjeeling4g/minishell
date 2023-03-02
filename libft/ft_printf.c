/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 20:33:03 by danpark           #+#    #+#             */
/*   Updated: 2023/01/02 16:07:14 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		len[1];

	*len = 0;
	va_start(ap, format);
	get_converted_value(format, ap, len);
	va_end(ap);
	return (*len);
}

void	get_converted_value(const char *format, va_list ap, int *sum)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (format[i])
	{
		if (format[i] == '%')
			len = put_argument(format[++i], ap);
		else
			len = ft_putchar(format[i]);
		if (len == -1)
		{
			*sum = -1;
			return ;
		}
		*sum += len;
		i++;
	}
	return ;
}

int	put_argument(char spec, va_list ap)
{
	int	len;

	if (spec == '%')
		len = change_from_pct();
	else if (spec == 'c')
		len = change_from_char(ap);
	else if (spec == 's')
		len = change_from_str(ap);
	else if (spec == 'p')
		len = change_from_ptr(ap);
	else if (spec == 'u')
		len = change_from_uint(ap);
	else if (spec == 'd')
		len = change_from_dec(ap);
	else if (spec == 'i')
		len = change_from_int(ap);
	else if (spec == 'x')
		len = change_from_hex_s(ap);
	else if (spec == 'X')
		len = change_from_hex_l(ap);
	else
		return (-1);
	return (len);
}

int	ft_putchar(char ch)
{
	int	i;

	i = write(1, &ch, 1);
	while (i == 0)
		write (1, &ch, 1);
	if (i == -1)
		return (-1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (*str)
	{
		i = ft_putchar(*str);
		sum += i;
		if (i == -1)
			return (-1);
		str++;
	}
	return (sum);
}
