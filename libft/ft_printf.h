/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 20:33:55 by danpark           #+#    #+#             */
/*   Updated: 2023/02/07 20:03:03 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "libft.h"

int				ft_printf(const char *format, ...);
void			get_converted_value(const char *format, va_list ap, int *sum);
int				put_argument(char spec, va_list ap);
int				ft_putchar(char ch);
int				ft_putstr(char *str);
int				change_from_char(va_list ap);
int				change_from_str(va_list ap);
int				change_from_dec(va_list ap);
int				change_from_int(va_list ap);
int				change_from_pct(void);
int				change_from_ptr(va_list ap);
int				change_from_hex_s(va_list ap);
int				change_from_hex_l(va_list ap);
int				change_from_uint(va_list ap);
unsigned int	ft_numlen_base(size_t num, unsigned int base);

#endif