#include "minishell.h"

int	execute_pwd(char **envp)
{
	char	*pwd;

	pwd = get_env(envp, "PWD");
	if (pwd != NULL)
		ft_printf("%s\n", pwd);
	else
		return (-1);
	exit(0);
}