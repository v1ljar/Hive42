#include "./libft/libft.h"
#include <signal.h>

int	main(void)
{
	int		sigset;
	sigset_t	set;

	ft_printf("PID: %i", getpid());
	sigset = sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigaction(SIGUSR1, NULL, NULL);
	while (1)
	{

	}
	return (0);
}
