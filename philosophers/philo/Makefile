#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   philo.c                                            :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2025/05/13 11:15:39 by vuljas            #+#    #+#             *#
#*   Updated: 2025/05/13 11:15:44 by vuljas           ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME = philo

CC = cc

WFLAGS = -Werror -Wextra -Wall

SRC = philo.c philo_utils.c routines.c philo_actions.c philo_print_utils.c

OBJPATH = obj/

OBJ = $(SRC:%.c=$(OBJPATH)%.o)

all: $(NAME)

$(NAME): $(OBJPATH) $(OBJ)
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
