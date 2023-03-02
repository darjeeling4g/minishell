/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:18:17 by danpark           #+#    #+#             */
/*   Updated: 2022/11/18 14:44:37 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_one_sign(const char *str)
{
	int	sg_cnt;

	sg_cnt = 0;
	while (*str == '-' || *str == '+')
	{
		sg_cnt++;
		if (sg_cnt > 1)
			return (0);
		str++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	minus;
	int	res;

	i = 0;
	minus = 0;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (is_one_sign(&str[i]) && str[i] == '-')
		minus++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	else if (is_one_sign(&str[i]) == 0)
		return (0);
	while ('0' <= str[i] && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (minus == 1)
		res *= -1;
	return (res);
}
