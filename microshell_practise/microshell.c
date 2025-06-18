#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

void	execute_cmd(char **argv, int i, int *tmp_fd, char **envp);
void	execute_pipe(char **argv, int i, int *tmp_fd, char **envp, int fd[]);
void	execute(char **argv, int i, int tmp_fd, char **envp);
void	change_dir(char **argv, int i);
void	print_msg(char *msg, char *cmd);

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	tmp_fd;

	(void)argc;
	tmp_fd = dup(0);
	argv++;
	while (*argv)
	{
		int i = 0;
		while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
			i++;
		if (i > 0 && !strcmp(argv[0], "cd"))
			change_dir(argv, i);
		else if (i > 0 && (argv[i] == NULL || !strcmp(argv[i], ";")))
			execute_cmd(argv, i, &tmp_fd, envp);
		else if (i > 0 && !strcmp(argv[i], "|"))
			execute_pipe(argv, i, &tmp_fd, envp, fd);
		if (argv[i])
			argv = &argv[i + 1];
		else
			break;
	}
	close(tmp_fd);
	return (0);
}

void	execute_cmd(char **argv, int i, int *tmp_fd, char **envp)
{
	if (fork() == 0)
		execute(argv, i, *tmp_fd, envp);
	else
	{
		close(*tmp_fd);
		while (waitpid(-1, NULL, WUNTRACED) != -1);
		*tmp_fd =  dup(0);
	}
}

void	execute_pipe(char **argv, int i, int *tmp_fd, char **envp, int fd[])
{
	pipe(fd);
	if (fork() == 0)
	{
		dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]);
		execute(argv, i, *tmp_fd, envp);
	}
	else
	{
		close(fd[1]);
		close(*tmp_fd);
		*tmp_fd = fd[0];
	}
}

void	execute(char **argv, int i, int tmp_fd, char **envp)
{
	argv[i] = NULL;
	dup2(tmp_fd, 0);
	close(tmp_fd);
	execve(argv[0], argv, envp);
	print_msg("error: cannot execute ", argv[0]);
	exit(1);
}

void	change_dir(char **argv, int i)
{
	if (i != 2)
		return (print_msg("error: cd: bad arguments", NULL));
	if (chdir(argv[1]) != 0)
		print_msg("error: cd: cannot change directory to ", argv[1]);
}

void	print_msg(char *msg, char *cmd)
{
	while (*msg)
		write(2, msg++, 1);
	if (cmd)
		while (*cmd)
			write(2, cmd++, 1);
	write(2, "\n", 1);
}
