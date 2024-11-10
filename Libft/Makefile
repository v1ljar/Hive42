NAME = libft.a

CC = gcc

WFLAGS = -Wall -Werror -Wextra

CFILES = $(shell ls ./*.c | ls --hide="*_bonus.c")

OFILES = $(CFILES:.c=.o)

BFILES = $(shell ls ./*_bonus.c)

BOFILES = $(BFILES:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	ar -rcs $(NAME) $(OFILES)

%.o: %.c
	$(CC) $(WFLAGS) -c $< -o $@

bonus: $(NAME) $(BOFILES)
	ar -rcs $(NAME) $(BOFILES)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

so:
	-gcc -shared -o libft.so $(shell ls ./*.o)
