


#include "ft_printf.h"
#include <limits.h>
#include <fcntl.h>
int main(void) {
	int i = INT_MIN;
	char c = 42;
	void *ptr = NULL;
	unsigned int ui = 0;
	char *s = "42";
	int res;
	int res_og;
	int og_stdout = dup(STDOUT_FILENO);
	fclose(stdout);
	res = ft_printf("char: %c\n string: %s\n pointer: %p\n dec: %d\n int: %i\n uint: %u\n base16: %x\n BaSE16: %X\n percent: %%\n", c, s, ptr, i, i, ui, c, i * 1000);
	res_og = printf("char: %c\n string: %s\n pointer: %p\n dec: %d\n int: %i\n uint: %u\n base16: %x\n BaSE16: %X\n percent: %%\n", c, s, ptr, i, i, ui, c, i * 1000);
	stdout = (FILE *)fdopen(og_stdout, "w");
	printf("%i", res);
	printf("%i", res_og);
} 
