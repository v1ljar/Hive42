# MINISHELL

## HIGH LEVEL ABSTRACTION OF MINISHELL AND WORK SHARING

**SET THE ENVIRONMENT🛠️**

- set/update the environment (*Viljar/Jyri*)

**LEX AND PARSE📜**

- prompt for input (*Viljar*)
	- main function is continous 'while (1)' loop, for the prompt we use readline function
		- ✅ if readline() output size is greater than prompt size
			- preprocess_input() translates readline() output ['\n', '\t', '\r'] into ' ' and cleans  from consecutive spaces
				- ✅ if preprocess_input() != NULL
					- continue lexing the preprocess_input() output
				- 🛑 else if unclosed quotes
					- Error message
					- Prompt back to user
				- 🛑 else
					- prompt back to user for next input
		- 🛑 else
			- process is waiting for user input
				- to terminate the process (exit), we use signals

- Lex the input (*Viljar*) [ Loop through cleaned input char by char, divide input into respective type of tokens, return value is t_token*]
	- ✅ if char is **$**
		- ✅ if NO previous token or previous token type is PIPE and next char is space
			- create token: type CMD, value '$'
		- 🛑 if next char is space or quote
			- skip the '$' and continue lexing
		- ✅ else
			- extract characters until space into environment variable string
				- expand the environment variable string
					- ✅ if expansion has value
						- if in tokens list no CMD token and previos token is not PIPE
							- create and add token: type CMD, value is expanded environment string
						- else create and add token: type ENVV, value is expanded environment string
					- 🛑 if expansion has no value
						- skip the characters and continue lexing
	- ✅ if char is operator **<** **>** **|**
		- save the operator value to stack
			- check the next char
				- if it is the same as operator **<** **>**
					- update the operator value and continue
			- check the operator type and add it to token respectively **INFILE OUTFILE APPEND HEREDOC PIPE**
			- if operator is **PIPE**
				- create token: type PIPE, value "|"
			- else
				- create token: type was initialized, value is extracted string after the operator or NULL if no characters after the operator
			- add token to the tokens list
	- 🛑 if char is space
		- skip space
	- ✅ else
		- extract charaters until space into a char *word [ If '$' if word and not in single quotes, then expand the environment variable respectively ]
			- 🛑 if word == NULL
				- continue lexing
			- ✅ if in tokens list no CMD token and previous token is not PIPE
				- create token: type CMD, value is the extracted word
			- ✅ else
				- create token: type ARG, value is the extracted word
			add token to the tokens list

- Parse the input (*Viljar*) [ Loop through the tokens list and create array of commands, PIPE acts as separator, return value is (t_master *master) ]
	- create varibles t_cmd *root_cmd and t_master *master
		- initialize root_cmd values to NULL, master->env fill with environment data and initialize master->root_cmd to t_cmd *root_cmd
	- parse through list of tokens
		- if token type is redirection [ INFILE OUTFILE APPEND or HEREDOC ]
			- create t_file struct for redirection [types: INFILE< OUTFILE> APPEND+ or HEREDOC+]
				- t_file->type is tokens type respecivly, t_file->*filename value is token value
					- add t_file struct into list respectively: t_cmd->*infile or t_cmd->*outfile
		- if token type is [ CMD ARG or ENVV ]
			- if token type is CMD, then search the shell path to the command and add it to t_cmd->path
			- add token value to t_cmd->**cmd
		- else
			- possible token type is only PIPE, create a new t_cmd and assign it as last t_cmd->next
	- return t_master *master

**EXECUTE🚀**
- Initial checks (*Jyri*)
	- Take in the t_master *master
	- check master->cmd;
		- if NULL
	 		- Do nothing and Return ;
	   	- else begin executing
- Prepare execution - In root parent (*Jyri*)
	- initialize struct pipe
 		- store stdin and stdout to tempin and tempout
		- initialize fdin and fdout to tempin and tempout
	- create a child and go to command execution
    		- wait the last child to return

- Command execution - In children (*Jyri*)
   - check cmd->next
	   	- if != NULL create a pipe(fd)
		 	- fdout = pipe[1]
		  	- pid = fork() -> a new child
		  	- if pid == 0
				- close pipe[1]
		   		- fdin = pipe[0]
		   		- call the function again with cmd->next
    - Handle redirections
	 	- Loop through infiles/outfiles and open them as needed
	 	- If '+' found on infile
	  		- execute heredoc (create a tmpfile and write the prompt there)
	   	- update fdin and fdout as needed
  - duplicate fdin and fdout to stdin and stdout
  - close fd's that don't need to be open
  - Check cmd[0]
	- if built-in
  		- execute builtin with args
  	- else
		- get path of the command
  	 	- execve(cmd_path, cmd + args, envp)

**TESTING**
- I created suppression file
	- To use it and create also log file, use command: valgrind --track-origins=yes --track-fds=yes --trace-children=yes --show-leak-kinds=all --leak-check=full --suppressions=suppressions.log --log-file=valgrind.log ./minishell

**REPEAT FROM THE BEGINNING**

----- END OF ABSTRACTION -----

## 📢THINGS TODO AND CONSIDER 🎯
- 💡 How and when to control the signals? ✅
	- 🔑 In the while (1) loop we use signal() for each signal, that listens for signals and I create signal_handler function, to handle the signals respectively.

- 💡 Is the environment variable expansion also working if the envv is after quotes and it should be part of the argument? ✅
	- 🔑 Yes, it is working and expanding to the argument.

- 💡 How to check the expansions in a heredoc? ✅
  	- 🔑 At the moment if delimiter has quotes, then those quotes are not cleaned and is passed on to the value. I think it would reasonable be if the function that handles the HEREDOC, at first checks the occurance of quotes in delimiter and function has a flag that indicates occurance of quotes, then if quotes occur, then need to clean the delimiter and set the quotes flag true, then user inserts the input, until delimiter everything is appended and then function needs to process the input based on the quotes flag. I think we can use char	*extract_env_var(char *str, int *i) function to expand the environment variable. ✅
  	-  The question was not about what should be considered but just a general question for myself that how should I implement it :) All clear now ✅
- 💡 How to set the ARG_MAX so that it matches shell? Now the shell value is 2097152 and minishell 131072? ✅
	- When reciving input, we can make a check if the size of the input is greater than 2097152, then it gives error message "Input is too long, max size is 2097152" and give prompt back to the user. ✅🛑?
 	- 🔑 It seems we don't need to use the ARG_MAX. At least that is what I talked with others. For environment we should use PATH_MAX which is in the limits.h library. ✅
- 💡 How to deal with builtin exits and errors. Builtins should be possible to use (especially cd) in a parent process for the chdir to take effect, but if errors occur we can't exit since it would exit the whole minishell. For now I have used mini_error, which prints the error msg to stderr and exits the process.
	- 🔑 Mini_error returns the exit value. Then it's up to function caller to either exit or return the value received from mini_error. ✅

### BUILTINS
- ✅ echo with -n
- ✅ env
- ✅ export
- ✅ unset
- ✅ pwd
- ✅ cd
- ✅ exit

## LINKS AND OTHER USEFUL STUFF
📖 [Bash Manual](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#What-is-Bash_003f)

📖 [WritingYourOwnShell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
