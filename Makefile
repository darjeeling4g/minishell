# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danpark <danpark@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/01 18:47:25 by danpark           #+#    #+#              #
#    Updated: 2023/03/31 22:43:19 by danpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_M = minishell.c minishell_utils.c parser.c parser_utils.c get_txt.c \
		 error_handler.c execute.c execute_utils.c execute_utils2.c \
		 check_builtin.c check_syntax_error.c signal.c here_doc.c redirection.c \
		 echo.c cd.c pwd.c exit.c env.c export.c unset.c 
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
OBJS_M = ${SRCS_M:.c=.o}
NAME = minishell
CPPFLAGS = -I libft -I ~/goinfre/.brew/opt/readline/include
LDFLAGS = -L libft -L ~/goinfre/.brew/opt/readline/lib
LDLIBS = -lft -lreadline -lncurses

all : $(NAME)

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

re :
	make fclean
	make all

phony : all clean fclean re
