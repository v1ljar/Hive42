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
void    ft_delete_collectable(t_game_data *game);
void    ft_free_instances(t_game_data *game, int len);
void    ft_count_offset(t_game_data *game, int *offset_y, int *offset_x);
void    ft_adjust_screen(t_game_data *game);
void    ft_map_correct_pos(t_game_data *game);
void    ft_fill_images(t_game_data *game);

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
    ft_map_correct_pos(&game);

    mlx_loop_hook(game.mlx, ft_hook, &game);
    mlx_key_hook(game.mlx, (void *)&my_keyhook, &game);

    mlx_loop(game.mlx);
    mlx_terminate(game.mlx);
    ft_free_vector(board.map, board.rows);
    return (EXIT_SUCCESS);
}

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
    game->collected_cols = 0;
    game->collectibles_list = malloc(sizeof(t_collectible *) * game->data->collectibles);
    if (!(game->collectibles_list))
    {
        puts(mlx_strerror(mlx_errno));
        exit (EXIT_FAILURE);
    }
    int i = 0;
    while (i < game->data->collectibles)
    {
        game->collectibles_list[i] = malloc(sizeof(t_collectible));
        if (!(game->collectibles_list[i]))
        {
            ft_free_instances(game, i);
            puts(mlx_strerror(mlx_errno));
            exit (EXIT_FAILURE);
        }
        game->collectibles_list[i]->img = malloc(sizeof(mlx_image_t *));
        if (!(game->collectibles_list[i]->img))
        {
            ft_free_instances(game, i);
            puts(mlx_strerror(mlx_errno));
            exit (EXIT_FAILURE);
        }
        game->collectibles_list[i]->enabled = 1;
        i++;
    }    
}
void ft_set_window_size(t_game_data *game)
{
    if (game->data->rows * 64 > (int)game->win_y && game->data->line_len * 64 > (int)game->win_x)
        mlx_set_window_size(game->mlx, game->win_x, game->win_y);
    else if (game->data->rows * 64 > (int)game->win_y && game->data->line_len * 64 < (int)game->win_x)
        mlx_set_window_size(game->mlx, game->data->line_len * 64, game->win_y);
    else if (game->data->rows * 64 < (int)game->win_y && game->data->line_len * 64 > (int)game->win_x)
        mlx_set_window_size(game->mlx, game->win_x, game->data->rows * 64);
    else
        mlx_set_window_size(game->mlx, game->data->line_len * 64, game->data->rows * 64);
}

void    ft_init_mlx_and_textures(t_game_data *game)
{
    if (!(game->mlx = mlx_init((64 * game->data->line_len), (64 * game->data->rows), "So long GAME", true)))
    {
        puts(mlx_strerror(mlx_errno));
        exit (EXIT_FAILURE);
    }
    
    mlx_get_monitor_size(0, &game->win_x, &game->win_y);
    game->bg_texture = mlx_load_png("./textures/bg_f.png");
    if (!game->bg_texture)
        ft_free_exit(game);
    game->wall_texture = mlx_load_png("./textures/wall_fin_64.png");
    if (!game->wall_texture)
        ft_free_exit(game);
    game->free_texture = mlx_load_png("./textures/free_64.png");
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
    game->player_texture = mlx_load_png("./textures/character_64.png");
    if (!game->player_texture)
        ft_free_exit(game);
}

void    ft_init_images(t_game_data *game)
{
    if (!(game->bg_image = mlx_texture_to_image(game->mlx, game->bg_texture)))
        ft_free_exit(game);    
    mlx_resize_image(game->bg_image, (64 * game->data->line_len), (64 * game->data->rows));

    if (!(game->player_image = mlx_texture_to_image(game->mlx, game->player_texture)))
        ft_free_exit(game);
    if (!(game->wall_image = mlx_texture_to_image(game->mlx, game->wall_texture)))
        ft_free_exit(game);
    if (!(game->free_image = mlx_texture_to_image(game->mlx, game->free_texture)))
        ft_free_exit(game);
    int i = 0;
    while (i < game->data->collectibles)
    {
        game->collectibles_list[i]->img = mlx_texture_to_image(game->mlx, game->collectible_texture);
        if (!game->collectibles_list[i]->img)
            ft_free_exit(game);
        i++;
    }
    if (!(game->finish_opened_image = mlx_texture_to_image(game->mlx, game->finish_opened_texture)))
        ft_free_exit(game);
    if (!(game->finish_locked_image = mlx_texture_to_image(game->mlx, game->finish_locked_texture)))
        ft_free_exit(game);
    game->image_list = malloc(sizeof(t_image_list *) * game->data->images_count);
    if (!(game->image_list))
    {
        ft_free_instances(game, game->data->collectibles);
        puts(mlx_strerror(mlx_errno));
        exit (EXIT_FAILURE);
    }
    i = 0;
    while (i < game->data->images_count)
    {
        game->image_list[i] = malloc(sizeof(t_image_list *));
        game->image_list[i]->img = malloc(sizeof(mlx_image_t));
        if (!(game->image_list[i])->img)
        {
            ft_free_instances(game, game->data->collectibles);
            puts(mlx_strerror(mlx_errno));
            exit (EXIT_FAILURE);
        }
        i++;
    }
    ft_fill_images(game);
}

void    ft_fill_images(t_game_data *game)
{
    int count;
    int i;
    int j;
    
    count = 0;
    i = 0;
    if (!(game->image_list[count++]->img = mlx_texture_to_image(game->mlx, game->bg_texture)))
        ft_free_exit(game);
    while (i < game->data->rows)
    {        
        j = 0;
        while (j < game->data->line_len)
        {
            if (game->data->map[i][j] == '1')
            {
                if (!(game->image_list[count++]->img = mlx_texture_to_image(game->mlx, game->wall_texture)))
                    ft_free_exit(game);
                ft_printf("HERE COUNT: %i\n", count);
            }
            else
            {
                if (!(game->image_list[count++]->img = mlx_texture_to_image(game->mlx, game->free_texture)))
                    ft_free_exit(game);
                if (game->data->map[i][j] == 'C')
                    if (!(game->image_list[count++]->img = mlx_texture_to_image(game->mlx, game->collectible_texture)))
                        ft_free_exit(game);

                if (game->data->map[i][j] == 'E')
                {
                    if (!(game->image_list[count++]->img = mlx_texture_to_image(game->mlx, game->finish_opened_texture)))
                        ft_free_exit(game);

                    if (!(game->image_list[count++]->img = mlx_texture_to_image(game->mlx, game->finish_locked_texture)))
                        ft_free_exit(game);

                }
            }
            j++;
            
        }
        i++;
    }
    
    if (!(game->image_list[count++]->img = mlx_texture_to_image(game->mlx, game->player_texture)))
        ft_free_exit(game);
    ft_printf("HERE COUNT FINAL: %i\n", count);
    ft_printf("HERE2\n");

}

void    ft_free_instances(t_game_data *game, int len)
{
    int i;

    i = 0;
    while (i < len)
    {
        free(game->collectibles_list[i]->img);
        free(game->collectibles_list[i]);
        i++;
    }
    free(game->collectibles_list);
}

void ft_count_offset(t_game_data *game, int *offset_y, int *offset_x)
{
    // Initialize offsets to zero
    *offset_y = 0;
    *offset_x = 0;

    // Calculate vertical offset
    if (game->data->player_y > (int)game->win_y / 64 / 2)
    {
        *offset_y = game->data->player_y - (int)game->win_y / 64 / 2;
        // Ensure the offset does not exceed the map bounds
        if (*offset_y + (int)game->win_y / 64 > game->data->rows)
            *offset_y = game->data->rows - (int)game->win_y / 64;
    }

    // Ensure offset_y is not negative
    if (*offset_y < 0)
        *offset_y = 0;

    // Calculate horizontal offset
    if (game->data->player_x > (int)game->win_x / 64 / 2)
    {
        *offset_x = game->data->player_x - (int)game->win_x / 64 / 2;
        // Ensure the offset does not exceed the map bounds
        if (*offset_x + (int)game->win_x / 64 > game->data->line_len)
            *offset_x = game->data->line_len - (int)game->win_x / 64;
    }

    // Ensure offset_x is not negative
    if (*offset_x < 0)
        *offset_x = 0;

    // Debugging output
    ft_printf("Player position: y: %i, x: %i\n", game->data->player_y, game->data->player_x);
    ft_printf("Map size: rows: %i, line_len: %i\n", game->data->rows, game->data->line_len);
    ft_printf("Window size: win_y: %i, win_x: %i\n", (int)game->win_y / 64, (int)game->win_x / 64);
    ft_printf("Calculated offsets: offset_y: %i, offset_x: %i\n", *offset_y, *offset_x);

    // Adjust image positions based on offsets
    for (int i = 0; i < game->data->images_count; i++)
    {
        if (game->image_list[i] && game->image_list[i]->img)
        {
            game->image_list[i]->img->instances[0].y -= *offset_y * 64; // Adjust Y position
            game->image_list[i]->img->instances[0].x -= *offset_x * 64; // Adjust X position
        }
    }
}

void    ft_map_correct_pos(t_game_data *game)
{
    int offset_y;
    int offset_x;

    offset_y = 0;
    offset_x = 0;
    ft_count_offset(game, &offset_y, &offset_x);
}

void    ft_map_on_window(t_game_data *game)
{
    int i;
    int j;
    int col_count;
    int img_index;

    i = 0;
    img_index = 0;
    col_count = 0;
    ft_printf("Images count: %i\n", game->data->images_count);
    if (mlx_image_to_window(game->mlx, game->image_list[img_index++]->img, game->data->line_len * 64, game->data->rows * 64) < 0)
    {
        ft_free_instances(game, game->data->collectibles);
        puts(mlx_strerror(mlx_errno));
        exit (EXIT_FAILURE);
    }
    ft_printf("HERE\n");
    //while ((i + offset_y) < game->data->rows && i - 1 < game->win_y / 64)
    while (i < game->data->rows)
    {
        j = 0;
        //while ((j + offset_x) < game->data->line_len && j - 1 < game->win_x / 64)
        while (j < game->data->line_len)
        {
            if (game->data->map[i][j] == '1')
            {
                mlx_image_to_window(game->mlx, game->image_list[img_index++]->img, j * 64, i * 64);
            }
            else
            {
                mlx_image_to_window(game->mlx, game->image_list[img_index++]->img, j * 64, i * 64);
                if (game->data->map[i][j] == 'C')
                {
                    
                    mlx_image_to_window(game->mlx, game->collectibles_list[col_count]->img, j * 64, i * 64);
                    game->image_list[img_index++]->img = game->collectibles_list[col_count]->img;
                    game->collectibles_list[col_count]->x = j;
                    game->collectibles_list[col_count++]->y = i;
                }
                if (game->data->map[i][j] == 'E')
                {
                    game->exit_x = j;
                    game->exit_y = i;
                    mlx_image_to_window(game->mlx, game->image_list[img_index++]->img, j * 64, i * 64);
                    mlx_image_to_window(game->mlx, game->image_list[img_index++]->img, j * 64, i * 64);
                }
            }
            j++;
        }
        i++;
    }
    mlx_image_to_window(game->mlx, game->player_image, (64*(game->data->player_x)), (64*(game->data->player_y)));
    game->image_list[img_index++]->img = game->player_image;
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
    
    game = param;
    if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(game->mlx);
}

void    ft_delete_collectable(t_game_data *game)
{
    int i;

    i = 0;
    while (i < game->data->collectibles)
    {
        if (game->collectibles_list[i]->enabled == 1
            && game->collectibles_list[i]->x == game->data->player_x
            && game->collectibles_list[i]->y == game->data->player_y)
        {
            game->collectibles_list[i]->enabled = 0;
            game->collectibles_list[i]->img->instances->enabled = false;
            break;
        }
        i++;
    }
}

void    ft_adjust_screen(t_game_data *game)
{
    if (game->data->rows * 64 > (int)game->win_y || game->data->line_len * 64 > (int)game->win_x)
    {
        int offset_y;
        int offset_x;

        offset_y = 0;
        offset_x = 0;
        ft_count_offset(game, &offset_y, &offset_x);
        //if (offset_y > 0 || offset_y > 0)
            //ft_map_on_window(game);
    }
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
                    game->collected_cols++;
                }
		    game->player_image->instances[0].y -= 64;
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
                    game->collected_cols++;
                }
		    game->player_image->instances[0].y += 64;
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
                    game->collected_cols++;
                }
		    game->player_image->instances[0].x -= 64;
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
                    game->collected_cols++;
                }
		    game->player_image->instances[0].x += 64;
            game->data->player_x++;
            game->moves++;
            
            if (game->data->map[game->data->player_y][game->data->player_x] == 'E')
                ft_game_loop(game);
        }
    }
    ft_delete_collectable(game);
    //ft_adjust_screen(game);
    if (game->data->collectibles == game->collected_cols)
        {
            mlx_delete_image(game->mlx, game->finish_locked_image);
            game->exit_valid = 1;
        }
    if (temp_moves != game->moves)
    {
        ft_printf("You have made %i moves.\n", game->moves);
        //ft_map_on_window(game);
    }
}

void    ft_free_exit(t_game_data *game)
{
    mlx_close_window(game->mlx);
    mlx_terminate(game->mlx);
    ft_free_vector(game->data->map, game->data->rows);
    ft_free_instances(game, game->data->collectibles);
    int i = 0;
    while (i < game->data->images_count)
    {
        free(game->image_list[i++]->img);
    }
    free(game->image_list);
    exit(ft_printf("Error! Failed to allocate memory!\n"));
}
