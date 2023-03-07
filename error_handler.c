/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:38:13 by danpark           #+#    #+#             */
/*   Updated: 2023/03/06 18:42:40 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_error_message(int errno)
{
	char	*errorstr;
	errorstr = strerror(errno);
	ft_putendl_fd(errorstr, 2);
	exit(1);
}