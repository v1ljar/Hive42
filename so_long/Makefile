NAME = so_long

CC = cc

WFLAGS = -Werror -Wextra -Wall -g

LIBFT = libft.a

LIBFTDIR = ./libft/

SRC = so_long.c

all: $(LIBFT) $(NAME)

$(LIBFT): $(LIBFTDIR)
		$(MAKE) -C $<

$(NAME):
		$(CC) $(WFLAGS) -o $(NAME) $(SRC) -L./libft -lft

clean:
		$(MAKE) -C $(LIBFTDIR) clean

fclean:
		@if [ ! -f $(NAME) ]; then \
				echo "make fclean: Nothing to be done for 'fclean'"; \
		else \
				rm -f $(NAME); \
		fi
		$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all