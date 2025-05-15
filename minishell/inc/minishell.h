/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:17:25 by vuljas            #+#    #+#             */
/*   Updated: 2025/05/09 13:42:59 by jpiensal         ###   ########.fr       */
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
	int					temp_io[2];
	char				*pwd;
	char				*oldpwd;
	struct sigaction	sa;
	bool				is_exit_set;
}	t_master;

/** SIGNALS **/
// Initializes signal handler.
void		init_signals(struct sigaction *sa);
// Interactive mode signal handling.
void		signal_handler_rl(void);
/** PREPROCESSING INPUT **/
/* Managing cleaning leading and trailing isspace characters and if quotes
 * are not closed, then it gives syntax error. */
int			preprocessing_input(t_master *mini, int i);
/* Fill in the result string from the temporary string and if quotes are not
 * closed, then print error message. */
int			handle_quote(char **res, char *buf, int *i, int *j);
/** PREPROCESSING UTILS **/
// Check if input has opened pipe that needs user to fill.
int			valid_open_pipe(char *temp, int i, t_master *mini, int j);
// Helper function for handle_open_pipe, handles SIGINT signal data freeing
int			free_n_continue(char **str, t_master *mini);
/** LEXING **/
/* Manages lexing process(loops through the string char by char and
 * divides values into respective type of tokens). */
void		lexer(t_master *mini, int i);
/** LEXING CHECKERS **/
// Function checks if the character is an operator.
int			is_operator(char c);
// Checks if the token type should be CMD (return 0) or ARG return (1).
int			is_cmd(t_token **tokens);
// Extracts and returns the name parameter of the operator.
char		*get_operator_name(t_master *mini, int *i, int type);
// Helper function for handle_env_var, it checks the type env_var should be.
void		check_env_var_position(t_token **tokens, t_token **last_tok,
				char *envv_name);
/** LEXING TOKEN ACTION **/
// Creates token and assigns type and value of token.
t_token		*create_token(int type, char *value);
// Adds token to the list accordingly.
void		add_token(t_token **tokens_list, t_token *new);
// Checks if tilde, then expands it, otherwise adds character into buf
int			check_tilde_add_to_buf(char *buf, char *str, int *i,
				t_master *mini);
/** LEXING HANDLE WORD **/
/* Helper function for handle_word, it manages the word extraction
 * from the string, it uses helper functions to extract the word,
 * allocates memory, fills with content and returns the word. */
char		*extract_word(char *str, int *i);
/* Helper function for process_word, it extracts the total content of the
 * word into modifyable string char **buf. */
void		handle_single_quotes(char *str, char **buf, int *i, int *j);
/* Helper function for handle_word, it allocates memory for the string
 * with calloc and if needed, uses helper function to handle quotes
 * and then returns the string. */
char		*process_word(char *str, t_master *mini, int i, int j);
/** LEXING HANDLE ENV_VAR **/
/* Helper function for handle_env_var, it handles the environment variable
 * if it is not in the quotes and expands the value from env. */
char		*expand_env_var(t_master *mini, char *str, int *i, int len);
/* Helper function for extract_env_var, it is called only if after
 * environment_variable in input string is not space or '\0',function
 * extracts the rest of the variable and joins it with expanded
 * environment variable.*/
char		*extract_full_variable(char *str, int *i, char *envv_name,
				t_master *mini);
/* Helper function to handle_double_quotes and it gets the env
 * name from the string and expands it, function uses
 * envv_to_str to place the expansion value into the string.*/
void		extract_envv_quotes(t_master *mini, char **buf, int *i,
				int *j);
/* Helper function for the extract_envv_quotes, it concatagnates
 * envv value into it string. */
void		envv_to_str(char **buf, char *env_v, int *j);
/** PARSER **/
// Parse through tokens and fill t_master struct root_cmd accordingly.
void		parser(t_master *mini);
/* Parser_helpers */
// Helper function for handle_redirection, adds file to infile list.
void		add_infile_to_list(t_cmd **last_cmd, t_file *file);
// Helper function for handle_redirection, adds file to outfile list.
void		add_outfile_to_list(t_cmd **last_cmd, t_file *file);
// Handles redirection error accordingly.
void		handle_redirection_error(t_master *mini, t_cmd **last_cmd);
/** PARSER_FREE **/
/* Helper function for parser, frees tokens pointers or values accordingly.
 * If int err == 0 - free tokens pointers.
 * If int err == 1 - free tokens values. */
void		free_tokens_pointers(t_token *tokens_list, int err);
// Frees t_master struct content respecively.
void		free_cmds(t_master	*mini);
/* Helper function for free_cmds, free infile/outfile list.
 * If id == 1 indicates infile, id == 0 for outfile. */
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
void		command_error(char *cmd);
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
/*
 * build_environment.c
 */
int			build_environment(t_master *mini);
int			copy_environment(t_master *mini, char **env);
/** ENVIRONMENT.C **/
/*
 * Takes in the environment list and a parameter to search for
 * If parameter found -> returns a character pointer to its value
 * if not found -> returns NULL
 */
char		*find_envv(t_list **env, const char *parameter);
/*
 * Takes in the environment and creates a memory allocated list of it
 */
t_list		*envcpy(char **envp);
/*
 * Takes in the environment list and a parameter to search for
 * If parameter found -> returns a pointer to the node of the parameter
 * If not found -> returns NULL
 */
t_list		*find_envp(t_list **env, const char *parameter);
/*
 * Takes in the environment list and updates the shell level
 * On success returns 0, and on error returns -1.
 */
int			update_shlvl(t_list *env, int new_lvl);
char		*find_path(t_list *env, char *cmd);
/** UPDATE_ENV.C **/
/*
 * Takes in the master struct
 * Updates the last command to environment "_"
 */
int			update_last_argument(t_master *mini, int i);
/*
 * Modifys the envlist with the given parameters
 * env is the visible environment list
 * tmp is the environment struct that is being modified
 * str is the content that the struct will have
 * if replace is true -> content is being replaced
 * if replace if false -> new environment struct is being added to the env
 */
int			modify_envlist(t_list *env, t_list *tmp, char *str, bool replace);
void		free_env_strings(char *shlvl, char *last_arg, char *pwd);
/*
 * Cleans up the memory (master struct) after main loop is being exited
 */
void		clean_up(t_master *mini);

#endif
