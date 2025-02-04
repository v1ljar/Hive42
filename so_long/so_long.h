/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:40:45 by vuljas            #+#    #+#             */
/*   Updated: 2025/01/30 14:40:50 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include "./libft/libft.h"
# include "./MLX42/include/MLX42/MLX42.h"

typedef struct s_map_data
{
	char	**map;
	char	**map_dup;
	int		line_len;
	int		rows;
	int		collectibles;
	int		exit_count;
	int		start_count;
	int		player_x;
	int		player_y;
	int		images_count;
}	t_map_data;

typedef struct s_mlx_key_data
{
	keys_t			key;
	action_t		action;
	int32_t			os_key;
	modifier_key_t	modifier;
}	t_mlx_key_data;

typedef struct s_collectible
{
	int			x;
	int			y;
	int			enabled;
	mlx_image_t	*img;
}	t_collectible;

typedef struct s_image_list
{
	mlx_image_t	*img;
}	t_image_list;

typedef struct s_game_data
{
	mlx_t			*mlx;
	t_map_data		*data;
	mlx_texture_t	*bg_texture;
	mlx_texture_t	*player_texture;
	mlx_texture_t	*pl_left_texture;
	mlx_texture_t	*pl_right_texture;
	mlx_texture_t	*wall_texture;
	mlx_texture_t	*free_texture;
	mlx_texture_t	*coll_texture;
	mlx_texture_t	*exit_lock_tex;
	mlx_texture_t	*exit_open_tex;
	mlx_image_t		*bg_image;
	mlx_image_t		*player_image;
	mlx_image_t		*pl_lef_img;
	mlx_image_t		*pl_rig_img;
	mlx_image_t		*wall_image;
	mlx_image_t		*free_image;
	mlx_image_t		*collectible_image;
	mlx_image_t		*exit_lock_image;
	mlx_image_t		*exit_open_image;
	t_collectible	**coll_list;
	t_image_list	**image_list;
	int				moves;
	int				exit_x;
	int				exit_y;
	int				exit_valid;
	int				collected_cols;
	int32_t			win_y;
	int32_t			win_x;
	int				player_win_y;
	int				player_win_x;
	int				bg_win_y;
	int				bg_win_x;
	int				col_count;
	int				offset_y;
	int				offset_x;
	int				target_x;
	int				target_y;
	int				is_moving;
	mlx_image_t		*coll_amount;
	int				coll_decrement;
	int				move_size;
}	t_game_data;

// Map initilizaton
int		ft_validate_map(char *map_path, t_map_data *board);

// Map validation
int		ft_validate_path(t_map_data *board);
void	ft_flood_fill(t_map_data *b, int x, int y, char prev);
int		ft_path_is_valid(t_map_data *b);
int		ft_validate_amount(t_map_data *board);

// Init data
void	ft_init_game_data(t_game_data *game, t_map_data *board);
void	ft_init_mlx_and_textures(t_game_data *game);
void	ft_initialize_map_data(t_map_data *board, char *whole_map, int lines,
			char *map_path);

// Init images
void	ft_init_images(t_game_data *game);

// Assign textures
void	ft_init_coll_player_texture(t_game_data *game);
void	ft_player_tex_to_img(t_game_data *g, int count);

// Map on window
void	ft_map_on_window(t_game_data *game);

// Map position
void	ft_map_correct_pos(t_game_data *game);

// Adjust image
void	ft_adjust_images(void *param);

// Keypress
void	my_keyhook(t_mlx_key_data keydata, void *param);

// Movement
void	ft_update_movement(void *param);
void	ft_animate_movement(t_game_data *game, int way);

// Free delete
void	ft_delete_collectable(t_game_data *game);
void	ft_free_lists(t_game_data *game, int nbr_images, int nbr_coll);
void	ft_free_collectibles(t_game_data *game, int len);
void	ft_free_textures(t_game_data *game);
void	ft_free_vector(char **str, int len);

// Exit
void	ft_escape_exit(t_game_data *game);
void	ft_game_loop_exit(t_game_data *game);
void	ft_free_exit(t_game_data *game);
void	ft_collectible_failed_free(t_game_data *game, int len);
void	ft_init_mlx_failed(t_game_data *game);

#endif
