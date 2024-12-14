NAME = push_swap

LIBNAME = libftprintf.a

LIBDIR = ./includes/

CC = cc

WFLAGS = -Wall -Werror -Wextra

SRC = push_swap.c

all: $(LIBNAME) $(NAME)

$(LIBNAME): $(LIBDIR)
	$(MAKE) -C $<

$(NAME):
	$(CC) $(WFLAGS) -o $@ $(SRC) -L./includes -lftprintf

clean:
	$(MAKE) -C $(LIBDIR) clean

fclean:
	rm -f $(NAME)
	$(MAKE) -C $(LIBDIR) fclean

re: fclean $(NAME)
	$(MAKE) -C $(LIBDIR) re

.PHONY: all clean fclean re