#include "minitalk.h"

static void	handler(int sig, siginfo_t *info, void *context);
static void handle_sig(int sig);
static int 	len = 0;

int	main(int argc, char **argv)
{
	struct sigaction sa;

	if (argc != 1)
		return(ft_printf("Server program do NOT accept arguments!\n"));
	ft_printf("PID: %i\n", getpid());

	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
}

static void	handler(int sig, siginfo_t *info, void *context)
{

	//ft_printf("SenderPID: %i", info->si_pid);
	if (sig == SIGUSR1)
		handle_sig(1);
	else if (sig == SIGUSR2)
		handle_sig(0);
	(void)info;
	(void)context;
}

static void handle_sig(int sig)
{
	static int				pos = 7;
	static unsigned char	c = 0;
	static char				str[200000];

	c += (sig << pos);
	if (pos == 0)
	{
		str[len] = c;
		len++;
		if (pos == 0 && c == '\0')
		{
			ft_printf("%s", str);
			ft_bzero(str, 200000);
			len = 0;
		}
		pos = 7;
		c = 0;
	}

	else
		pos--;
}