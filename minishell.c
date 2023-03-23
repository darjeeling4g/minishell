/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:49:46 by danpark           #+#    #+#             */
/*   Updated: 2023/03/23 18:47:55 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		//rl_point = rl_end - 2;
		printf("\n");
		rl_on_new_line();
		// rl_replace_line("", 1);
		rl_redisplay();
	}
}

void    init_rl_catch_signals(void)
{
    extern int  rl_catch_signals;
    rl_catch_signals = 0;
}

int main(int argc, char **argv, char **envp)
{
	t_list	*p_lst;
	t_list	*e_lst;
	char	*input;
	int		flag;
	
	// t_token	*token;
	// t_list	*rd_lst;
	// t_list	*txt;
	// t_rd	*rd;
	init_rl_catch_signals();
	signal(SIGINT, sigint_handler);
	write(2, "signal execute\n", 20);
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
			p_lst = tokenizer(input);
			
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
