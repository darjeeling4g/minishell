/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:49:46 by danpark           #+#    #+#             */
/*   Updated: 2023/03/05 20:17:23 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_complete_command(char *input)
{
	int	i;
	int	flag;

	i = -1;
	flag = 1;
	while (input[++i])
	{
		if (input[i] == DQ && flag == 1)
			flag = DQ;
		else if (input[i] == SQ && flag == 1)
			flag = SQ;
		else if (input[i] == DQ && flag == DQ)
			flag = 1;
		else if (input[i] == SQ && flag == SQ)
			flag = 1;
	}
	return (flag);
}

void	join_input(char **input, int flag)
{
	char	*tmp;
	char	*add_input;

    while (flag != 1)
    {
        rl_on_new_line();
        add_input = readline("> ");
        tmp = *input;
        *input = ft_strjoin(*input, "\n");
        free(tmp);
		tmp = *input;
        *input = ft_strjoin(*input, add_input);
        flag = is_complete_command(*input);
        printf("=>%d, %s\n", flag, *input);
        free (tmp);
        free (add_input);
    }
}

t_list	*tokenizer(char *input)
{
	t_list	*res;
	t_list	*new;
	t_token	*token;

	token = init_token();
	res = NULL;
	while (*input)
	{
		while (*input == ' ')
			input++;
		if (*input == '<' || *input == '>')
			add_redirection_struct(token, &input);
		else if (*input != '|')
			add_text_struct(token, &input);
		else if (*input == '|')
		{
			new = ft_lstnew(token);
			ft_lstadd_back(&res, new);
			token = init_token();
			input++;
		}
	}
	new = ft_lstnew(token);
	ft_lstadd_back(&res, new);
	return (res);
}

t_token	*init_token(void)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token) * 1);
	if (!token)
		exit(1);
	token->rd = 0;
	token->txt = 0;
	return (token);
}

void	add_text_struct(t_token *token, char **input)
{
	t_list	*new;
	char	*txt;

	txt = get_txt(input);
	new = ft_lstnew(txt);
	ft_lstadd_back(&token->txt, new);
}

void	add_redirection_struct(t_token *token, char **input)
{
	t_list	*new;
	t_rd	*rd;

	rd = (t_rd *)malloc(sizeof(t_rd) * 1);
	if (!rd)
		exit(1);
	if (**input == '<')
	{
		(*input)++;
		if (**input == '<')
		{
			rd->type = HRDC;
			(*input)++;
		}
		else
			rd->type = IN;
	}
	if (**input == '>')
	{
		(*input)++;
		if (**input == '>')
		{
			rd->type = APND;
			(*input)++;
		}
		else
			rd->type = OUT;
	}
	rd->file = get_txt(input);
	new = ft_lstnew(rd);
	ft_lstadd_back(&(token->rd), new);
}

int main(void)
{
    t_list  *p_lst;
	char	*input;
	int		flag;
	
	t_token	*token;
	t_list	*rd_lst;
	t_list	*txt;
	t_rd	*rd;

		input = "<< infile | cat | ls | grep 'print this'| >> outfile";
//    while ((input = readline("minishell$ ")) != NULL)
//	{
		flag = is_complete_command(input);
        join_input(&input, flag);
		// Do something with the user's input
        p_lst = tokenizer(input);//need to save pointer of the input!!!

		// test!!
		while (p_lst)
		{
			token = (t_token *)p_lst->content;
			rd_lst = (t_list *)token->rd;
			txt = (t_list *)token->txt;
			while (rd_lst)
			{
				rd = (t_rd *)rd_lst->content;	
				printf("type : %d, file : %s\n", rd->type, rd->file);
				rd_lst = rd_lst->next;
			}
			while (txt)
			{
				printf("txt : %s\n", (char *)txt->content);
				txt = txt->next;
			}
			p_lst = p_lst->next;
//		}

		// Add the input to the history
		add_history(input);
		// Free the memory allocated by readline()
//		free(input);
    }
    return 0;
}
