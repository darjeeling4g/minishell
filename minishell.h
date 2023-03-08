/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:46:30 by danpark           #+#    #+#             */
/*   Updated: 2023/03/08 20:53:13 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <sys/errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# define HRDC 0
# define APND 1
# define IN 2
# define OUT 3
# define SQ '\''
# define DQ '\"'
# define CLOSED 0
# define UNCLOSED 1

typedef struct s_token
{
	t_list	*txt;
	t_list	*rd;
}	t_token;

typedef struct s_rd
{
	int		type;
	char	*file;
}	t_rd;

typedef enum e_quote
{
	F_DQ,
	F_SQ,
	F_LT
}	t_quote;

//minishell.c
int		is_complete_command(char *input);
void	join_input(char **input, int flag);
t_list	*tokenizer(char *input);
t_token	*init_token(void);
void	add_text_struct(t_token *token, char **input);
void	add_redirection_struct(t_token *token, char **input);
char	**get_duplicate_envp(char **envp);

//minishell_utils.c
char	*ft_substrjoin(char *s1, char *s2, unsigned int s2_start, size_t s2_len);
size_t	ft_strlen_md(const char *s);

//get_txt.c
char	*get_txt(char **input);
char	*get_expanded_env(char **input, int *i);
char	*get_changed_double_quote(char **input, int *quote, char *txt);
char	*get_changed_single_quote(char **input, int *quote, char *txt);
char	*get_changed_string(char **input, char *txt);

//error_handler.
void	put_error_message(int errno);
void	free_array(char **arr, int idx);

//execute.c
void	interpret_token(t_list *tokens, char **envp);
void	parent_do(t_list *tokens, pid_t pid, int *fds[], char **envp);
void	execute_command(t_token *token, int (*fds)[2], int first, char **envp);
char	**combine_command(t_list *txt);
void	redirection(t_list *rds);
char	*get_env(t_list *envlst, const char *name);
char	*find_bin(char *arg, char **envp);

int	execute_pwd(char **envp);
#endif