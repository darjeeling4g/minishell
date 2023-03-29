/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:49:46 by danpark           #+#    #+#             */
/*   Updated: 2023/03/30 03:55:58 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	g_exit_code = 0;

void set_input_mode(int flag)
{
	struct termios	termattr;

	tcgetattr(STDOUT_FILENO, &termattr);
	if (flag == PARENT)
		termattr.c_lflag &= ~ECHOCTL;
	else
		termattr.c_lflag |= ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW, &termattr);
}

void signal_handler(int sig)
{
	g_exit_code = 1;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

int main(int argc, char **argv, char **envp)
{
	t_list			*tokens;
	t_list			*e_lst;
	char			*input;
	int				flag;

	set_input_mode(PARENT);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	(void)argc;
	(void)argv;
	e_lst = array_to_list(envp);
	input = readline("minishell$ ");
	while (input != NULL)
	{
		signal(SIGINT, SIG_IGN);
		if (*input)
		{
			flag = is_complete_command(input);
			join_input(&input, flag);
			tokens = tokenizer(input, e_lst);
			add_history(input);
			free(input);
			// if (check_token_syntax())
			if (tokens != NULL)
				interpret_token(tokens, e_lst);
		}
		set_input_mode(PARENT);
		signal(SIGINT, signal_handler);
		input = readline("minishell$ ");
	}
	return (0);
}


void join_input(char **input, int flag)
{
	char *tmp;
	char *add_input;

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
		free(tmp);
		free(add_input);
	}
}

int is_complete_command(char *input)
{
	int i;
	int flag;

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
