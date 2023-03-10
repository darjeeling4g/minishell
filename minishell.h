/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:46:30 by danpark           #+#    #+#             */
/*   Updated: 2023/03/10 17:01:38 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <string.h>
# include <unistd.h>
# include <sys/errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "get_next_line.h" 
# define HRDC 0
# define APND 1 
# define IN 2
# define OUT 3
# define SQ '\''
# define DQ '\"'
# define CLOSED 0
# define UNCLOSED 1
# define EXIT 0
# define CONT 1

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
void	join_input(char **input, int flag);
int		is_complete_command(char *input);

//minishell_utils.c
char	*ft_substrjoin(char *s1, char *s2, unsigned int s2_start, size_t s2_len);
//size_t	ft_strlen_md(const char *s);
char	**list_to_array(t_list *lst);
t_list	*array_to_list(char **arr);

//parser.c
t_list	*tokenizer(char *input);
t_token	*init_token(void);
void	add_text_struct(t_token *token, char **input);
void	add_redirection_struct(t_token *token, char **input);

//get_txt.c
char	*get_txt(char **input);
char	*get_expanded_env(char **input, int *i);
char	*get_changed_double_quote(char **input, int *quote, char *txt);
char	*get_changed_single_quote(char **input, int *quote, char *txt);
char	*get_changed_string(char **input, char *txt);

//error_handler.c
void	put_error_message(int type);
void	free_array(char **arr, int idx);

//execute.c
void	interpret_token(t_list *tokens, t_list *e_lst); 
void	parent_do(t_list *tokens, pid_t pid, int (*fds)[2], t_list *e_lst);
void	execute_command(t_list *tokens, int (*fds)[2], int first, t_list *e_lst);

//execute_utils.c
char	*get_env(t_list *e_lst, const char *name);
char	*find_bin(char *arg, char **envp);
void	redirection(t_list *rds);
void	get_here_doc_input(t_rd *rd);

//check_builtin.c
int		is_builtin(t_list *cmdlst);
void	execute_builtin_command(t_token *token, t_list *e_lst);
int		is_valid_name(char *name);

//builtins.c
int		execute_echo(char **cmd);
int		execute_cd(char **cmd, t_list *e_lst);
int		execute_pwd(t_list *e_lst);
void	execute_exit(void);

//builtins_env.c
int		execute_env(t_list *e_lst);
int		execute_export(char** cmd, t_list *e_lst);
int		execute_unset(char **cmd, t_list *e_lst);
void	print_sorted_envp(t_list *e_lst);
t_list	*get_env_node(char *name, t_list *e_lst);

#endif
