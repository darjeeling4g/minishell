/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:59:51 by danpark           #+#    #+#             */
/*   Updated: 2022/11/18 16:03:55 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*curr;

	if (lst == 0)
		return ;
	if (!(*lst) && !new)
		return ;
	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	curr = (*lst);
	while (curr -> next)
		curr = curr -> next;
	curr -> next = new;
}
