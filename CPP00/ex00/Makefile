NAME = megaphone

CC = c++

FLAGS = -Werror -Wextra -Wall -std=c++11

SRC = megaphone.cpp

OBJ = $(SRC:%.c = obj/%.o)

all: $(NAME)

obj/%.o: %.c
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

.PHONY: all clean fclean re
