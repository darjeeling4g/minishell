

void get_readline_input(struct termios *termattr[2])
{
	char	ch;
	int	idx;

	ch = 0;
	idx = -1;
	save_input_mode(termattr[ORG]);
	set_input_mode(termattr[NEW]);
	while (read(0, &ch, 1) > 0)
	{
		if (ch == 4)
		{
			if (idx == -1)
				exit(0);
			else
				return ;
		}
		else if (ch == 127)
		{
			if (idx >= 0)
			{
				--idx;
				write(0, "\b \b", 3);
			}
		}
		else if (ch == '\n')
			break ;
		else
		{
			++idx;
			write(0, &ch, 1);
			write()
		}
		ch = 0;
	}
	reset_input_mode(termattr[ORG]);
}

int main(int argc, char **argv, char **envp)
{
	t_list			*p_lst;
	t_list			*e_lst;
	char			*input;
	int				flag;
	struct termios	termattr[2];

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	(void)argc;
	(void)argv;
	e_lst = array_to_list(envp);
	// input = readline("minishell$ ");
	// while (input != NULL)
	// {
	// 	if (*input)
	// 	{
	// 		flag = is_complete_command(input);
	// 		join_input(&input, flag);
	// 		p_lst = tokenizer(input, e_lst);
	// 		add_history(input);
	// 		free(input);
	// 		interpret_token(p_lst, e_lst, &termattr[ORG]);
	// 	}
	// 	set_input_mode(&termattr[NEW]);
	// 	input = readline("minishell$ ");
	// }
	while (1)
	{
		get_readline_input(&termattr);
		ft_putstr_fd("minishell$ ", 1);

		
	}
	return (0);
}