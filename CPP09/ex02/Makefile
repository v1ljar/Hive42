#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/12 10:39:01 by vuljas            #+#    #+#              #
#    Updated: 2026/02/12 10:39:04 by vuljas           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = PmergeMe

CC = c++

FLAGS = -Werror -Wall -Wextra -MMD -MP -std=c++20

SRC = main.cpp PmergeMe.cpp

OBJ = $(SRC:%.cpp=obj/%.o)

DEP = $(OBJ:.o=.d)

all: $(NAME)

obj/%.o: %.cpp
	mkdir -p obj
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $@ $(OBJ)

-include $(DEP)

clean:
	@if [ -d obj ]; then \
		rm -rf obj; \
	else \
		echo "make clean: Nothing to be done for 'make clean'"; \
	fi \

fclean: clean
	@if [ -f $(NAME) ]; then \
		rm $(NAME); \
	else \
		echo "make fclean: Nothing to be done for 'make fclean'"; \
	fi \

re: fclean all

PHONY: all clean fclean re
