# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/30 10:27:08 by jpiensal          #+#    #+#              #
#    Updated: 2025/04/01 11:54:30 by jpiensal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

CC 			= cc
CFLAGS		= -Werror -Wextra -Wall -g

HEADERS		= -I inc/

LIBFT_PATH	= src_libft/
OBJ_PATH	= obj/

LIBFT_SRC	= ft_isascii.c ft_putstr_fd.c ft_strnstr.c ft_atoi.c ft_memmove.c \
	   		ft_strlcat.c ft_isdigit.c ft_split.c ft_strrchr.c ft_bzero.c \
	   		ft_memset.c ft_strlcpy.c ft_isprint.c ft_strchr.c ft_strtrim.c \
	   		ft_calloc.c ft_putchar_fd.c ft_strlen.c ft_itoa.c ft_memchr.c \
	   		ft_strdup.c ft_substr.c ft_isalnum.c ft_putendl_fd.c ft_strmapi.c \
	   		ft_memcmp.c ft_striteri.c ft_tolower.c ft_isalpha.c ft_putnbr_fd.c \
	   		ft_strncmp.c ft_memcpy.c ft_strjoin.c ft_toupper.c ft_atol.c \
			ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_strjoin_n_free.c\
			ft_lstmap.c ft_lstnew.c ft_lstsize.c ft_strcmp.c ft_strrcmp.c \
			ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
			ft_delarray.c ft_strfind_all.c ft_arrlen.c ft_peek_nextchr.c \
			get_next_line.c get_next_line_utils.c ft_split_between.c \
			ft_strspn.c ft_atoll.c

LIBFT_OBJ	= $(LIBFT_SRC:%.c=$(OBJ_PATH)%.o)

RM			= rm -rf

all: 		$(NAME)

$(NAME):	$(OBJ_PATH) $(LIBFT_OBJ)  
			@ar -rcs $@ $(LIBFT_OBJ) 

$(LIBFT_OBJ):	$(OBJ_PATH)%.o: $(LIBFT_PATH)%.c
			@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(OBJ_PATH):
			@if [ ! -d "$(OBJ_PATH)" ]; then mkdir -p $(OBJ_PATH); fi

clean:
			@$(RM) $(OBJ_PATH)
			
fclean:	clean
			@$(RM) $(NAME)

re: 		fclean all

.PHONY: all clean fclean re
