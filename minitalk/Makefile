NAME = client

NAME_S = server

CC = cc

WFALGS = -Wall -Werror -Wextra

SRC_CLIENT = client.c

SRC_SERVER = server.c

OBJ_CLIENT = $(SRC_CLIENT:%.c=obj_client/%.o)

OBJ_SERVER = $(SRC_SERVER:%.c=obj_server/%.o)

LIBFT = libft.a

LIBFTDIR = ./libft/

all: $(NAME) $(NAME_S)

$(NAME): $(LIBFT) $(OBJ_CLIENT)
	$(CC) $(WFLAGS) $(OBJ_CLIENT) -L./libft -lft -o $@

$(NAME_S): $(LIBFT) $(OBJ_SERVER)
	$(CC) $(WFLAGS) $(OBJ_SERVER) -L./libft -lft  -o $@

obj_client/%.o: %.c
	mkdir -p obj_client
	$(CC) $(WFLAGS) -c $< -o $@

obj_server/%.o: %.c
	mkdir -p obj_server
	$(CC) $(WFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

clean:
	@if [ -d obj_client ]; then \
		rm -rf obj_client; \
	fi
	@if [ -d obj_server ];  then \
		rm -rf obj_server; \
	fi
	$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	$(MAKE) -C $(LIBFTDIR) fclean
	rm -f $(NAME)
	rm -f $(NAME_S)

re: fclean
	all


