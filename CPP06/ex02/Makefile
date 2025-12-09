#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/09 11:36:30 by vuljas            #+#    #+#              #
#    Updated: 2025/12/09 11:36:31 by vuljas           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = type_identification

CC = c++

FLAGS = -Werror -Wall -Wextra -MMD -MP -std=c++17

SRC = main.cpp Base.cpp

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
