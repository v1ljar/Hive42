NAME = so_long

CC = cc

WFLAGS = -Werror -Wextra -Wall -g

SRC = so_long.c so_long_utils_map_initialization.c so_long_utils_map_validation.c

LIBFT = libft.a

LIBFTDIR = ./libft/

all: $(LIBFT) $(NAME)

$(LIBFT): $(LIBFTDIR)
		$(MAKE) -C $<

$(NAME):
		$(CC) $(WFLAGS) -o $@ $(SRC) -L./libft -lft ./MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm

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

.PHONY: all clean fclean re