NAME = libft.a

CC = cc

WFLAGS = -Wall -Werror -Wextra

CFILES = ft_atoi.c ft_putchar_fd.c ft_strlen.c ft_bzero.c ft_putendl_fd.c \
	ft_strmapi.c ft_calloc.c ft_putnbr_fd.c	ft_strncmp.c \
	ft_isalnum.c ft_putstr_fd.c ft_strnstr.c ft_isalpha.c \
	ft_split.c ft_strrchr.c ft_isascii.c ft_strchr.c ft_strtrim.c \
	ft_isdigit.c ft_memchr.c ft_strdup.c ft_substr.c ft_isprint.c \
	ft_memcmp.c ft_striteri.c ft_tolower.c ft_itoa.c ft_memcpy.c \
	ft_strjoin.c ft_toupper.c ft_memmove.c ft_strlcat.c ft_memset.c \
	ft_strlcpy.c ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c \
	ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c \
	ft_lstlast_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c \
	./printf/ft_printf.c ./printf/ft_printf_utils.c

OFILES = $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	ar -rcs $(NAME) $(OFILES)

%.o: %.c
	$(CC) $(WFLAGS) -c $< -o $@

clean:
	rm -f $(OFILES) $(BOFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
