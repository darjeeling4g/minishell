/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:49:46 by danpark           #+#    #+#             */
/*   Updated: 2023/03/30 13:56:40 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	g_exit_code = 0;

void	set_input_mode(int flag)
{
	struct termios	termattr;

	tcgetattr(STDOUT_FILENO, &termattr);
	if (flag == PARENT)
		termattr.c_lflag &= ~ECHOCTL;
	else
		termattr.c_lflag |= ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW, &termattr);
}

void	set_initial_minishell(int argc, char **argv)
{
	set_input_mode(PARENT);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	(void)argc;
	(void)argv;
}

t_list	*get_environment_list(char **envp)
{
	t_list	*e_lst;

	e_lst = array_to_list(envp);
	if (!get_env_node("OLDPWD", e_lst))
		ft_lstadd_back(&e_lst, ft_lstnew(ft_strdup("OLDPWD")));
	return (e_lst);
}

void	minishell(t_list *e_lst)
{
	t_list	*tokens;
	char	*input;
	int		flag;

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
			if (tokens != NULL)
				if (check_token_syntax(tokens) == TRUE)
					interpret_token(tokens, e_lst);
		}
		set_input_mode(PARENT);
		signal(SIGINT, signal_handler);
		input = readline("minishell$ ");
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*e_lst;

	set_initial_minishell(argc, argv);
	e_lst = get_environment_list(envp);
	minishell(e_lst);
	exit(0);
}
