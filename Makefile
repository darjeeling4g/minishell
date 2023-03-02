# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danpark <danpark@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/01 18:47:25 by danpark           #+#    #+#              #
#    Updated: 2023/03/02 15:26:24 by danpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_M = minishell.c
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
OBJS_M = ${SRCS_M:.c=.o}
NAME = minishell
CPPFLAG = -I libft -I ~/goinfre/.brew/opt/readline/include
LDFLAG = -L libft -L ~/goinfre/.brew/opt/readline/lib
LDLIBS = -lft -lreadline

all = $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $(CPPFLAG) -c $< -o $@

$(NAME) : $(OBJS_M)
	make -C libft
	$(CC) $(CFLAGS) $(LDFLAG) $(LDLIBS) $^ -o $@

