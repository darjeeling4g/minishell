/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:46:30 by danpark           #+#    #+#             */
/*   Updated: 2023/03/28 17:05:59 by siyang           ###   ########.fr       */
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
	int type;
	char *file;
} t_rd;

typedef enum e_quote
{
	F_DQ,
	F_SQ,
	F_LT
} t_quote;

// minishell.c
void save_input_mode(struct termios *org_term);
void set_input_mode(struct termios *new_term);
void reset_input_mode(struct termios *org_term);
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
void	add_redirection_struct(t_token *token, char **input, t_list *e_lst);
void	handle_redirection_error(char **input);

// get_txt.c
char	*get_txt(char **input, t_list *e_lst);
char	*get_expanded_env(char **input, int *i, t_list *e_lst);
char	*get_changed_double_quote(char **input, int *quote, char *txt, t_list *e_lst);
char	*get_changed_single_quote(char **input, int *quote, char *txt);
char	*get_changed_string(char **input, char *txt, t_list *e_lst);

// error_handler.c
int		put_error_message(unsigned char code, char *cmd);
int		put_customized_error_message(unsigned char code, char *cmd, char *custom);
void	free_array(char **arr, int idx);

// execute.c
void interpret_token(t_list *tokens, t_list *e_lst, struct termios *termattr);
void parent_do(t_list *tokens, pid_t pid, int (*fds)[2], t_list *e_lst, struct termios *termattr);
void execute_command(t_list *tokens, int (*fds)[2], int first, t_list *e_lst, struct termios *termattr);

// execute_utils.c
char	*get_env(t_list *e_lst, const char *name);
char	*find_bin(char *arg, char **envp);
int		redirection(t_list *rds, int std[2]);
int		is_vaild_file(char *filename);
void	get_here_doc_input(t_rd *rd, int std[2]);

// check_builtin.c
int is_builtin(t_list *cmdlst);
void execute_builtin_command(t_token *token, t_list *e_lst, int parent);
int is_valid_name(char *name);

// builtins.c
int		execute_echo(char **cmd);
int 	execute_cd(char **cmd, t_list *e_lst);
int 	execute_pwd(t_list *e_lst);
void	execute_exit(t_token *token);

// builtins_env.c
int execute_env(t_list *e_lst);
int execute_export(char **cmd, t_list *e_lst);
int execute_unset(char **cmd, t_list *e_lst);
void print_sorted_envp(t_list *e_lst);
t_list *get_env_node(char *name, t_list *e_lst);

#endif
