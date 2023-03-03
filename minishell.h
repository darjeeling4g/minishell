/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:46:30 by danpark           #+#    #+#             */
/*   Updated: 2023/03/03 21:51:02 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
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
	struct s_txt	**txt;
	struct s_rd		**rd;
}	t_token;

typedef struct s_txt
{
	char	*str;
}	t_txt;

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

#endif