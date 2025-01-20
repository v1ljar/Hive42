#ifndef SO_LONG_H
# define SO_LONG_H

# include "./libft/libft.h"
# include <fcntl.h>
# include "./MLX42/include/MLX42/MLX42.h"

typedef struct s_map_data
{
    char    **map;
    char    **map_dup;
    int     line_len;
    int     rows;
    int     collectibles;
    int     exit_count;
    int     start_count;
    int     player_x;
    int     player_y;
}   t_map_data;

typedef struct s_mlx_key_data
{
    keys_t          key;
    action_t        action;
    int32_t         os_key;
    modifier_key_t  modifier;
}   t_mlx_key_data;

typedef struct s_game_data
{
    mlx_image_t     *image;
    mlx_t           *mlx;
    t_map_data      *data;
    mlx_texture_t   *bg_texture;
    mlx_texture_t   *player_texture;    
    mlx_texture_t   *wall_texture;
    mlx_texture_t   *free_texture;
    mlx_texture_t   *collectible_texture;
    mlx_texture_t   *finish_locked_texture;
    mlx_texture_t   *finish_opened_texture;
    mlx_image_t     *bg_image;
    mlx_image_t     *wall_image;
    mlx_image_t     *free_image;
    mlx_image_t     *collectible_image;
    mlx_image_t     *finish_locked_image;
    mlx_image_t     *finish_opened_image;
    int             moves;
    int             exit_x;
    int             exit_y;
}   t_game_data;

//typedef void (*mlx_keyfunc)(t_mlx_key_data keydata, void *param);
// Map initilizaton
int     ft_validate_map(char *map_path, t_map_data *board);
int     ft_initialize_board(char *map_path, t_map_data *board);
void    ft_initialize_map_data(t_map_data *board, char *whole_map, int lines);
int     ft_validate_parts(t_map_data *board);
int     ft_validate_amount(t_map_data *board);
// Map validation
int     ft_validate_path(t_map_data *board);
void    ft_flood_fill(t_map_data *b, int x, int y, char prev, unsigned char new);
int     ft_path_is_valid(t_map_data *b);
void    ft_free_vector(char **str, int len);

#endif