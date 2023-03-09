/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:49:46 by danpark           #+#    #+#             */
/*   Updated: 2023/03/10 00:17:53 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    t_list  *p_lst;
	t_list	*e_lst;
	char	*input;
	int		flag;
	
	// t_token	*token;
	// t_list	*rd_lst;
	// t_list	*txt;
	// t_rd	*rd;
	(void)argc;
	(void)argv;
	e_lst = array_to_list(envp);
//	input = "<";
	while ((input = readline("minishell$ ")) != NULL)
	{
		if (*input)
		{
			flag = is_complete_command(input);
			join_input(&input, flag);
			// // Do something with the user's input
			p_lst = tokenizer(input);//need to save pointer of the input!!!
			
			//test!!
			// while (p_lst)
			// {
			// 	token = (t_token *)p_lst->content;
			// 	rd_lst = (t_list *)token->rd;
			// 	txt = (t_list *)token->txt;
			// 	while (rd_lst)
			// 	{
			// 		rd = (t_rd *)rd_lst->content;	
			// 		printf("type : %d, file : %s\n", rd->type, rd->file);
			// 		rd_lst = rd_lst->next;
			// 	}
			// 	while (txt)
			// 	{
			// 		printf("txt : %s\n", (char *)txt->content);
			// 		txt = txt->next;
			// 	}
			// 	printf("==========pipe========\n");
			// 	p_lst = p_lst->next;
			// }
			// Add the input to the history
			add_history(input);
			// Free the memory allocated by readline()
			free(input);
			interpret_token(p_lst, e_lst);
		}
    }
    return 0;
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