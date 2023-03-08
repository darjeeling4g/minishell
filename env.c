
#include "minishell.h"

void	execute_env(char **envp)
{
	while (*envp)
	{
		if (ft_strchr(*envp, '=')) 
			printf("%s\n", *envp);
		envp++;
	}
	exit(0);
}