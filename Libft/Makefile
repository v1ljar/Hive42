NAME = libft.a

CC = gcc

WFLAGS = -Wall -Werror -Wextra

CFILES = $(wildcard *.c)
#ft_isalpha.c ft_isdigit.c ft_strlen.c ft_isalnum.c \
#ft_isascii.c ft_isprint.c ft_memset.c ft_bzero.c ft_memcpy.c \
#ft_memmove.c ft_strlcpy.c

OFILES = $(CFILES:.c=.o)

all: $(NAME)


$(NAME): $(OFILES)
	ar -rcs $(NAME) $(OFILES)

%.o: %.c
	$(CC) $(WFLAGS) -c $< -o $@

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

so:
	-gcc -shared -o libft.so $(OFILES)
