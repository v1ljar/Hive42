#include <unistd.h>  // write, chdir
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

int	execute_cmd(char *cmd, char *cmd_arg, char **envp);

int	main(int argc, char **argv, char **envp)
{
	static char	*cmd;
	static char	*cmd_arg;
	int			fd[2];

	if (argc == 1)
		return (write(2, "Enter arguments!\n", 17));
	if (!strcmp(argv[1], "cd"))
	{
		if (argc == 2 || argc > 3)
		{
			write(2, "error: cd: bad arguments\n", 25);
			return (1);
		}
		if (chdir(argv[2]))
		{
			write(2, "error: cd: cannot change directory to ", 38);
			int  i = 0;
			while (argv[2][i] != '\0')
				write(2, &argv[2][i++], 1);
			write(2, "\n", 1);
			return (1);
		}
	}
	if (argc == 2)
	{
		cmd = argv[1];
		return (execute_cmd(cmd, cmd_arg, envp));
	}
	return (0);
}

int	execute_cmd(char *cmd, char *cmd_arg, char **envp)
{
	execve(cmd, &cmd_arg, envp);
	write(1, "error: cannot execute ", 22);
	int i = 0;
	while (cmd[i] != '\0')
		write(1, &cmd[i++], 1);
	write(1, "\n", 1);
	return (1);
}