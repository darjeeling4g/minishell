#include "minishell.h"

int	execute_pwd(t_token *token)
{
	char cwd[1024];
	
	if (getcwd(cwd, sizeof(cwd)) != NULL) 
		ft_printf(cwd);
	else
		put_error_message(errno);
	return (0);
}