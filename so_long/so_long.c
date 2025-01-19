#include "so_long.h"
#include <stdio.h> // For puts!

void    ft_hook(void *param);
void    my_keyhook(t_mlx_key_data keydata, void *param);
void    ft_map_on_window(t_game_data *game);

int main(int argc, char **argv)
{
    t_map_data          board;

    t_game_data         game;

    if (argc != 2 || ft_validate_map(argv[1], &board) == -1)
    {
        ft_free_vector(board.map, board.rows);
        ft_free_vector(board.map_dup, board.rows);
        return (ft_printf("Error\n"));
    }
    game.data = &board;
    if (!(game.mlx = mlx_init((100 * board.line_len), (100 * board.rows), "So long GAME", true)))
    {
        puts(mlx_strerror(mlx_errno));
        return (EXIT_FAILURE);
    }
    game.bg_texture = mlx_load_png("./textures/bg.png");
    if (!game.bg_texture)
    {
        mlx_close_window(game.mlx);
        puts(mlx_strerror(mlx_errno));
        return (EXIT_FAILURE);
    }
    if (!(game.bg_image = mlx_texture_to_image(game.mlx, game.bg_texture)))
    {
        mlx_close_window(game.mlx);
        puts(mlx_strerror(mlx_errno));
        return (EXIT_FAILURE);
    }
    if (mlx_image_to_window(game.mlx, game.bg_image, 0, 0) < 0)
    {
        mlx_close_window(game.mlx);
        puts(mlx_strerror(mlx_errno));
        return (EXIT_FAILURE);
    }
    game.wall_texture = mlx_load_png("./textures/wall3.png");
    if (!game.wall_texture)
    {
        mlx_close_window(game.mlx);
        puts(mlx_strerror(mlx_errno));
        return (EXIT_FAILURE);
    }
    game.free_texture = mlx_load_png("./textures/free3.png");
    if (!game.free_texture)
    {
        mlx_close_window(game.mlx);
        puts(mlx_strerror(mlx_errno));
        return (EXIT_FAILURE);
    }
    game.collectible_texture = mlx_load_png("./textures/collectible.png");
    if (!game.collectible_texture)
    {
        mlx_close_window(game.mlx);
        puts(mlx_strerror(mlx_errno));
        return (EXIT_FAILURE);
    }
    game.finish_texture = mlx_load_png("./textures/exit3.png");
    if (!game.finish_texture)
    {
        mlx_close_window(game.mlx);
        puts(mlx_strerror(mlx_errno));
        return (EXIT_FAILURE);
    }
    ft_map_on_window(&game);

    
    
    game.player_texture = mlx_load_png("./textures/character.png");
    if (!game.player_texture)
    {
        mlx_close_window(game.mlx);
        puts(mlx_strerror(mlx_errno));
        return (EXIT_FAILURE);
    }
    if (!(game.image = mlx_texture_to_image(game.mlx, game.player_texture)))
    {
        mlx_close_window(game.mlx);
        puts(mlx_strerror(mlx_errno));
        return (EXIT_FAILURE);
    }
    if (mlx_image_to_window(game.mlx, game.image, (100*board.player_x), (100*(board.player_y))) == -1)
    {
        mlx_close_window(game.mlx);
        puts(mlx_strerror(mlx_errno));
        return (EXIT_FAILURE);
    }
    mlx_loop_hook(game.mlx, ft_hook, &game);
    mlx_key_hook(game.mlx, (void *)&my_keyhook, &game);

    mlx_loop(game.mlx);
    mlx_terminate(game.mlx);
    ft_free_vector(board.map, board.rows);
    return (EXIT_SUCCESS);
}

void    ft_map_on_window(t_game_data *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->data->rows)
    {
        j = 0;
        while (j < game->data->line_len)
        {
            if (game->data->map[i][j] == '1')
            {
                game->wall_image = mlx_texture_to_image(game->mlx, game->wall_texture);
                if (!game->wall_image || mlx_image_to_window(game->mlx, game->wall_image, j * 100, i * 100))
                {
                    mlx_close_window(game->mlx);
                    puts(mlx_strerror(mlx_errno));
                    return ;
                }
            }
            else
            {
                game->free_image = mlx_texture_to_image(game->mlx, game->free_texture);
                if (!game->free_image || mlx_image_to_window(game->mlx, game->free_image, j * 100, i * 100))
                {
                    mlx_close_window(game->mlx);
                    puts(mlx_strerror(mlx_errno));
                    return ;
                }
                if (game->data->map[i][j] == 'C')
                {
                    game->collectible_image = mlx_texture_to_image(game->mlx, game->collectible_texture);
                    if (!game->collectible_image || mlx_image_to_window(game->mlx, game->collectible_image, j * 100, i * 100))
                    {
                        mlx_close_window(game->mlx);
                        puts(mlx_strerror(mlx_errno));
                        return ; 
                    }
                }
                if (game->data->map[i][j] == 'E')
                {
                    game->finish_image = mlx_texture_to_image(game->mlx, game->finish_texture);
                    if (!game->finish_image || mlx_image_to_window(game->mlx, game->finish_image, j * 100, i * 100))
                    {
                        mlx_close_window(game->mlx);
                        puts(mlx_strerror(mlx_errno));
                        return ; 
                    }
                }
            }
            j++;
        }
        i++;
    }
}

void    ft_hook(void *param)
{
    t_game_data *game;
    int i;
    int j;
    
    game = param;
    if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(game->mlx);
    i = 0;
    while (i < game->data->rows)
    {
        j = 0;
        while (j < game->data->line_len)
        {
            if (game->data->map[i][j] == 'C')
            {
                mlx_image_to_window(game->mlx, game->collectible_image, j * 100, i * 100);
            }
            else if (game->data->map[i][j] == '0')
                mlx_image_to_window(game->mlx, game->free_image, j * 100, i *100);
            j++;
        }
        i++;
    }
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
    t_game_data *game;

    game = param;
    if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
    {
        ft_printf("Player y: %d\tPlayer x: %d\n", game->data->player_y, game->data->player_x);

        if (game->data->map[game->data->player_y - 1][game->data->player_x] != '1')
        {
            if (game->data->map[game->data->player_y - 1][game->data->player_x] == 'C')
                {
                    game->data->map[game->data->player_y - 1][game->data->player_x] = '0';
                    game->data->collectibles--;
                    ft_printf("Collectibles: %d\n", game->data->collectibles);
                }
		    game->image->instances[0].y -= 100;
            game->data->player_y--;
        }
    }
    if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
    {
        if (game->data->map[game->data->player_y + 1][game->data->player_x] != '1')
        {
            if (game->data->map[game->data->player_y + 1][game->data->player_x] == 'C')
                {
                    game->data->map[game->data->player_y + 1][game->data->player_x] = '0';
                    game->data->collectibles--;
                    ft_printf("Collectibles: %d\n", game->data->collectibles);
                }
		    game->image->instances[0].y += 100;
            game->data->player_y++;
        }
    }
    if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
	{
        if (game->data->map[game->data->player_y][game->data->player_x - 1] != '1')
        {
            if (game->data->map[game->data->player_y][game->data->player_x - 1] == 'C')
                {
                    game->data->map[game->data->player_y][game->data->player_x - 1] = '0';
                    game->data->collectibles--;
                    ft_printf("Collectibles: %d\n", game->data->collectibles);
                }
		    game->image->instances[0].x -= 100;
            game->data->player_x--;
        }
    }
    if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
	{
        if (game->data->map[game->data->player_y][game->data->player_x + 1] != '1')
        {
            if (game->data->map[game->data->player_y][game->data->player_x + 1] == 'C')
                {
                    game->data->map[game->data->player_y][game->data->player_x + 1] = '0';
                    game->data->collectibles--;
                    ft_printf("Collectibles: %d\n", game->data->collectibles);
                }
		    game->image->instances[0].x += 100;
            game->data->player_x++;
        }
    }
}
