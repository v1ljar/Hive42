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

OBJ = $(SRC:%.cpp = obj/%.o)

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
fclean:
	@if [ -f $(NAME) ]; then \
		rm $(NAME); \
	else \
		echo "make fclean: Nothing to be done for 'make fclean'"; \
	fi

re: fclean all

test: all
	@echo "\033[1;36mBuilding and running tests...\033[0m"
	$(CXX) $(CXXFLAGS) test.cpp -o test_replace
	@./test_replace



.PHONY: all clean fclean re
