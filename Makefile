# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danpark <danpark@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/01 18:47:25 by danpark           #+#    #+#              #
#    Updated: 2023/03/05 17:59:54 by danpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_M = minishell.c get_txt.c minishell_utils.c
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f
OBJS_M = ${SRCS_M:.c=.o}
NAME = minishell
CPPFLAGS = -I libft -I ~/goinfre/.brew/opt/readline/include
LDFLAGS = -L libft -L ~/goinfre/.brew/opt/readline/lib
LDLIBS = -lft -lreadline

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