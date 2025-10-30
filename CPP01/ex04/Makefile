#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/23 13:23:27 by vuljas            #+#    #+#              #
#    Updated: 2025/10/23 13:23:31 by vuljas           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = sed_is_for_losers

CC = c++

FLAGS = -Werror -Wextra -Wall -std=c++11

SRC = main.cpp

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

test: all
	@rm -rf tests;
	@mkdir -p tests;
	@echo "\t\t[ Building and running tests... ]"
	$(CC) $(FLAGS) test.cpp -o ./tests/test_replace
	@./tests/test_replace
	@rm -rf tests main.o;
	@make fclean;



.PHONY: all clean fclean re
