#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
	char *rl;

	rl = readline("Prompt > ");
	printf("%s\n", rl);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	printf("\n");
	rl_on_new_line();
	rl_replace_line("secundo", 0);
	rl_redisplay();
	return (0);
}