/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpark <danpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:20:50 by danpark           #+#    #+#             */
/*   Updated: 2022/11/23 17:13:25 by danpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_str(char const *s, char c)
{
	int	cnt;
	int	i;

	cnt = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
			cnt++;
		while (s[i] != c && s[i])
			i++;
	}
	return (cnt);
}

static char	*get_str(const char *s, char c, size_t index)
{
	char	*str;
	size_t	size;
	size_t	i;

	size = 0;
	i = index;
	while (s[i] && s[i] != c)
	{
		size++;
		i++;
	}
	str = 0;
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (0);
	str[size] = '\0';
	i = 0;
	while (i < size)
		str[i++] = s[index++];
	return (str);
}

static char	**ft_free(char **tab, size_t i)
{
	while (i-- > 0)
		free(tab[i]);
	free(tab);
	return (0);
}

static char	**get_tab(char **tab, char const *s, char c, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < size)
	{
		while (s[j] == c && s[j])
			j++;
		tab[i] = get_str(s, c, j);
		if (!tab[i])
			return (ft_free(tab, i));
		while (s[j] != c && s[j])
			j++;
		i++;
	}
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	size;

	if (!s)
		size = 0;
	else
		size = count_str(s, c);
	tab = (char **)malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (0);
	tab[size] = 0;
	return (get_tab(tab, s, c, size));
}
