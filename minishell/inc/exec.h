/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:25:08 by jpiensal          #+#    #+#             */
/*   Updated: 2025/04/29 14:20:03 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <limits.h>
# include <errno.h>
# include <sys/stat.h>
# include "minishell.h"

/** EXEC.C **/
/*
 * This is the main function of execution.
 * Takes in master struct.
 * Declared in minishell.h
 * Forks 1 child if a command is found and the only command is not builtin
 * initializes io-table for commands
 * waits for all the children to return.
 */
//int		mini_exec(t_master *mini);
/*
 * File also contains these functions:
 * static exec_cmd(t_master *mini, t_cmd *cmd);
 * -> is the main recursive fuction of each command
 * static int create_new_process(t_master *mini, t_cmd *cmd);
 * -> helper function to create a new process to execute a command
 * static void exec_builtin(t_master *mini, t_cmd *cmd);
 * -> looks at the current command and calls the builtin if match is found
 */
int		handle_heredoc(t_list *env, t_file *file, int *fd, t_master *mini);
/** EXEC_UTILS.c **/
/*
 * counts the number of commands
 */
size_t	count_commands(t_cmd *cmd);
int		is_heredoc_signal(t_master *mini, int *fd, char *line);
/*
 * copies a list whose contents are strings to an array of strings
 */
char	**cpy_lst_to_arr(t_list *lst);
/*
 * performs a swap for two char * pointers
 */
void	swap_ptrs(char **s1, char **s2);
void	close_herepipes(t_file *file);
/* REDIRECTIONS.C */
/*
 * sets the needed redirections for current command
 * calls the function "open_files" which opens all the set files and
 * returns the last one (similar to bash)
 */
int		set_redirections(t_cmd *cmd);
int		dup_fd(t_cmd *cmd);
int		set_io(t_cmd *cmd, int *temp_io, bool is_in);
int		create_pipe(t_cmd *cmd);
void	wait_loop(t_master *mini);
/***** BUILT-IN FUNCTIONS *****/

/*
 * Takes in environment list and the args of command 'export'
 * Tries to find all the strings in args from the environment list
 * If there's a match -> replaces the match
 * If no match -> creates a new environment parameter
 * If no args given, prints the env list to stdout if not directed elsewhere
 */
int		mini_export(t_list *env, char **args);

/*
 * Takes in environment list and args of command 'unset'
 * Tries to find all the strings in args from the environment list
 * If there's a match -> remove current arg from env
 * If no match - does nothing
 */
int		mini_unset(t_master *mini, char **args);

/*
 * Takes in the environment list
 * Prints it to stdout if not directed elsewhere
 */
int		mini_env(t_list *env, char **cmd);

/*
 * Takes in the environment list.
 * prints its parameter PWD to stdout if not directed elsewhere
 */
int		mini_pwd(t_master *mini);

/*
 * If n is specified stores that value to "$?"
 * Only needed to exit minishell?
 * In all other cases the "normal" exit function can be used?
 */
int		mini_exit(t_master *mini, char **cmd);

/*
 * Takes in the arguments of command 'echo'
 * Prints the arguments to stdout if not directed elsewhere
 * If -n flag given, doesn't add a new line at the end of print
 */
int		mini_echo(char **args);

/*
 * Takes in the master struct and the command list
 * If used with other commands check the validity of command but doesn't execute
 * Error checks:
 * -> Only one argument accepted
 * -> Only dirs allowed
 * -> User needs to have execute permissions
 * If used alone:
 * -> If no args or if '~' changes dir to $HOME
 * -> If '-' used changes dir to $OLDPWD
 * -> If $HOME or $OLDPWD have been unset sets errno and prints it in mini_error
 */
int		mini_cd(t_master *mini, char **cmd);

#endif
