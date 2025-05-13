NAME = philo

CC = cc

WFLAGS = -Werror -Wextra -Wall -pthread -g

SRC = philo.c philo_utils.c routines.c philo_actions.c

OBJPATH = obj/

OBJ = $(SRC:%.c=$(OBJPATH)%.o)

all: $(NAME)

$(NAME): $(OBJPATH) $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

$(OBJ): $(OBJPATH)%.o: %.c
	$(CC) $(WFLAGS) -c $< -o $@

$(OBJPATH):
	mkdir -p $(OBJPATH)

clean:
	rm -rf $(OBJ) $(OBJPATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
