/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:32:23 by danpark           #+#    #+#             */
/*   Updated: 2023/03/05 20:17:25 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lstnew_token(t_rd *rd, char *txt)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token) * 1);
	if (!token)
		eixt(1);
	token->rd = rd;
	token->txt = txt;
	token->next = 0;
	return (token);
}

void	*tokenlst_add_back(t_token **head, t_token *token)
{
	t_token	*tmp;

	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = token;
}

t_rd	*lstnew_rd(int type, char *file)
{
	t_rd	*rd;

	rd = (t_rd *)malloc(sizeof(t_rd) * 1);
	if (!rd)
		exit(1);
	rd->type = type;
	rd->file = file;
	rd->next = 0;
	return (rd);
}

void	rdlst_add_back(t_rd **head, t_rd *rd)
{
	t_rd *tmp;

	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = rd;
}

t_txt	*lstnew_txt(char *content)
{
	t_txt	*txt;

	txt = (t_txt *)malloc(sizeof(t_txt) * 1);
	if (!txt)
		exit(1);
	txt->txt = contet;
	txt->next = 0;
	return (txt);
}

void	rdlst_add_back(t_rd **head, t_txt *txt)
{
	t_txt *tmp;

	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = txt;
}