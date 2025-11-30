#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/27 11:24:44 by vuljas            #+#    #+#              #
#    Updated: 2025/11/27 11:24:45 by vuljas           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = intern

CC = c++

FLAGS = -Wall -Wextra -Werror -std=c++17 -MMD -MP

SRC = main.cpp Bureaucrat.cpp AForm.cpp ShrubberyCreationForm.cpp \
	  RobotomyRequestForm.cpp PresidentialPardonForm.cpp Intern.cpp

OBJ = $(SRC:%.cpp=obj/%.o)

DEP = $(OBJ:.o=.d)

obj/%.o: %.cpp
	mkdir -p obj;
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $@ $(OBJ)

-include $(DEP)

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
