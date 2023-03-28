/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:49:46 by danpark           #+#    #+#             */
/*   Updated: 2023/03/28 17:03:27 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	g_exit_code = 0;

void save_input_mode(struct termios *org_term)
{
	tcgetattr(STDOUT_FILENO, org_term);
}

void set_input_mode(struct termios *new_term)
{
	tcgetattr(STDOUT_FILENO, new_term);
	new_term->c_lflag &= ~(ICANON | ECHOCTL);
	// new_term->c_cc[VMIN] = 1;
	// new_term->c_cc[VTIME] = 0;
	tcsetattr(STDOUT_FILENO, TCSANOW, new_term);
}

void reset_input_mode(struct termios *org_term)
{
	tcsetattr(STDOUT_FILENO, TCSANOW, org_term);
}

void signal_handler(int sig)
{
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
	t_list			*p_lst;
	t_list			*e_lst;
	char			*input;
	int				flag;
	struct termios	termattr[2];

	save_input_mode(&termattr[ORG]);
	set_input_mode(&termattr[NEW]);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	(void)argc;
	(void)argv;
	e_lst = array_to_list(envp);
	input = readline("minishell$ ");
	while (input != NULL)
	{
		if (*input)
		{
			flag = is_complete_command(input);
			join_input(&input, flag);
			p_lst = tokenizer(input, e_lst);
			add_history(input);
			free(input);
			interpret_token(p_lst, e_lst, &termattr[ORG]);
		}
		set_input_mode(&termattr[NEW]);
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
