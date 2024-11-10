NAME = libft.a

CC = gcc

WFLAGS = -Wall -Werror -Wextra

CFILES = $(shell ls ./*.c | ls --hide="*_bonus.c")

OFILES = $(CFILES:.c=.o)

BFILES = $(shell ls ./*_bonus.c)
<<<<<<< HEAD
=======

BOFILES = $(BFILES:.c=.o)

all: $(NAME)
>>>>>>> 338b55019fff64a411233e65d8a8b1c09a21950b

BOFILES = $(BFILES:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	ar -rcs $(NAME) $(OFILES)

%.o: %.c
	$(CC) $(WFLAGS) -c $< -o $@

<<<<<<< HEAD
bonus: $(NAME) $(BOFILES)
=======
bonus: $(BOFILES)
>>>>>>> 338b55019fff64a411233e65d8a8b1c09a21950b
	ar -rcs $(NAME) $(BOFILES)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

so:
	-gcc -shared -o libft.so $(shell ls ./*.o)
