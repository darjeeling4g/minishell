/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:49:46 by danpark           #+#    #+#             */
/*   Updated: 2023/03/31 18:02:43 by danpark          ###   ########.fr       */
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

	input = readline("minishell$ ");
	while (input != NULL)
	{
		tokens = NULL;
		signal(SIGINT, SIG_IGN);
		if (*input)
		{
			join_input(&input, is_complete_command(input));
			tokens = tokenizer(input, e_lst);
			add_history(input);
			if (tokens != NULL)
				if (check_token_syntax(tokens) == TRUE)
					interpret_token(tokens, e_lst);
		}
		free(input);
		set_input_mode(PARENT);
		signal(SIGINT, signal_handler);
		if (tokens)
			free_token_list(tokens);
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
