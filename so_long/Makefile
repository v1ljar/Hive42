NAME = so_long

CC = cc

WFLAGS = -Werror -Wextra -Wall -g

SRC = so_long.c so_long_utils_map_initialization.c so_long_utils_map_validation.c \
	so_long_utils_adjust_image.c so_long_utils_exit.c so_long_utils_free_delete.c \
	so_long_utils_init_data.c so_long_utils_init_images.c so_long_utils_keypress.c \
	so_long_utils_map_pos.c so_long_utils_map_on_window.c so_long_utils_movement.c \
	so_long_utils_assign_textures.c

LIBFT = libft.a

LIBFTDIR = ./libft/

MLX42 = ./MLX42/build/libmlx42.a

all: $(NAME)

$(LIBFT): $(LIBFTDIR)
		$(MAKE) -C $<

$(MLX42):
		@if [ ! -f $(MLX42) ]; then \
				git clone https://github.com/codam-coding-college/MLX42.git; \
				cd MLX42; \
				cmake -B build; \
				cmake --build build -j4; \
				cd ..; \
		else \
				echo "MLX42 library already created!"; \
		fi


$(NAME): $(LIBFT) $(MLX42)
		$(CC) $(WFLAGS) -o $@ $(SRC) -L./libft -lft $(MLX42) -ldl -lglfw -pthread -lm -O3  -msse4.2 -mavx2

clean:
		$(MAKE) -C $(LIBFTDIR) clean

fclean:
		@if [ ! -f $(NAME) ]; then \
				echo "make fclean: Nothing to be done for 'fclean'"; \
		else \
				rm -f $(NAME); \
		fi
		@if [ -d "MLX42" ]; then \
				rm -rf MLX42; \
		fi
		$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re
