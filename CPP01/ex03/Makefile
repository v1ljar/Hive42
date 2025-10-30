#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/30 13:09:12 by vuljas            #+#    #+#              #
#    Updated: 2025/10/30 13:09:14 by vuljas           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = unnecessary_violence

CC = c++

FLAGS = -Werror -Wextra -Wall -std=c++17

SRC = main.cpp Weapon.cpp HumanA.cpp HumanB.cpp

OBJ = $(SRC:%.cpp=obj/%.o)

all: $(NAME)

obj/%.o: %.cpp
	mkdir -p obj
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $@ $(OBJ)

clean:
	@if [ -d obj ]; then \
		rm -rf obj; \
	else \
		echo "make clean: Nothing to be done for 'make clean'"; \
	fi
fclean: clean
	@if [ -f $(NAME) ]; then \
		rm $(NAME); \
	else \
		echo "make fclean: Nothing to be done for 'make fclean'"; \
	fi

re: fclean all

.PHONY: all clean fclean re
