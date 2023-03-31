/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:46:30 by danpark           #+#    #+#             */
/*   Updated: 2023/03/31 22:40:19 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <string.h>
# include <unistd.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <term.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
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
# define ORG 0
# define NEW 1
# define CHILD 0
# define PARENT 1
# define SUCCESS 0
# define FAIL -1

extern unsigned char	g_exit_code;

typedef struct s_token
{
	t_list	*txt;
	t_list	*rd;
}	t_token;

typedef struct s_rd
{
	int		type;
	char	*file;
	int		read;
}	t_rd;

typedef enum e_quote
{
	F_DQ,
	F_SQ,
	F_LT
}	t_quote;

// minishell.c
void	set_initial_minishell(int argc, char **argv);
t_list	*get_environment_list(char **envp);
void	minishell(t_list *e_lst);
void	set_input_mode(int flag);

// signal.c
void	signal_handler(int sig);
void	set_child_exit_status(t_list *tokens);

// minishell_utils.c
char	*ft_substrjoin(char *s1, char *s2, unsigned int s2_start, \
size_t s2_len);
char	**list_to_array(t_list *lst);
t_list	*array_to_list(char **arr);
void	join_input(char **input, int flag);
int		is_complete_command(char *input);

// parser.c
t_list	*tokenizer(char *input, t_list *e_lst);
void	add_text_struct(t_token *token, char **input, t_list *e_lst);
int		add_redirection_struct(t_token *token, char **input, t_list *e_lst);
int		add_token_content(char **input, t_list *e_lst, t_list *tokens, \
t_token *token);
void	add_rd_type(t_rd *rd, char **input);

// parser_utils.c
t_token	*init_token(void);

// get_txt.c
char	*get_txt(char **input, t_list *e_lst);
char	*get_expanded_env(char **input, int *i, t_list *e_lst, int plain);
char	*get_changed_double_quote(char **input, int quote, char *txt, \
t_list *e_lst);
char	*get_changed_single_quote(char **input, int quote, char *txt);
char	*get_changed_string(char **input, char *txt, t_list *e_lst, int start);

// error_handler.c
int		put_error_message(unsigned char code, char *cmd);
int		put_customized_error_message(unsigned char code, char *cmd, \
char *custom);
void	free_array(char **arr, int idx);
void	free_token_list(t_list *tokens);
void	delete_list_content(void *content);

// execute.c
void	interpret_token(t_list *tokens, t_list *e_lst);
void	parent_do(t_list *tokens, int (*fds)[2], t_list *e_lst);
void	execute_command(t_list *tokens, int (*fds)[2], int first, \
t_list *e_lst);
void	creat_exe_process(t_list *tokens, int (*fds)[2], t_list *e_lst);
void	change_stream(t_list *tokens, int (*fds)[2], int first);

// execute_utils.c
char	*get_env(t_list *e_lst, const char *name);
char	*find_bin(char *arg, char **envp);
char	*get_complete_path(char *arg, char *path_group);
int		is_vaild_file(char *filename);

// execute_utils2.c
int		is_a_directory(char *path);
void	handle_execute_fail(t_list *e_lst, char *cmd);

// here_doc.c
int		creat_here_doc_fd(t_list *rds, int cnt);
char	*get_here_doc_input(t_rd *rd);
void	close_here_doc_fd(t_list *rds);
int		handle_here_doc_process(pid_t pid, int *fds, t_rd *rd);

// redirection.c
int		redirection(t_list *rds);
int		set_input_fd(t_rd *rd);
int		set_output_fd(t_rd *rd);

// check_builtin.c
int		is_builtin(t_list *cmdlst);
void	execute_builtin_command(t_token *token, t_list *e_lst);
void	parent_execute_command(t_token *token, t_list *e_lst);
int		is_valid_name(char *name);

// builtins.c
void	execute_cd(char **cmd, t_list *e_lst);
void	execute_pwd(void);
void	execute_exit(t_token *token);

// check_syntax_error.c
int		is_valid_filename(char *input);
int		check_token_syntax(t_list *tokens);
int		is_exist_filename(t_token *token);

// echo.c
void	execute_echo(char **cmd);
int		count_exist_option(char **cmd);

// cd.c
void	execute_cd(char **cmd, t_list *e_lst);
void	set_pwd(t_list *e_lst, char *path, char **cmd);
void	change_old_pwd(t_list *old_pwd, char *tmp);
void	change_pwd(t_list *pwd);

// pwd.c
void	execute_pwd(void);

// exit.c
void	execute_exit(t_token *token);
void	check_exit_error(char *exitcode, t_list *txt);
// env.c
void	execute_env(t_list *e_lst);

// export.c
void	execute_export(char **cmd, t_list *e_lst);
void	update_env_list(char *env, char *cmd, t_list *e_lst);
void	sort_n_print(t_list *e_lst);
void	sort_envp(int i, int j, char **arr);
void	print_sorted_envp(char **arr);

// unset.c
void	execute_unset(char **cmd, t_list *e_lst);
t_list	*get_env_node(char *name, t_list *e_lst);

#endif
