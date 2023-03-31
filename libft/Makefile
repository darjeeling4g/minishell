# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danpark <danpark@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/18 12:06:19 by danpark           #+#    #+#              #
#    Updated: 2023/03/31 17:34:22 by danpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_M = ft_isalpha.c ft_atoi.c ft_bzero.c ft_calloc.c ft_isdigit.c ft_isalnum.c\
		 ft_isascii.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c\
		 ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
		 ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c\
		 ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c\
    	 ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c\
		 ft_tolower.c ft_toupper.c ft_printf.c change_to_str1.c\
		 change_to_str2.c change_to_str3.c get_next_line.c get_next_line_utils.c
SRCS_B = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c\
		 ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c\
		 ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
OBJS_M = ${SRCS_M:.c=.o}
OBJS_B = ${SRCS_B:.c=.o}
INCS = libft.h
LIBC = ar rc
NAME = libft.a

ifdef BONUS
	OBJS = $(OBJS_B) $(OBJS_M)
else
    OBJS = $(OBJS_M)
endif

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCS)

$(NAME) : $(OBJS)
	$(LIBC) $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS_B) $(OBJS_M)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus:
	make BONUS=1 all
	
.PHONY : clean fclean re all bonus