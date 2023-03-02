/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:32:25 by danpark           #+#    #+#             */
/*   Updated: 2022/12/06 13:07:08 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# define INIT 0
# define BACKUP 1

char	*get_next_line(int fd);
char	*read_next_line(char *buff, int read_size, int fd, int i);
char	*set_backup(char *backup, char *buff, int read_size, int check);
int		del_backup(char **backup, char **read_line, int read_size, int i);
size_t	ft_strlen_md(const char *s);
char	*ft_strjoin_md(char const *s1, char const *s2, int len);
#endif