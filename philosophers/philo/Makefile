# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 11:15:39 by vuljas            #+#    #+#              #
#    Updated: 2025/05/28 13:23:18 by vuljas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

WFLAGS = -Werror -Wextra -Wall

SRC = philo.c philo_utils.c philo_routines.c philo_actions.c philo_helpers.c \
		philo_routines_helpers.c philo_threads.c

OBJPATH = obj/

OBJ = $(SRC:%.c=$(OBJPATH)%.o)

all: $(NAME)

$(NAME): $(OBJPATH) $(OBJ) philo.h Makefile
	$(CC) $(OBJ) -o $(NAME)

$(OBJ): $(OBJPATH)%.o: %.c
	$(CC) $(WFLAGS) -c $< -o $@ -pthread

$(OBJPATH):
	mkdir -p $(OBJPATH)

clean:
	rm -rf $(OBJ) $(OBJPATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
