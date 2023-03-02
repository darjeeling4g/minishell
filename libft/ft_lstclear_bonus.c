/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 19:49:39 by danpark           #+#    #+#             */
/*   Updated: 2022/11/18 16:04:02 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;
	t_list	*tmp;

	if (!lst || !(*lst))
		return ;
	curr = (*lst);
	while (curr)
	{
		tmp = curr;
		curr = curr -> next;
		if (del)
			del(tmp -> content);
		free(tmp);
	}
	(*lst) = 0;
}
