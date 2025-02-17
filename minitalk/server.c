#include "minitalk.h"

static void	handler(int sig, siginfo_t *info, void *context);
static void handle_sig(int sig);

int	main(int argc, char **argv)
{
	struct sigaction sa;

	if (argc != 1)
		return(ft_printf("Server program do NOT accept arguments!\n"));
	ft_printf("PID: %i\n", getpid());

	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_ONSTACK;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
}

static void	handler(int sig, siginfo_t *info, void *context)
{
	if (sig == SIGUSR1)
		handle_sig(1);
	else
		handle_sig(0);
	(void)info;
	(void)context;
}

static void handle_sig(int sig)
{
	static int				pos = 7;
	static unsigned char	c = 0;

	c += (sig << pos);
	if (pos == 0)
	{
		write(1, &c, 1);
		pos = 7;
		c = 0;
	}
	else
		pos--;
}