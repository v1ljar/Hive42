NAME = libftprintf.a

LIBNAME = libft.a

LIBDIR = ./libft/

CC = cc

WFLAGS = -Wall -Werror -Wextra

SRC = ft_printf.c  ft_printf_utils.c

OBJ = $(SRC:.c=.o)

all: $(LIBNAME) $(NAME)

$(LIBNAME): $(LIBDIR)
	$(MAKE) -C $<

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

.o: .c
	$(CC) $(WFLAGS) -c $< -o $@ -L./libft -lft

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBDIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBDIR) fclean

re: fclean $(NAME)
	$(MAKE) -C $(LIBDIR) re

.PHONY: all clean fclean re test
