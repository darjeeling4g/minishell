/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:49:46 by danpark           #+#    #+#             */
/*   Updated: 2023/03/05 14:57:46 by danpark          ###   ########.fr       */
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

	while (*input)
	{
		add_redirection_struct(token, &input);
		add_text_struct();
		if (*input == '|')
		{
			new = ft_lstnew(&token);
			ft_lstadd_back(&res, new);
		}
		input++;
	}
	new = ft_lstnew(&token);
	ft_lstadd_back(&res, new);
	return (res);
}

void	add_redirection_struct(t_token *token, char **input)
{
	t_rd	*rd;

	rd = malloc(sizeof(t_rd) * 1);
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
}

void	add_text_struct(t_token *token, char *input, int i)
{
	if (**input == SQ)
}

int main(void)
{
    t_list  *p_lst;
	char	*input;
	int		flag;

    while ((input = readline("minishell$ ")) != NULL)
	{
		flag = is_complete_command(input);
        join_input(&input, flag);
		// Do something with the user's input
        p_lst = tokenizer(input);

		// Add the input to the history
		add_history(input);

		// Free the memory allocated by readline()
		free(input);
    }

    return 0;
}
