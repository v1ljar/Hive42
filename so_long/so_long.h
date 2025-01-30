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

# include "./libft/libft.h"
# include <fcntl.h>
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
	mlx_image_t		*player_image;
	mlx_t			*mlx;
	t_map_data		*data;
	mlx_texture_t	*bg_texture;
	mlx_texture_t	*player_texture;
	mlx_texture_t	*wall_texture;
	mlx_texture_t	*free_texture;
	mlx_texture_t	*collectible_texture;
	mlx_texture_t	*finish_locked_texture;
	mlx_texture_t	*finish_opened_texture;
	mlx_image_t		*bg_image;
	mlx_image_t		*wall_image;
	mlx_image_t		*free_image;
	mlx_image_t		*collectible_image;
	mlx_image_t		*finish_locked_image;
	mlx_image_t		*finish_opened_image;
	t_collectible	**collectibles_list;
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
}	t_game_data;

// Map initilizaton
int		ft_validate_map(char *map_path, t_map_data *board);
int		ft_initialize_board(char *map_path, t_map_data *board);
void	ft_initialize_map_data(t_map_data *board, char *whole_map, int lines);
int		ft_validate_parts(t_map_data *board);
int		ft_validate_amount(t_map_data *board);

// Map validation
int		ft_validate_path(t_map_data *board);
void	ft_flood_fill(t_map_data *b, int x, int y, char prev);
int		ft_path_is_valid(t_map_data *b);
void	ft_free_vector(char **str, int len);

// Init data
void	ft_init_game_data(t_game_data *game, t_map_data *board);
void	ft_allocate_collectibles_list(t_game_data *game);
void	ft_init_mlx_and_textures(t_game_data *game);

// Init images
void	ft_init_images(t_game_data *game);
void	ft_init_image_list(t_game_data *game);
void	ft_fill_images_list(t_game_data *game);
void	ft_fill_wall_images(t_game_data *game, int *count);
void	ft_fill_images_ex_wall(t_game_data *game, int i, int j, int *count);

// Map on window
void	ft_map_on_window(t_game_data *game);
void	ft_draw_map(t_game_data *game, int y, int x, int *index);
void	ft_init_exit_pos(t_game_data *game, int x, int y);

// Map position
void	ft_map_correct_pos(t_game_data *game);
void	ft_count_offset(t_game_data *game);
void	ft_horizontal_offset(t_game_data *game);
void	ft_vertical_offset(t_game_data *game);

// Adjust image
void	ft_adjust_images(void *param);
void	ft_adjust_image_w(t_game_data *game);
void	ft_adjust_image_s(t_game_data *game);
void	ft_adjust_image_a(t_game_data *game);
void	ft_adjust_image_d(t_game_data *game);

// Keypress
void	my_keyhook(t_mlx_key_data keydata, void *param);
void	ft_keypress_w(t_game_data *game);
void	ft_keypress_s(t_game_data *game);
void	ft_keypress_a(t_game_data *game);
void	ft_keypress_d(t_game_data *game);

// Free delete
void	ft_delete_collectable(t_game_data *game);
void	ft_free_lists(t_game_data *game, int nbr_images, int nbr_coll);
void	ft_free_collectibles(t_game_data *game, int len);
void	ft_free_textures(t_game_data *game);

// Exit
void	ft_escape_exit(t_game_data *game);
void	ft_game_loop_exit(t_game_data *game);
void	ft_free_exit(t_game_data *game);
void	ft_collectible_failed_free(t_game_data *game, int len);
void	ft_init_mlx_failed(t_game_data *game);

#endif
