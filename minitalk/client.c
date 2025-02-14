#include "./libft/libft.h"
#include <signal.h>

int	main(int argc, char *argv[])
{
	int		pid;
	char	*str;
	int		sigset;
	sigset_t	set;

	if (argc != 3)
		exit(ft_printf("Client program requires 2 arguments! PID and message string\n"));
	pid = ft_atoi(argv[1]);
	str = argv[2];
	sigset = sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	ft_printf("PID: %i\nSTRING: %s\nSIGSET: %i\n", pid, str, sigset);
	ft_printf("1 if SIGUSR1 is member: %i\n", sigismember(&set, SIGUSR1));
	kill(pid, SIGUSR1);
	write(pid, &str, ft_strlen(str));
	ft_printf("Sent a signal\n");
	return (0);
}
