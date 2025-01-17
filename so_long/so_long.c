#include "so_long.h"
#include <stdio.h> // For puts!

void    ft_hook(void *param);
void    my_keyhook(t_mlx_key_data keydata, void *param);

int main(int argc, char **argv)
{
    t_map_data          board;
    mlx_t               *mlx;
    mlx_texture_t       *bg_texture;
    mlx_texture_t       *player_texture;
    static mlx_image_t  *bg_image;

    if (argc != 2 || ft_validate_map(argv[1], &board) == -1)
    {
        ft_free_vector(board.map, board.rows);
        ft_free_vector(board.map_dup, board.rows);
        return (ft_printf("Error\n"));
    }
    if (!(mlx = mlx_init((128*(board.line_len + 3)), (128*(board.rows + 2)), "So long GAME", true)))
    {
        puts(mlx_strerror(mlx_errno));
        return (EXIT_FAILURE);
    }
    bg_texture = mlx_load_png("./textures/bg2.png");
    if (!bg_texture)
    {
        mlx_close_window(mlx);
        puts(mlx_strerror(mlx_errno));
        return (EXIT_FAILURE);
    }
    if (!(bg_image = mlx_texture_to_image(mlx, bg_texture)))
    {
        mlx_close_window(mlx);
        puts(mlx_strerror(mlx_errno));
        return (EXIT_FAILURE);
    }
    if (mlx_image_to_window(mlx, bg_image, 0, 0) < 0)
    {
        mlx_close_window(mlx);
        puts(mlx_strerror(mlx_errno));
        return (EXIT_FAILURE);
    }
    player_texture = mlx_load_png("./textures/player.png");
    if (!player_texture)
    {
        mlx_close_window(mlx);
        puts(mlx_strerror(mlx_errno));
        return (EXIT_FAILURE);
    }
    if (!(image = mlx_texture_to_image(mlx, player_texture)))
    {
        mlx_close_window(mlx);
        puts(mlx_strerror(mlx_errno));
        return (EXIT_FAILURE);
    }
    if (mlx_image_to_window(mlx, image, (128*(board.player_x + 1)), (128*(board.player_y + 1))) == -1)
    {
        mlx_close_window(mlx);
        puts(mlx_strerror(mlx_errno));
        return (EXIT_FAILURE);
    }
    mlx_loop_hook(mlx, ft_hook, mlx);
    mlx_key_hook(mlx, (void *)&my_keyhook, NULL);

    mlx_loop(mlx);
    mlx_terminate(mlx);
    ft_free_vector(board.map, board.rows);
    return (EXIT_SUCCESS);
}

void    ft_hook(void *param)
{
    mlx_t               *mlx;

    mlx = param;
    if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
        mlx_close_window(mlx);
    /*if (mlx_is_key_down(mlx, MLX_KEY_UP))
        image->instances[0].y -= 50;
    if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
        image->instances[0].y += 50;
    if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
        image->instances[0].x -= 50;
    if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
        image->instances[0].x += 50;*/
}

void    my_keyhook(t_mlx_key_data keydata, void *param)
{
    mlx_t               *mlx;

    mlx = param;
    if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		image->instances[0].y -= 128;
    if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		image->instances[0].y += 128;
    if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		image->instances[0].x -= 128;
    if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		image->instances[0].x += 128;
}
