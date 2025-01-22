#include "so_long.h"
#include <stdio.h> // For puts!

void    ft_hook(void *param);
void    ft_game_loop(t_game_data *game);
void    my_keyhook(t_mlx_key_data keydata, void *param);
void    ft_map_on_window(t_game_data *game);
void    ft_declare_game_data(t_game_data *game, t_map_data *board);
void    ft_init_mlx_and_textures(t_game_data *game);
void    ft_init_images(t_game_data *game);
void    ft_free_exit(t_game_data *game);

void    ft_declare_game_data(t_game_data *game, t_map_data *board)
{
    game->mlx = NULL;
    game->data = board;    
    game->bg_texture = NULL;
    game->player_texture = NULL;    
    game->wall_texture = NULL;
    game->free_texture = NULL;
    game->collectible_texture = NULL;
    game->finish_locked_texture = NULL;
    game->finish_opened_texture = NULL;
    game->bg_image = NULL;
    game->player_image = NULL;
    game->wall_image = NULL;
    game->free_image = NULL;
    game->collectible_image = NULL;
    game->finish_locked_image = NULL;
    game->finish_opened_image = NULL;
    game->moves = 0;
    game->exit_x = 0;
    game->exit_y = 0;
    game->exit_valid = 0;
}

void    ft_init_mlx_and_textures(t_game_data *game)
{
    if (!(game->mlx = mlx_init((100 * game->data->line_len), (100 * game->data->rows), "So long GAME", true)))
    {
        puts(mlx_strerror(mlx_errno));
        exit (EXIT_FAILURE);
    }
    game->bg_texture = mlx_load_png("./textures/bg_f.png");
    if (!game->bg_texture)
        ft_free_exit(game);
    game->wall_texture = mlx_load_png("./textures/wall_fin.png");
    if (!game->wall_texture)
        ft_free_exit(game);
    game->free_texture = mlx_load_png("./textures/free_f4.png");
    if (!game->free_texture)
        ft_free_exit(game);
    game->collectible_texture = mlx_load_png("./textures/collectable3.png");
    if (!game->collectible_texture)
        ft_free_exit(game);
    game->finish_locked_texture = mlx_load_png("./textures/exit_locked.png");
    if (!game->finish_locked_texture)
        ft_free_exit(game);
    game->finish_opened_texture = mlx_load_png("./textures/exit_opened.png");
    if (!game->finish_opened_texture)
        ft_free_exit(game);
    game->player_texture = mlx_load_png("./textures/character.png");
    if (!game->player_texture)
        ft_free_exit(game);
}

int main(int argc, char **argv)
{
    t_map_data          board;
    t_game_data         game;

    if (argc != 2 || ft_validate_map(argv[1], &board) == -1)
    {
        ft_free_vector(board.map, board.rows);
        ft_free_vector(board.map_dup, board.rows);
        return (ft_printf("Error! Map is not valid!\n"));
    }
    ft_declare_game_data(&game, &board);
    ft_init_mlx_and_textures(&game);
    ft_init_images(&game);
   
    ft_map_on_window(&game);
    
    mlx_loop_hook(game.mlx, ft_hook, &game);
    mlx_key_hook(game.mlx, (void *)&my_keyhook, &game);

    mlx_loop(game.mlx);
    mlx_terminate(game.mlx);
    ft_free_vector(board.map, board.rows);
    return (EXIT_SUCCESS);
}

void    ft_free_exit(t_game_data *game)
{
    mlx_close_window(game->mlx);
    mlx_terminate(game->mlx);
    ft_free_vector(game->data->map, game->data->rows);
    exit(ft_printf("Error! Failed to allocate memory!\n"));
}
void    ft_init_images(t_game_data *game)
{
    if (!(game->bg_image = mlx_texture_to_image(game->mlx, game->bg_texture)))
        ft_free_exit(game);
    if (!(game->player_image = mlx_texture_to_image(game->mlx, game->player_texture)))
        ft_free_exit(game);
    if (!(game->wall_image = mlx_texture_to_image(game->mlx, game->wall_texture)))
        ft_free_exit(game);
    if (!(game->free_image = mlx_texture_to_image(game->mlx, game->free_texture)))
        ft_free_exit(game);
    if (!(game->collectible_image = mlx_texture_to_image(game->mlx, game->collectible_texture)))
        ft_free_exit(game);
    if (!(game->finish_opened_image = mlx_texture_to_image(game->mlx, game->finish_opened_texture)))
        ft_free_exit(game);
    if (!(game->finish_locked_image = mlx_texture_to_image(game->mlx, game->finish_locked_texture)))
        ft_free_exit(game);
    ft_printf("Window x: %i|\ty: %i", game->mlx->window, game->mlx->height);
}
void    ft_map_on_window(t_game_data *game)
{
    int i;
    int j;

    i = 0;
    if (mlx_image_to_window(game->mlx, game->bg_image, 0, 0) < 0)
        ft_free_exit(game);
    while (i < game->data->rows)
    {
        j = 0;
        while (j < game->data->line_len)
        {
            if (game->data->map[i][j] == '1')
            {
                if ((mlx_image_to_window(game->mlx, game->wall_image, j * 100, i * 100)) < 0)
                    ft_free_exit(game);
            }
            else
            {
                if ((mlx_image_to_window(game->mlx, game->free_image, j * 100, i * 100)) < 0)
                    ft_free_exit(game);
                if (game->data->map[i][j] == 'C')
                {
                    if ((mlx_image_to_window(game->mlx, game->collectible_image, j * 100, i * 100)) < 0)
                        ft_free_exit(game);
                }
                if (game->data->map[i][j] == 'E')
                {
                    game->exit_x = game->data->player_x;
                    game->exit_y = game->data->player_y;
                    if (game->exit_valid == 1 && (mlx_image_to_window(game->mlx, game->finish_opened_image, j * 100, i * 100)) < 0)
                        ft_free_exit(game);
                    if (game->exit_valid == 0 && (mlx_image_to_window(game->mlx, game->finish_locked_image, j * 100, i * 100)) < 0)
                        ft_free_exit(game);
                }
            }
            j++;
        }
        i++;
    }
    if (mlx_image_to_window(game->mlx, game->player_image, (100*game->data->player_x), (100*(game->data->player_y))) == -1)
        ft_free_exit(game);
}

void    ft_game_loop(t_game_data *game)
{
    ft_printf("SUCCESS!!! You have completed the map with %i moves. Good job!\n", game->moves);
    mlx_terminate(game->mlx);
    mlx_close_window(game->mlx);
    ft_free_vector(game->data->map, game->data->rows);
    exit (EXIT_SUCCESS);    
}

void    ft_hook(void *param)
{
    t_game_data *game;
    //int i;
    //int j;
    
    game = param;
    if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(game->mlx);
    /*i = 0;
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
    }*/
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
    int         temp_moves;

    game = param;
    temp_moves = game->moves;
    if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
    {
        if (game->data->map[game->data->player_y - 1][game->data->player_x] != '1' && (!(game->data->map[game->data->player_y - 1][game->data->player_x] == 'E' && game->exit_valid == 0)))
        {
            if (game->data->map[game->data->player_y - 1][game->data->player_x] == 'C')
                {
                    game->data->map[game->data->player_y - 1][game->data->player_x] = '0';
                    game->data->collectibles--;
                }
		    //game->player_image->instances[0].y -= 100;
            game->data->player_y--;
            game->moves++;
            if (game->data->map[game->data->player_y][game->data->player_x] == 'E')
                ft_game_loop(game);
        }
    }
    if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
    {
        if (game->data->map[game->data->player_y + 1][game->data->player_x] != '1' && (!(game->data->map[game->data->player_y + 1][game->data->player_x] == 'E' && game->exit_valid == 0)))
        {
            if (game->data->map[game->data->player_y + 1][game->data->player_x] == 'C')
                {
                    game->data->map[game->data->player_y + 1][game->data->player_x] = '0';
                    game->data->collectibles--;
                }
		    //game->player_image->instances[0].y += 100;
            game->data->player_y++;
            game->moves++;
            if (game->data->map[game->data->player_y][game->data->player_x] == 'E')
                ft_game_loop(game);
        }
    }
    if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
	{
        if (game->data->map[game->data->player_y][game->data->player_x - 1] != '1' && (!(game->data->map[game->data->player_y][game->data->player_x - 1] == 'E' && game->exit_valid == 0)))
        {
            if (game->data->map[game->data->player_y][game->data->player_x - 1] == 'C')
                {
                    game->data->map[game->data->player_y][game->data->player_x - 1] = '0';
                    game->data->collectibles--;
                }
		    //game->player_image->instances[0].x -= 100;
            game->data->player_x--;
            game->moves++;
            if (game->data->map[game->data->player_y][game->data->player_x] == 'E')
                ft_game_loop(game);
        }
    }
    if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
	{
        if (game->data->map[game->data->player_y][game->data->player_x + 1] != '1' && (!(game->data->map[game->data->player_y][game->data->player_x + 1] == 'E' && game->exit_valid == 0)))
        {
            if (game->data->map[game->data->player_y][game->data->player_x + 1] == 'C')
                {
                    game->data->map[game->data->player_y][game->data->player_x + 1] = '0';
                    game->data->collectibles--;
                }
		    //game->player_image->instances[0].x += 100;
            game->data->player_x++;
            game->moves++;
            if (game->data->map[game->data->player_y][game->data->player_x] == 'E')
                ft_game_loop(game);
        }
    }
    if (game->data->collectibles == 0)
        game->exit_valid = 1;
    if (temp_moves != game->moves)
    {
        ft_printf("You have made %i moves.\n", game->moves);
        ft_map_on_window(game);
    }
}
