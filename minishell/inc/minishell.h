/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:17:25 by vuljas            #+#    #+#             */
/*   Updated: 2025/04/29 14:34:15 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <signal.h>

# include "libft.h"

# define RED "\033[1;31m"
# define GREEN "\033[0;92m"
# define YELLOW "\033[0;93m"
# define BLUE "\033[1;34m"
# define YE	"\033[4;94m"
# define RESET "\033[0m"

extern volatile sig_atomic_t	g_signal;

typedef enum e_token_type
{
	CMD,
	ARG,
	PIPE,
	INFILE,
	OUTFILE,
	HEREDOC,
	APPEND,
	ENVV
}	t_token_type;
/*
 * Stores information of tokens.
 * Stored values: 	token type, token value and pointer to next token.
 */
typedef struct s_token
{
	int				type;
	char			*value;
	struct s_token	*next;
}	t_token;
/*
 * Stores all the necessary information to execute a command
 * cmd[0] is the name of the command and cmd[1+n] are the arguments
 * infile/outfile are pointers to a list of t_file structs
 * path has the shell path to the command, e.g. usr/bin/cat
 * next is the pointer to next command if one exits
 */
typedef struct s_cmd
{
	char			**cmd;
	struct s_file	*infile;
	struct s_file	*outfile;
	char			*path;
	int				fdin;
	int				fdout;
	bool			io_error;
	struct s_cmd	*next;
}	t_cmd;

/*
 * Stores the files that the user wants to be redirected
 * Type tells is the redirection '<', '>' or '+'
 * '+' represent both '<<' and '>>'
 * next is the pointer to next file if one exits
 */
typedef struct s_file
{
	char			type;
	char			*filename;
	int				herepipe[2];
	struct s_file	*next;
}	t_file;

/*
 * Stores all the necessary data to run the shell
 * including the environment list and commands exit status.
 * Also has a pointer to the first command
 */
typedef struct s_master
{
	t_list				*env;
	struct s_cmd		*root_cmd;
	char				*input;
	char				*cleaned;
	struct s_token		*tokens;
	int					wstatus;
	int					pid;
	char				*pwd;
	char				*oldpwd;
	struct sigaction	sa;
	bool				is_exit_set;
}	t_master;

/* Signals */
void		init_signals(struct sigaction *sa);
void		rl_signal_handler(void);
void		exec_signals_handler(void);
/* Preprocessing_input */
// Managing cleaning leading and trailing isspace characters and if quotes
// are not closed, then it gives syntax error.
int			preprocessing_input(t_master *mini, int i);
/* Preprocessing utils */
int			valid_open_pipe(char *temp, int i, t_master *mini, int j);
int			free_n_continue(char **str, t_master *mini);
/*	Lexing */
// Manages lexing process(loops through the string char by char and
// divides values into respective type tokens).
void		lexer(t_master *mini, int i);
/* Lexing_checkers */
// Function checks if the character is an operator.
int			is_operator(char c);
// Checks if the token type should be CMD (return 0) or ARG return (1).
int			is_cmd(t_token **tokens);
// Extracts and returns the name parameter of the operator.
char		*get_operator_name(t_master *mini, int *i, int type);
// Helper function for handle_envv, it checks the type envv should be.
void		check_envv_position(t_token **tokens, t_token **last_tok,
				char *envv_name);
/* Lexing token action */
// Creates token and assigns type and value of token.
t_token		*create_token(int type, char *value);
// Adds token to the list accordingly
void		add_token(t_token **tokens_list, t_token *new);
/* Lexing handle word */
// Helper function for handle_word, it manages the word extraction
// from the string, it uses helper functions to extract the word,
// allocate memory, fills with content and return the word.
char		*extract_word(char *str, int *i);
// Helper function for handle_word, it allocates memory for the string
// with calloc and if needed, uses helper function to handle quotes
// and then return the string.
char		*extract_quotes(char *str, t_master *mini, int i, int j);
/* Lexing handle envv */
// Helper function for handle_envv, it handles the environment variable
// if it is not in the quotes and expands the value from env.
char		*expand_envv(t_master *mini, char *str, int *i, int len);
// Helper function for extract_env_var, it is called only if
// environment_variable is not ending with space or '\0',function
// extracts the rest of the variable and joins it with expanded
// environment variable.
char		*extract_full_variable(char *str, int *i, char *envv_name,
				t_master *mini);
// Helper function to handle_double_quotes and it gets the env
// name from the string and expands it, function uses
// envv_to_str to place the expansion value into the string.
void		extract_envv_quotes(t_master *mini, char **buf, int *i,
				int *j);
// Helper function for the extract_envv_quotes, it concatagnates
// envv value into it string.
void		envv_to_str(char **buf, char *env_v, int *j);

/* Parser */
// Parse through tokens and fill t_master struct accordingly, return the struct
void		parser(t_master *mini);
/* Parser_helpers */
// Helper function for handle_redirection, adds file to infile list.
void		add_infile_to_list(t_cmd **last_cmd, t_file *file);
// Helper function for handle_redirection, adds file to outfile list.
void		add_outfile_to_list(t_cmd **last_cmd, t_file *file);
void		handle_redirection_error(t_master *mini, t_cmd **last_cmd);
int			is_directory(t_master *mini, bool print);
/* Parser_free */
// Helper function for parser, frees tokens pointers.
void		free_tokens_pointers(t_token *tokens_list, int err);
// Frees t_master struct content respecively.
void		free_cmds(t_master	*mini);
// Helper function for free_cmds, free infile/outfile list.
// If id == 1 indicates infile, 0 for outfile.
void		iterate_list_free(t_cmd *temp, int id);

/*
 * This is the main function of execution.
 * Takes in master struct.
 * Forks 1 child if a command is found and the only command is not builtin
 * initializes io-table for commands
 * waits for all the children to return.
 */
int			mini_exec(t_master *mini);
/** MINISHELL_UTILS.C **/
/*
 * prints the given cmd, filename and error text to stderr
 * 2 possible outputs depending on errortype:
 * -> minishell: cmd: filename: err_str
 * -> minishell: cmd: filename: strerror(errno)
 */
int			mini_error(char *cmd, char *filename, char *err_str, int err_no);
void		handle_temp_io(int temp_io[2], int flag);
/*
 * Check if given string is a builtin command
 * Returns true if so and false if not.
 */
bool		is_builtin(const char **str);
/*
 * Helper function to delete the content of a list node containing a string.
 */
void		del_content(void *content);
int			close_fd(t_cmd *cmd);
/** ENVIRONMENT.C **/
/*
 * Takes in the environment list and a parameter to search for
 * If parameter found -> returns a character pointer to its value
 * if not found -> returns NULL
 */
char		*find_envv(t_list *env, const char *parameter);
/*
 * Takes in the environment and creates a memory allocated list of it
 */
t_list		*envcpy(char **envp);
/*
 * Takes in the environment list and a parameter to search for
 * If parameter found -> returns a pointer to the node of the parameter
 * If not found -> returns NULL
 */
t_list		*find_envp(t_list *env, const char *parameter);
/*
 * Takes in the environment list and updates the shell level
 * On success returns 0, and on error returns -1.
 */
int			update_shlvl(t_list *env);
char		*find_path(t_list *env, char *cmd);
/** UPDATE_ENVIRONMENT.C **/
/*
 * Updates the local env list
 */
/*
 * Takes in the master struct
 * Updates the last command to environment "_"
 */
void		update_last_argument(t_master *mini);
/*
 * Updates the pwd and oldpwd that are in the master struct
 * Updates PWD and OLDPWD of the environment if not removed
 */
void		update_directories(t_master *mini);
/*
 * Modifys the envlist with the given parameters
 * env is the visible environment list
 * tmp is the environment struct that is being modified
 * str is the content that the struct will have
 * if replace is true -> content is being replaced
 * if replace if false -> new environment struct is being added to the env
 */
void		modify_envlist(t_list *env, t_list *tmp, char *str, bool replace);
/*
 * Cleans up the memory (master struct) after main loop is being exited
 */
void		clean_up(t_master *mini);

#endif
