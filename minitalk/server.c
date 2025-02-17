#include "./libft/libft.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void bit_write(int x)
{
    static int bit = 7;
    static unsigned char set = 0;

    set += (x << bit);

    if (bit == 0)
    {
        write(1, &set, 1);
        set = 0;
        bit = 7;
    }
    else
    {
        bit--;
    }
}
void handle_signal(int signum, siginfo_t *info, void *context)
{
    if(signum == SIGUSR1)
        bit_write(1);
    else
        bit_write(0);
    (void)info;
    (void)context;
}

int main()
{
    struct sigaction sa;
    
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_signal;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
    {
        perror("sigaction failed");
        return 1;
    }

    printf("Server running. PID: %d\n", getpid());

    while (1)
    {
        pause();
    }

    return 0;
}
