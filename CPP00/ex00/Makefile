NAME = megaphone

CC = c++

FLAGS = -Werror -Wextra -Wall -std=c++11

SRC = megaphone.cpp

OBJ = $(SRC:%.cpp=obj/%.o)

all: $(NAME)

obj/%.o: %.cpp
	mkdir -p obj
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@

clean:
	@if [ -d obj ]; then \
		rm -rf obj; \
	else \
		echo "make clean: Nothing to be done for 'make clean'";\
	fi

fclean: clean
	@if [ ! -f $(NAME) ]; then \
		echo "make fclean: nothing to be done for 'make fclean'"; \
	else \
		rm -f $(NAME); \
	fi

re: fclean all

.PHONY: all clean fclean re
