NAME = push_swap

CC = cc

WFLAGS = -Wall -Werror -Wextra

SRC = push_swap.c push_swap_utils_fill_stack_a.c push_swap_utils_check_stack.c \
	push_swap_utils_sort.c push_swap_utils_sort_make_moves.c push_swap_utils_sort_b_pos.c \
	push_swap_utils_a_moves.c push_swap_utils_b_moves.c

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
