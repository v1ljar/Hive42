#include "so_long.h"

void    ft_init_game_data(t_game_data *game, t_map_data *board)
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
    game->player_left_image = NULL;
    game->player_right_image = NULL;
    game->wall_image = NULL;
    game->free_image = NULL;
    game->collectible_image = NULL;
    game->finish_locked_image = NULL;
    game->finish_opened_image = NULL;
    game->moves = 0;
    game->exit_x = 0;
    game->exit_y = 0;
    game->exit_valid = 0;
    game->collected_cols = 0;
    game->bg_win_y = 0;
    game->bg_win_x = 0;
    ft_allocate_collectibles_list(game);
}

void    ft_free_game_data(t_game_data *game)
{
    if (game->bg_texture != NULL)
        mlx_delete_texture(game->bg_texture);
    if (game->player_texture != NULL)
        mlx_delete_texture(game->player_texture);
    if (game->player_left_texture != NULL)
        mlx_delete_texture(game->player_left_texture);
    if (game->player_right_texture != NULL)
        mlx_delete_texture(game->player_right_texture);
    if (game->wall_texture != NULL)
        mlx_delete_texture(game->wall_texture);
    if (game->free_texture != NULL)
        mlx_delete_texture(game->free_texture);
    if (game->collectible_texture != NULL)
        mlx_delete_texture(game->collectible_texture);
    if (game->finish_locked_texture != NULL)
        mlx_delete_texture(game->finish_locked_texture);
    if (game->finish_opened_texture != NULL)
        mlx_delete_texture(game->finish_opened_texture);
}

void    ft_allocate_collectibles_list(t_game_data *game)
{
    int i;

    i = 0;
    game->collectibles_list = malloc(sizeof(t_collectible *) * game->data->collectibles);
    if (!(game->collectibles_list))
    {
        ft_free_vector(game->data->map, game->data->rows);        
        exit(ft_printf("Error! Collectibles list malloc failed!\n"));
    }
    while (i < game->data->collectibles)
    {
        game->collectibles_list[i] = malloc(sizeof(t_collectible));
        if (!(game->collectibles_list[i]))
            ft_collectible_failed_free(game, i);
        game->collectibles_list[i]->enabled = 1;
        i++;
    }
    game->is_moving = 0;
}

void    ft_init_mlx_and_textures(t_game_data *game)
{
    if (!(game->mlx = mlx_init((64 * game->data->line_len), (64 * game->data->rows), "So long GAME", true)))
        ft_init_mlx_failed(game);
    mlx_get_monitor_size(0, &game->win_x, &game->win_y);
    game->bg_texture = mlx_load_png("./textures/bg_f.png");
    if (!game->bg_texture)
        ft_free_exit(game);
    game->wall_texture = mlx_load_png("./textures/wall_fin_64.png");
    if (!game->wall_texture)
        ft_free_exit(game);
    game->free_texture = mlx_load_png("./textures/free_64_2.png");
    if (!game->free_texture)
        ft_free_exit(game);
    game->collectible_texture = mlx_load_png("./textures/collectable_64.png");
    if (!game->collectible_texture)
        ft_free_exit(game);
    game->finish_locked_texture = mlx_load_png("./textures/exit_locked_64.png");
    if (!game->finish_locked_texture)
        ft_free_exit(game);
    game->finish_opened_texture = mlx_load_png("./textures/exit_opened_64.png");
    if (!game->finish_opened_texture)
        ft_free_exit(game);
    game->player_texture = mlx_load_png("./textures/player_64_2.png");
    if (!game->player_texture)
        ft_free_exit(game);
    game->player_left_texture = mlx_load_png("./textures/player_left_64.png");
    if (!game->player_left_texture)
        ft_free_exit(game);
    game->player_right_texture = mlx_load_png("./textures/player_right_64.png");
    if (!game->player_right_texture)
        ft_free_exit(game);
}
