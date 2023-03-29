/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:46:30 by danpark           #+#    #+#             */
/*   Updated: 2023/03/30 03:35:22 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#include <string.h>
#include <unistd.h>
#include <sys/errno.h>
#include <signal.h>
#include <term.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "get_next_line.h"
#define HRDC 0
#define APND 1
#define IN 2
#define OUT 3
#define SQ '\''
#define DQ '\"'
#define CLOSED 0
#define UNCLOSED 1
#define ORG 0
#define NEW 1
#define CHILD 0
#define PARENT 1
#define SUCCESS 0
#define FAIL -1

extern unsigned char	g_exit_code;

typedef struct s_token
{
	t_list *txt;
	t_list *rd;
} t_token;

typedef struct s_rd
{
	int		type;
	char	*file;
	int		read;
} t_rd;

typedef enum e_quote
{
	F_DQ,
	F_SQ,
	F_LT
} t_quote;

// minishell.c
void set_input_mode(int flag);
void join_input(char **input, int flag);
int is_complete_command(char *input);

// minishell_utils.c
char *ft_substrjoin(char *s1, char *s2, unsigned int s2_start, size_t s2_len);
// size_t	ft_strlen_md(const char *s);
char **list_to_array(t_list *lst);
t_list *array_to_list(char **arr);

// parser.c
t_list	*tokenizer(char *input, t_list *e_lst);
t_token	*init_token(void);
void	add_text_struct(t_token *token, char **input, t_list *e_lst);
int		add_redirection_struct(t_token *token, char **input, t_list *e_lst);
void	handle_redirection_error(char **input);

// get_txt.c
char	*get_txt(char **input, t_list *e_lst);
char	*get_expanded_env(char **input, int *i, t_list *e_lst, int plain);
char	*get_changed_double_quote(char **input, int *quote, char *txt, t_list *e_lst);
char	*get_changed_single_quote(char **input, int *quote, char *txt);
char	*get_changed_string(char **input, char *txt, t_list *e_lst);

// error_handler.c
int		put_error_message(unsigned char code, char *cmd);
int		put_customized_error_message(unsigned char code, char *cmd, char *custom);
void	free_array(char **arr, int idx);
void	free_token_list(t_list *tokens);
void	delete_list_content(void *content);

// execute.c
void	interpret_token(t_list *tokens, t_list *e_lst);
void	parent_do(t_list *tokens, pid_t pid, int (*fds)[2], t_list *e_lst);
void	execute_command(t_list *tokens, int (*fds)[2], int first, t_list *e_lst);

// execute_utils.c
char	*get_env(t_list *e_lst, const char *name);
char	*find_bin(char *arg, char **envp);
int		redirection(t_list *rds);
int		is_vaild_file(char *filename);
void	get_here_doc_input(t_list *rds);
void	close_here_doc_pipe(t_list *rds);

// check_builtin.c
int		is_builtin(t_list *cmdlst);
void	execute_builtin_command(t_token *token, t_list *e_lst, int parent);
int		is_valid_name(char *name);

// builtins.c
void	execute_echo(char **cmd);
void	execute_cd(char **cmd, t_list *e_lst);
void	execute_pwd(void);
void	execute_exit(t_token *token);

// builtins_env.c
void	execute_env(t_list *e_lst);
void	execute_export(char **cmd, t_list *e_lst);
void	execute_unset(char **cmd, t_list *e_lst);
void	sort_n_print(t_list *e_lst);
void	print_sorted_envp(char **arr);
t_list *get_env_node(char *name, t_list *e_lst);

// check_syntax_error.c
int	is_valid_filename(char *input);

int		count_contained_redirection(char *str);
int		is_valid_redirection_token_syntax(char *str);
void	put_redirection_syntax_error_message(char *str);
char	*get_syntax_error_message(char *str);

#endif
