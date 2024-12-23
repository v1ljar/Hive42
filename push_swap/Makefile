NAME = push_swap

CC = cc

WFLAGS = -Wall -Werror -Wextra

SRC = push_swap.c push_swap_utils.c

LIBNAME = libft.a

LIBDIR = ./libft/

all: $(LIBNAME) $(NAME)

$(LIBNAME): $(LIBDIR)
	$(MAKE) -C $<

$(NAME):
	$(CC) $(WFLAGS) $(SRC) -o $(NAME) -L./libft -lft

clean:
	$(MAKE) -C $(LIBDIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBDIR) fclean

re: fclean all

.PHONY: all clean fclean re
