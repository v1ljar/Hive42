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
	rl_on_new_line() function tells the update routine that we have moved onto a new empty line,
	usually used after outputting a line.

rl_replace_line		void rl_replace_line(const char *txt, int linenbr);		#include <readline/readline.h>
	rl_replace_line() function replaces the new line[linenbr] with *txt. Also needs
	rl_redisplay() to display the line on terminal.

rl_redisplay		int rl_redisplay(void);		#include <readline/readline.h>
	The rl_redisplay() change what is displayed on the screen to reflect the current contents of rl_line_buffer.

add_history		void add_history(char *s);		#include<readline/history.h>
	The add_history() function saves the line passed as parameter in the history so it can be retrieved later
	in the terminal (like pressing the up arrow in bash).

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
	The open() function opens the file specified by pathname. If specified file does not  exist, it may optionally
	be created by open() (if O_CREATE is specified as flag).

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
	The waitpid() system call suspends execution of the calling thread until a child specified by pid argument has changed state.
	By default, waitpid() waits only for terminated children, but this behavior is modifiable via the options argument.

wait3	pid_t wait3(int *wstatus, int options, struct rusage *rusage);		#include <sys/wait.h>
	NONSTANDARD, suggested is waitpid(). The wait3() system call is similar to waitpid(), but additionally return resource usage
	information about the child in the structure pointed to by rusage. wait3() waits of any child.

wait4	pid_t wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage);
	NONSTANDARD, suggested is waitpid(). The wait4() system call is similar to waitpid(), but additionally return resource usage
	information about the child in the structure pointed to by rusage. wait4() can be used to select a specific child or children, on to wait.

signal		void (*signal(int sig, void(*func)(int)))(int);		#include <signal.h>
	The signal() function specigies a gunction to be executed when the program recives a given signal. The parameter *func is a
	poitner to a function that takes one argument of type int and has no return value.

sigaction		int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);	#include <signal.h>
	The sigaction() function examines and changes the action associated with a specific signal.
	NB! *act must be const struct sigaction. To use signal info, sa_flags must be SA_SIGINFO.

sigemptyset		int sigemptyset(sigset_t *set);		#include <signal.h>
	The sigemptyset() initializes the signal set given by set to empty, with all signal excluded from the set.
	Puropse is to create signal rules, so they do not interupt eachother.

sigaddset		int sigaddset(sigset_t *set, int signum);	#include <signal.h>
	The sigaddset() function adds signal signum to set.

kill		int kill(pid_t pid, int sig);		#include <signal.h>
	The kill() function can be used to send any signal to any process group or process.

exit		void exit(int status);		#include <unistd.h>
	The exit() terminates the calling process "immediately".

getcwd		char *getcwd(char *buf, size_t size);		#include <unistd.h>
	The getcwd() returns a null-terminated string containing the absolute pathname that is the current working directory of the calling process.
	The pathname is returned as the function result and via the argument *buf.

chdir		int chdir(const char *path);		#include <unistd.h>
	The chdir() changes the current working directory of the calling process to the directory specified in path.
	EXAMPLE:
		#include <unistd.h>
		#include <stdio.h> // for printf

		int main(void)
		{
			char *pwd;

			pwd = getcwd(NULL, 0);
			printf("pwd before chdir: %s\n", pwd);
			chdir("/Users/saeby/Documents/42/minishell");
			pwd = getcwd(NULL, 0);
			printf("pwd after chdir: %s\n", pwd);
			return (0);
		}

	OUTPUT:
		$> pwd before chdir: /Users/saeby/Documents/tmp
		$> pwd after chdir: /Users/saeby/Documents/42/minishell

stat		int stat(const char *pathname, struct stat *statbuf);		#include <sys/stat.h>
	The stat() return information about a file, in the buffer pointed to by statbuf.

lstat		int lstat(const char *pathname, struct stat *statbuf);		#include <sys/stat.h>
	The lstat() is identical to stat(), except that if pathname s a symmbolic link, then it returns nformation about the link itself, not the file that the link refers to.

fstat		int fstat(int fd, struct stat *statbuf);		#include <sys/stat.h>
	The fstat() is identical to stat(), except that the file about which information is to be retrieved is specified by the file descriptor fd.
	NB!The stat structure
		All of these stat system calls return a stat structure, which contains  the  following
		fields:
			struct stat {
				dev_t		st_dev;			/* ID of device containing file */
				ino_t		st_ino;			/* Inode number */
				mode_t		st_mode;		/* File type and mode */
				nlink_t		st_nlink;		/* Number of hard links */
				uid_t		st_uid;			/* User ID of owner */
				gid_t		st_gid;			/* Group ID of owner */
				dev_t		st_rdev;		/* Device ID (if special file) */
				off_t		st_size;		/* Total size, in bytes */
				blksize_t	st_blksize;		/* Block size for filesystem I/O */
				blkcnt_t	st_blocks;		/* Number of 512B blocks allocated */
			};

unlink		int unlink(const char* pathname);		#include <unistd.h>
	The unlink() deletes a name from the filesystem. If that name was the last link to a file and no processes have the file open, the file is deleted and the space it was using is made available for reuse.
	If the name was the last link to a file but any processes still have the file open, the file will remain in existence until the last file descriptor referring to it is closed.
	If the name referred to a symbolic link, the link is removed.
	If the name referred to a socket, FIFO, or device, the name for it is removed but processes which have the object open may continue to use it.

execve		int execve(const char *pathname, const char *argv[], const char* envp[]);		#include <unistd.h>
	The execve() executes the program referred to by pathname. This causes the program that is currently being run by the calling process to be replaced with a new program, with newly initialized stack, heap, and (initialized and uninitialized) data segments.

dup		int dup(int oldfd);		#include <unistd.h>
	The dup() creates a copy of the file descriptor oldfd, unig the lowest-numbered unused file descriptor for the new descriptor.
	The two file descriptors do not share file descriptor flags (the close-on-exec flag). The close-on-exec flag (FD_CLOEXEC; see fcntl(2)) for the duplicate desciptor is off.

dup2		int dup2(int oldfd, int newfd);
	The dup2() performs the same task as dup(), but instead of using the lowest-numbered unused file descriptor, it uses the file descriptor number specified in newfd. If the file descriptor newfd was previously open, it is silently closed before being reused.
	The steps of closing and reusing the file descriptor newfd are performed atomically. This is important, because trying to implement equivalent functionality using close() and dup() would be subject to race conditions, whereby newfd might be reused between the two steps(such reuse could happen because the main program is interrupted by a signal handler that allocates a file descriptor).

pipe		int pipe(int pipefd[2]);		#include <unistd.h>
	The pipe() creates a pipe, a unidirecrional data channel that can be used for interprocess communication. The array pipefd[0] refers to the read end of the pipe. pipefd[1] refers to the write end of the pipe.

opendir		DIR *opendir(const char*name);		#include <dirent.h>
	The opendir() function opens a direcory stream corresponding to the direcory name and returns a pointer to the directory stream. The stream is positioned at the first entry in the directory.

readdir		struct dirent *readdir(DIR *dirp);		#include <dirent.h>
	The readdir() function returns a pointer to a dirent structure representing the next directory entry in the direcory stream pointed to by dirp. It return NULL on reaching the end of the directory stream or if an error occurred.
	In the glibc implementation, the dirent structure is defined as follows:

			struct dirent {
				ino_t			d_ino;			/* Inode number */
				off_t			d_off;			/* Not an offset; see below */
				unsigned short	d_reclen;		/* Length of this record */
				unsigned char	d_type;			/* Type of file; not supported by all filesystem types */
				char			d_name[256];	/* Null-terminated filename */
			};

closedir		int closedir(DIR *dirp);		#include <dirent.h>
	The closedir() function closes the directory stream associated with dirp. A successful call too closedir() also closes the underlying file descriptor associated with dirp. The directory stream descriptor dirp is not available after this call.

strerror		char *strerror(int errnum);		#include <string.h>
	The strerror() function returns a pointer to a string that describes the error code passed in the argument errnum, possibly using the LC_MESSAGES part of the current locale to select the approptiate language.

perror		void perror(const char *s);		#include <stdio.h>
	The perror() function produces a message on standard error describing the last error encountered during a call to a system or library function.

isatty		int isatty(int fd);		#include <unistd.h>
	The isatty() function tests whether fd is an open file decriptor referring to a terminal. Returns 1 if fd i an open file descriptor to a terminal, otherwise 0 and errno is set to indicate the error.

ttyname		char **ttyname(int fd);		#include <unistd.h>
	The ttyname() returns a pointer to the null-terminated pathname of the terminal device that is open on the file descriptor fd, or NULL on error(for example if fd is not connected to a terminal).

ttyslot		int ttyslot(void);
	The ttyslot() returns the index of the current user's entry in some file.

ioctl		int ioctl(int fd, unsigned long request, ...);		#include <sys/ioctl.h>
	The ioctl() manipulates the underlying device parameters of special files. In particular, many operating characteristics of character special files (e.g. terminals) may be controlled with ioctl() requests. The argument fd must be an open fd.

getenv		char *getenv(const char *name);		#include <stdlib.h>
	The getenv() function searches the environment list to find the environment variable name and returns a pointer to the corresponding value string.

tcsetattr		int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);	#include <termios.h>
	The tcsetattr() function shall set the parameters associated with the terminal referred to by the open file descriptor fd from the termios struct referenced by termios_p.

tcgetattr		int tcgetattr(int fd, struct termios *termios_p);		#include <termios.h>
	The tcgetattr() function shall get the parameters associated with the terminal referred to by fd and store them in the termios struct referenced by termios_p.

tgetent		int tgetent(char *bp, const char *name);		#include <term.h>??
	The tgetent() routine loads the entry for name. It returns 1 on success, 0 if there is no such entry and -1 if the terminfo database could not be found. The emulation ignores the buffer pointer bp.

tgetflag		int tgetflag(char *id);		#include <term.h>??
	The tgetflag() routine gets the boolean entry for id or 0 if it is not available.

tgetnum		int tgetnum(char *id);		#include <term.h>??
	The tgetnum() routine gets the numeric entry for id or -1 if it is not avaiable.

tgetstr		char *tgetstr(char *id, char **area);		#include <term.h>??
	The tgetstr() routine returns the string enrty for id or 0 if it is not available. The return value will also be copied to the buffer pointed to by **area and the **area value will be updated to point past the null ending this value.

tgoto		char *tfoto(const char *cap, int col, int row);		#include <term.h>
	The tgoto() routine instantiates the parameters into the given capability. The output from this routine is to be passed to tputs.

tputs		int tputs(const char *str, int affcnt, int (*putc)(int));		#include <term.h>
	The tputs() routine applies padding information to the string str and outputs it. The str must be a terminfo string variable or the return value from tparm, tgetstr or tgoto. affcnt is the number of lines affected or 1 if not applicable. putc is a "putchar- like routine to which the characters are passed, one at a time.