/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:32:24 by siyang            #+#    #+#             */
/*   Updated: 2023/03/08 20:19:07 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_export(char** cmd, char ***envp)
{
	// if (!argv[1])
		// print sorted envp
	// else
		// while(argv)
		// 	if (check_valid_cmd())
			//	error;
		//	if (already exist env())	
			// free prev_env
			// add new env
		//	else
			//	malloc envp_size + 1
			//	copy prev_envp to new envp
			//	add new env
			//	free prev_envp
	int		index;
	int		size;
	char	**tmp;
	char	*new;

	cmd++;
	if (*cmd)
		print_sorted_envp();
	else
	{
		while (cmd)
		{
			if (check_valid_cmd(cmd))
				put_error_message(errno);
			index = check_exist_env(cmd, *envp);
			if (index)
			{
				free(envp[index]);
				new = ft_strdup(*cmd);
				if (!new)
					put_error_message(errno);
				envp[index] = new;
			}
			else
			{
				size = 0;
				while ((*envp)[size])
					size++;	
				tmp = malloc(sizeof(char *) * (size + 1));
				while ()
				{

				}
			}
			cmd++;
		}
	}
	exit(0);
}

void	print_sort_envp()
{

}

int	check_valid_cmd(char **cmd)
{
	// check first char : alpa
	// after first char : alnum
}

int	check_exist_env(char **cmd, char **envp)
{

}