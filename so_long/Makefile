NAME = so_long

CC = cc

WFLAGS = -Werror -Wextra -Wall

MLXFLAGS = -ldl -lglfw -pthread -lm -O3  -msse4.2 -mavx2

SRC = so_long.c so_long_utils_map_initialization.c so_long_utils_map_validation.c \
	so_long_utils_adjust_image.c so_long_utils_exit.c so_long_utils_free_delete.c \
	so_long_utils_init_data.c so_long_utils_init_images.c so_long_utils_keypress.c \
	so_long_utils_map_pos.c so_long_utils_map_on_window.c so_long_utils_movement.c \
	so_long_utils_assign_textures.c

OBJ = $(SRC:%.c=obj/%.o)

LIBFT = libft.a

LIBFTDIR = ./libft/

MLX42 = ./MLX42/build/libmlx42.a

all: $(MLX42) $(LIBFT) $(NAME)

obj/%.o: %.c
		mkdir -p obj
		$(CC) $(WFLAGS) -c $< -o $@

$(LIBFT): 
		@if [ ! -f $(LIBFT) ]; then \
			$(MAKE) -C $(LIBFTDIR); \
		else \
			echo "Libft up to date!"; \
		fi

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


$(NAME): $(MLX42) $(LIBFT) $(OBJ)  
		@if [ ! -f $(NAME) ] || [ -n "$(OBJ)" ]; then \
			$(CC) $(WFLAGS) -o $@ $(OBJ) -L./libft -lft $(MLX42) $(MLXFLAGS); \
		else \
			echo "make: Nothing to be done for 'make'"; \
		fi

clean:
		$(MAKE) -C $(LIBFTDIR) clean
		@if [ -d obj ]; then \
			rm -rf obj; \
		else \
			echo "make: Nothing to be done for 'make clean'"; \
		fi

fclean:
		@if [ ! -f $(NAME) ]; then \
				echo "make fclean: Nothing to be done for 'fclean'"; \
		else \
				rm -f $(NAME); \
		fi
		@if [ -d "MLX42" ]; then \
				rm -rf MLX42; \
		fi
		@if [ -d obj ]; then \
			rm -rf obj; \
		fi
		$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re
