MINISHELL external functions:

readline		char *readline(const char *prompt_text);
	readline() reads a line from the terminal and return it, using prompt as a prompt. If no prompt is given as a parameter, no prompt will be shown in the terminal. The line returned is allocated with malloc and we have to free it ourselves.
	Saves readline output int string, NEED TO FREE IT!
	NB! When compiling it need also "-lreadline" flag!!!

	#include <stdio.h>
	#include <readline/readline.h>
	#include <readline/history.h>

	int main(void)
	{
		char *rl;
		rl = readline("Prompt > ");
		printf("%s\n", rl);
		return(0);
	}
	OUTPUT:
	$> ./minishell
	Prompt > Hi ! How are you ?
	Hi ! How are you ?
	$>

rl_clear_history		void rl_clear_history(void);		#include <readline/readline.h>
	rl_clear_history() function clears the history list by deteting all of the entries.
	The rl_clear_history() function frees data that the readline library saves in the history list.

rl_on_new_line		int rl_on_new_line(void);		#include <readline/readline.h>
	rl_on_new_line() function tells the update routine that we have moved onto a new empty line, usually used after outputting a line.

rl_replace_line		void rl_replace_line(const char *txt, int linenbr);		#include <readline/readline.h>
	rl_replace_line() function replaces the new line[linenbr] with *txt. Also needs
	rl_redisplay() to display the line on terminal.

rl_redisplay		int rl_redisplay(void);		#include <readline/readline.h>
	The rl_redisplay() change what is displayed on the screen to reflect the current contents of rl_line_buffer.

add_history		void add_history(char *s);		#include<readline/history.h>
	The add_history() function saves the line passed as parameter in the history so it can be retrieved later in the terminal (like pressing the up arrow in bash).

printf		int printf(char *format, ...);		#include <stdio.h>
	The printf() function print arguments according to *format or execute according to OPTION.

malloc		void *malloc(size_t size);		#include <stdlib.h>
	The malloc() function allocates size bytes and returns a pointer to the allocated memory. Memory is not initialized!

free		void free(void *ptr);		#include <stdlib.h>
	The free() function frees the memory space pointed to by *ptr. If *ptr is NULL, then no operation is performed.

write		ssize_t write(int fd, const void *buf, size_t count);		#include <unistd.h>
	The write() function writes up to count bytes from the buffer starting at *buf to the file referred to by th efile descriptor fd.

access		int access(const char *pathname, int mode);		#include <unistd.h>
	The access() function checks whether the calling process can access the file pathname.
	MODE: F_OK tests for the existence of the file. R_OK, W_OK or X_OK checks existance and persmission respectively.

open		int open(const char *pathname, int flags);		#include <fcntl.h>
	The open() function opens the file specified by pathname. If specified file does not  exist, it may optionally be created by open() (if O_CREATE is specified as flag).

read		ssize_t read(int fd, const void *buf, size_t count);		#include <unistd.h>
	The read() function attempts to read up to count bytes from file descriptor fd into the buffer starting at *buf.

close		int close(int fd);		#include <unistd.h>
	The close() function closes a file descriptor, so that it no longer refers to any file and may be reused.

fork		pid_t fork(void);		#include <unistd.h>
	The fork() function crates a new process by duplicating the calling process. The new process is referred to as the child process.

wait		pid_t wait(int *wstatus);		#include <sys/wait.h>
	The wait() sustem call suspends execution of the calling thread until one of its children terminates.
	With fork, if a wait is not performed, then the terminated child remains in a "zombie" state.

waitpid		pid_t waitpid(pid_t pid, int *wstatus, int options);		#include <sys/wait.h>
	The waitpid() system call suspends execution of the calling thread until a child specified by pid argument has changed state. By default, waitpid() waits only for terminated children, but this behavior is modifiable via the options argument.

wait3	pid_t wait3(int *wstatus, int options, struct rusage *rusage);		#include <sys/wait.h>
	NONSTANDARD, suggested is waitpid(). The wait3() system call is similar to waitpid(), but additionally return resource usage information about the child in the structure pointed to by rusage. wait3() waits of any child.

wait4	pid_t wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage);
	NONSTANDARD, suggested is waitpid(). The wait4() system call is similar to waitpid(), but additionally return resource usage information about the child in the structure pointed to by rusage. wait4() can be used to select a specific child or children, on to wait.

signal		

sigaction

sigemptyset

sigaddset

kill

exit

getcwd

chdir

stat

lstat

fstat

unlink

execve

dup

dup2

pipe

opendir

readdir

closedir

strerror

perror

isatty

ttyname

ttyslot

ioctl

getenv

tcsetattr

tcgetattr

tgetent

tgetflag

tgetnum

tgetstr

tgoto

tputs