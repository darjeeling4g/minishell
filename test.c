#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void	execute_echo(char **cmd)
{
	int	option;

	option = 0;
	cmd++;
	if (!*cmd)
	{
		printf("\n");
		return ;
	}
	if (strlen(*cmd) == strlen("-n") && \
	strncmp("-n", *cmd, strlen(*cmd)) == 0)
	{
		cmd++;
		option = 1;
	}
	while (*cmd)
	{
		printf("%s", *cmd);
		cmd++;
		if (*cmd)
			printf(" ");
		else if (!option)
			printf("\n");
	}
	exit(1);
}

int main(int ac, char **str)
{
	execute_echo(str);
}