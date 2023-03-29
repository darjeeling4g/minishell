# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danpark <danpark@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/01 18:47:25 by danpark           #+#    #+#              #
#    Updated: 2023/03/29 18:12:54 by danpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_M = minishell.c minishell_utils.c parser.c get_txt.c error_handler.c \
		 execute.c execute_utils.c check_builtin.c builtins.c builtins_env.c\
		 check_syntax_error.c
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f
OBJS_M = ${SRCS_M:.c=.o}
NAME = minishell
CPPFLAGS = -I libft -I ~/goinfre/.brew/opt/readline/include
LDFLAGS = -L libft -L ~/goinfre/.brew/opt/readline/lib
LDLIBS = -lft -lreadline -lncurses

all = $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME) : $(OBJS_M)
	make bonus -C libft
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $^ -o $@

clean : 
	$(MAKE) fclean -C libft
	$(RM) $(OBJS_M)

fclean :
	$(MAKE) clean
	$(RM) $(NAME)