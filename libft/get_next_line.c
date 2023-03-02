/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 13:16:39 by danpark           #+#    #+#             */
/*   Updated: 2022/12/02 22:45:47 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int		read_size;
	char	buff[BUFFER_SIZE];
	char	*read_line;
	int		i;

	i = 0;
	read_size = read(fd, buff, BUFFER_SIZE);
	read_line = read_next_line(buff, read_size, fd, i);
	return (read_line);
}

char	*read_next_line(char *buff, int read_size, int fd, int i)
{
	char		*read_line;
	static char	*backup;

	i = del_backup(&backup, &read_line, read_size, i);
	if (i == 1)
		return (0);
	else if (i == -1)
		return (read_line);
	if (read_size)
		backup = set_backup(backup, buff, read_size, INIT);
	while (backup[i] && backup[i] != '\n')
		i++;
	if (backup[i] == '\n')
	{
		read_line = ft_strjoin_md(0, backup, i + 1);
		backup = set_backup(backup, buff, read_size, BACKUP);
		return (read_line);
	}
	read_size = read(fd, buff, BUFFER_SIZE);
	i = del_backup(&backup, &read_line, read_size, 0);
	if (i == 1)
		return (0);
	else if (i == -1)
		return (read_line);
	return (read_next_line(buff, read_size, fd, i));
}

char	*set_backup(char *backup, char *buff, int read_size, int check)
{
	int		i;
	char	*temp;

	i = 0;
	if (check == INIT && backup)
	{
		temp = ft_strjoin_md(0, backup, ft_strlen_md(backup));
		free (backup);
		backup = ft_strjoin_md(temp, buff, read_size);
		free (temp);
	}
	else if (check == INIT && !backup)
		backup = ft_strjoin_md(0, buff, read_size);
	else
	{
		while (backup[i] && backup[i] != '\n')
			i++;
		temp = ft_strjoin_md(0, backup, ft_strlen_md(backup));
		free (backup);
		backup = ft_strjoin_md(0, &temp[i + 1], ft_strlen_md(temp) - i - 1);
		free (temp);
	}
	return (backup);
}

int	del_backup(char **backup, char **read_line, int read_size, int i)
{
	if (read_size < 0 || BUFFER_SIZE < 1 || (read_size == 0 && *backup == 0))
	{
		if (read_size < 0)
			free (*backup);
		*backup = NULL;
		return (1);
	}
	else if (read_size == 0 && *backup)
	{
		while ((*backup)[i] && (*backup)[i] != '\n')
			i++;
		if ((*backup)[i] == '\n')
		{
			*read_line = ft_strjoin_md(0, *backup, ++i);
			*backup = set_backup(*backup, 0, 0, BACKUP);
		}
		else
		{
			*read_line = ft_strjoin_md(0, *backup, ft_strlen_md(*backup));
			free(*backup);
			*backup = NULL;
		}
		return (-1);
	}
	return (0);
}
