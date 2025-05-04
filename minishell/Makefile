# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/20 10:49:58 by jpiensal          #+#    #+#              #
#    Updated: 2025/04/11 13:53:17 by jpiensal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
LIBFT		= libft/libft.a
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g
HEADERS		= -I./inc -I./libft/inc/

OBJ_PATH	= obj/
PARSER_PATH = src_parsing/
BUILTIN_PATH= built-in/

SRC			= environment.c update_env.c \
			  exec.c exec_utils.c \
			  redirections.c heredoc.c \
			  minishell_utils.c \
			  signals.c \
			  main.c

SRC_PARSER	= preprocess_input.c lexing.c lexing_checkers.c \
			lexing_token_action.c lexing_handle_word.c lexing_handle_envv.c \
			parser.c parser_helpers.c parser_free.c preprocess_utils.c \

SRC_BUILTIN	= export.c env.c pwd.c unset.c echo.c cd.c exit.c

OBJ			= $(SRC:%.c=$(OBJ_PATH)%.o)
PARSER_OBJ	= $(SRC_PARSER:%.c=$(OBJ_PATH)%.o)
BUILTIN_OBJ	= $(SRC_BUILTIN:%.c=$(OBJ_PATH)%.o)

all:		$(NAME)

$(NAME):	$(LIBFT) $(OBJ_PATH) $(OBJ) $(PARSER_OBJ) $(BUILTIN_OBJ)
			$(CC) $(OBJ) $(PARSER_OBJ) $(BUILTIN_OBJ) -o $(NAME) $(LIBFT) -lreadline

$(LIBFT):
			make all -C ./libft

$(OBJ):		$(OBJ_PATH)%.o: %.c
			$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(PARSER_OBJ): $(OBJ_PATH)%.o: $(PARSER_PATH)%.c
			$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(BUILTIN_OBJ): $(OBJ_PATH)%.o: $(BUILTIN_PATH)%.c
			$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(OBJ_PATH):
			mkdir -p $(OBJ_PATH)

clean:
			make clean -C ./libft
			rm -rf $(OBJ) $(OBJ_PATH)

fclean:		clean
			make fclean -C ./libft
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
