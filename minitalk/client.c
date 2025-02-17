#include "./libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>


void send_bits(int pid, char *str)
{
    int i;
    unsigned char octet;

    while (*str)
    {
        i = 8;
        octet = *str++;
        while (i--)
        {
            if (octet >> i & 1)
            {
                kill(pid, SIGUSR1);
            }
            else
            {
                kill(pid, SIGUSR2);
            }
            usleep(500);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <PID> <0 or 1>\n", argv[0]);
        return 1;
    }

    int sig = atoi(argv[1]);
    if (sig <= 0)
    {
        printf("Invalid PID.\n");
        return 1;
    }

    send_bits(sig, argv[2]);
    printf("Signal sent to PID %d\n", sig);
    return 0;
}