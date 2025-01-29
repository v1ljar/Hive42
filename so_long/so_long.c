#include "so_long.h"

void    ft_adjust_images(void *param);
void    ft_adjust_image_w(t_game_data *game);
void    ft_adjust_image_s(t_game_data *game);
void    ft_adjust_image_a(t_game_data *game);
void    ft_adjust_image_d(t_game_data *game);

void    ft_game_loop_exit(t_game_data *game);

void    my_keyhook(t_mlx_key_data keydata, void *param);
void    ft_keypress_w(t_game_data *game);
void    ft_keypress_s(t_game_data *game);
void    ft_keypress_a(t_game_data *game);
void    ft_keypress_d(t_game_data *game);
void    ft_delete_collectable(t_game_data *game);
void    ft_escape_exit(t_game_data *game);

void    ft_map_on_window(t_game_data *game);
void    ft_declare_game_data(t_game_data *game, t_map_data *board);
void    ft_init_mlx_and_textures(t_game_data *game);
void    ft_init_images(t_game_data *game);
void    ft_free_exit(t_game_data *game);

void    ft_free_collectibles(t_game_data *game, int len);

void    ft_map_correct_pos(t_game_data *game);
void    ft_count_offset(t_game_data *game);
void    ft_horizontal_offset(t_game_data *game);
void    ft_vertical_offset(t_game_data *game);


void    ft_fill_images_list(t_game_data *game);
void    ft_free_lists(t_game_data *game, int nbr_images, int nbr_coll);

void    ft_allocate_collectibles_list(t_game_data *game);
void    ft_collectible_failed_free(t_game_data *game, int len);

void    ft_init_mlx_failed(t_game_data *game);

void    ft_init_image_list(t_game_data *game);
void    ft_fill_wall_images(t_game_data *game, int *count);
void    ft_fill_images_ex_wall(t_game_data *game, int i, int j, int *count);

void    ft_draw_map(t_game_data *game, int y, int x, int *index);
void    ft_init_exit_pos(t_game_data *game, int x, int y);

void    ft_free_game_data(t_game_data *game);

int main(int argc, char **argv)
{
    t_map_data          board;
    t_game_data         game;

    if (argc != 2 || ft_validate_map(argv[1], &board) == -1)
    {
        ft_free_vector(board.map, board.rows);
        ft_free_vector(board.map_dup, board.rows);
        return (ft_printf("Error! Map is not valid!\n"), 1);
    }
    ft_declare_game_data(&game, &board);    
    ft_init_mlx_and_textures(&game);
    ft_init_images(&game);
    ft_map_on_window(&game);
    ft_map_correct_pos(&game);

    mlx_loop_hook(game.mlx, ft_adjust_images, &game);
    mlx_key_hook(game.mlx, (void *)my_keyhook, &game);

    mlx_loop(game.mlx);
    mlx_close_window(game.mlx);
    mlx_terminate(game.mlx);
    ft_free_vector(game.data->map, game.data->rows);
    return(ft_printf("Exited the game without compiting the game!\n"));
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
    game->bg_win_y = 0;
    game->bg_win_x = 0;
    ft_allocate_collectibles_list(game);
}

void    ft_free_game_data(t_game_data *game)
{
    /*if (game->mlx != NULL)
        free(game->mlx);*/
    if (game->bg_texture != NULL)
        mlx_delete_texture(game->bg_texture);
    if (game->player_texture != NULL)
        mlx_delete_texture(game->player_texture);
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
    int i;

    if (!(game->bg_image = mlx_texture_to_image(game->mlx, game->bg_texture)))
        ft_free_exit(game);    
    mlx_resize_image(game->bg_image, (64 * game->data->line_len), (64 * game->data->rows));
    if (!(game->player_image = mlx_texture_to_image(game->mlx, game->player_texture)))
        ft_free_exit(game);
    if (!(game->wall_image = mlx_texture_to_image(game->mlx, game->wall_texture)))
        ft_free_exit(game);
    if (!(game->free_image = mlx_texture_to_image(game->mlx, game->free_texture)))
        ft_free_exit(game);
    if (!(game->finish_opened_image = mlx_texture_to_image(game->mlx, game->finish_opened_texture)))
        ft_free_exit(game);
    if (!(game->finish_locked_image = mlx_texture_to_image(game->mlx, game->finish_locked_texture)))
        ft_free_exit(game);        
    i = 0;
    while (i < game->data->collectibles)
    {
        game->collectibles_list[i]->img = mlx_texture_to_image(game->mlx, game->collectible_texture);
        if (!game->collectibles_list[i]->img)
            ft_free_exit(game);
        i++;
    }
    ft_init_image_list(game);
    ft_fill_images_list(game);
}

void    ft_init_image_list(t_game_data *game)
{
    int i;

    game->image_list = malloc(sizeof(t_image_list *) * game->data->images_count);
    if (!(game->image_list))
    {
        ft_free_exit(game);
        exit(ft_printf("Error! Images list malloc failed!\n"));
    }
    i = 0;
    while (i < game->data->images_count)
    {
        game->image_list[i] = malloc(sizeof(t_image_list *));
        i++;
    }
}

void    ft_fill_images_list(t_game_data *game)
{
    int count;
    int y;
    int x;
    
    count = 1;
    y = 0;    
    if (!(game->image_list[0]->img = mlx_texture_to_image(game->mlx, game->bg_texture)))
        ft_free_exit(game);
    while (y < game->data->rows)
    {        
        x = 0;
        while (x < game->data->line_len)
        {
            if (game->data->map[y][x] == '1')
                ft_fill_wall_images(game, &count);
            else
                ft_fill_images_ex_wall(game, y, x, &count);
            x++;            
        }
        y++;
    }    
    if (!(game->image_list[count++]->img = mlx_texture_to_image(game->mlx, game->player_texture)))
        ft_free_exit(game);
}

void    ft_fill_wall_images(t_game_data *game, int *count)
{
    int len;

    len = *count;
    if (!(game->image_list[len++]->img = mlx_texture_to_image(game->mlx, game->wall_texture)))
        ft_free_exit(game);
    *count = len;
}

void    ft_fill_images_ex_wall(t_game_data *game, int y, int x, int *count)
{
    int len;

    len = *count;
    if (!(game->image_list[len++]->img = mlx_texture_to_image(game->mlx, game->free_texture)))
        ft_free_exit(game);
    if (game->data->map[y][x] == 'C')
        if (!(game->image_list[len++]->img = mlx_texture_to_image(game->mlx, game->collectible_texture)))
            ft_free_exit(game);
    if (game->data->map[y][x] == 'E')
    {
        if (!(game->finish_opened_image = mlx_texture_to_image(game->mlx, game->finish_opened_texture)))
            ft_free_exit(game);
        game->image_list[len++]->img = game->finish_opened_image;
        if (!(game->finish_locked_image = mlx_texture_to_image(game->mlx, game->finish_locked_texture)))
            ft_free_exit(game);
        game->image_list[len++]->img = game->finish_locked_image;
    }
    *count = len;
}

void    ft_init_exit_pos(t_game_data *game, int x, int y)
{
    game->exit_x = x;
    game->exit_y = y; 
}

void    ft_draw_map(t_game_data *game, int y, int x, int *index)
{
    int img_index;

    img_index = *index;
    if (game->data->map[y][x] == '1')
        mlx_image_to_window(game->mlx, game->image_list[img_index++]->img, x * 64, y * 64);
    else
    {
        mlx_image_to_window(game->mlx, game->image_list[img_index++]->img, x * 64, y * 64);
        if (game->data->map[y][x] == 'C')
        {            
            mlx_image_to_window(game->mlx, game->collectibles_list[game->col_count]->img, x * 64, y * 64);
            game->image_list[img_index++]->img = game->collectibles_list[game->col_count]->img;
            game->collectibles_list[game->col_count]->x = x;
            game->collectibles_list[game->col_count++]->y = y;
        }
        if (game->data->map[y][x] == 'E')
        {
            ft_init_exit_pos(game, x, y);
            mlx_image_to_window(game->mlx, game->image_list[img_index++]->img, x * 64, y * 64);
            mlx_image_to_window(game->mlx, game->image_list[img_index++]->img, x * 64, y * 64);
        }
    }
    *index = img_index;
}

void    ft_map_on_window(t_game_data *game)
{
    int y;
    int x;
    int img_index;

    y = 0;
    img_index = 0;
    game->col_count = 0;
    if (mlx_image_to_window(game->mlx, game->bg_image, 0, 0) < 0)
    {
        ft_free_collectibles(game, game->data->collectibles);        
        exit(ft_printf("Error! Backround to the window failed!\n"));
    }
    game->image_list[img_index++]->img = game->bg_image;
    while (y < game->data->rows)
    {
        x = 0;
        while (x < game->data->line_len)
        {
            ft_draw_map(game, y, x, &img_index);
            x++;
        }
        y++;
    }
    mlx_image_to_window(game->mlx, game->player_image, (64 * game->data->player_x), (64 * game->data->player_y));
    game->image_list[img_index++]->img = game->player_image;
}

void    ft_map_correct_pos(t_game_data *game)
{
    game->offset_y = 0;
    game->offset_x = 0;
    ft_count_offset(game);
}

void    ft_vertical_offset(t_game_data *game)
{
    game->offset_y = game->data->player_y - (int)game->win_y / 64;
    if (game->offset_y + ((int)game->win_y / 64) > game->data->rows)
        game->offset_y = game->data->rows - ((int)game->win_y / 64);
}

void    ft_horizontal_offset(t_game_data *game)
{
    game->offset_x = game->data->player_x - (int)game->win_x / 64;
    if (game->offset_x + (int)game->win_x / 64 > game->data->line_len)
        game->offset_x = game->data->line_len - (int)game->win_x / 64;
}

void ft_count_offset(t_game_data *game)
{
    int i;

    if (game->data->player_y > (int)game->win_y / 64)
        ft_vertical_offset(game);
    if (game->offset_y < 0)
        game->offset_y = 0;
    if (game->data->player_x > (int)game->win_x / 64)
        ft_horizontal_offset(game);
    if (game->offset_x < 0)
        game->offset_x = 0;
    game->player_win_y = game->data->player_y - game->offset_y;
    game->player_win_x = game->data->player_x - game->offset_x;
    game->bg_win_y = game->bg_win_y - game->offset_y;
    game->bg_win_x = game->bg_win_x - game->offset_x;
    i = 0;
    while (i < game->data->images_count)
    {
        if (game->image_list[i] && game->image_list[i]->img)
        {
            game->image_list[i]->img->instances[0].y -= game->offset_y * 64;
            game->image_list[i]->img->instances[0].x -= game->offset_x * 64;
        }
        i++;
    }
}

void    ft_adjust_images(void *param)
{
    t_game_data *game;

    game = param;
    if (mlx_is_key_down(game->mlx, MLX_KEY_W))
    {
        if ((game->player_win_y < ((game->win_y / 64) / 4)) && (int)game->image_list[0]->img->instances[0].y < 0)
            ft_adjust_image_w(game);
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_S))
    {
        if ((game->player_win_y > ((int)game->win_y / 64) * 3 / 4) && !(game->bg_win_y <= (((int)game->win_y / 64) - game->data->rows)))
            ft_adjust_image_s(game);
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_A))
    {
        if ((game->player_win_x < (game->win_x / 64) / 4) && (int)game->image_list[0]->img->instances[0].x < 0)
            ft_adjust_image_a(game);
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_D))
    {
        if ((game->player_win_x > ((int)game->win_x / 64) * 3 / 4) && !(game->bg_win_x <= (((int)game->win_x / 64) - game->data->line_len)))
            ft_adjust_image_d(game);
    }
}

void    ft_adjust_image_w(t_game_data *game)
{
    int i;

    i = 0;
    while (i < game->data->images_count)
        game->image_list[i++]->img->instances[0].y += 64;
    game->player_win_y++;
    game->bg_win_y++;
}

void    ft_adjust_image_s(t_game_data *game)
{
    int i;

    i = 0;
    while (i < game->data->images_count)
        game->image_list[i++]->img->instances[0].y -= 64;
    game->player_win_y--;
    game->bg_win_y--;
}

void    ft_adjust_image_a(t_game_data *game)
{
    int i;

    i = 0;
    while (i < game->data->images_count)
        game->image_list[i++]->img->instances[0].x += 64;
    game->player_win_x++;
    game->bg_win_x++;
}

void    ft_adjust_image_d(t_game_data *game)
{
    int i;

    i = 0;
    while (i < game->data->images_count)
        game->image_list[i++]->img->instances[0].x -= 64;
    game->player_win_x--;
    game->bg_win_x--;
}

void    my_keyhook(t_mlx_key_data keydata, void *param)
{
    t_game_data *game;
    int         temp_moves;

    game = param;
    temp_moves = game->moves;   
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        ft_escape_exit(game);    
    else if (mlx_is_key_down(game->mlx, MLX_KEY_W))
        ft_keypress_w(game);
    else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
    {
        ft_keypress_s(game);
    }
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A))
        ft_keypress_a(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
        ft_keypress_d(game);    
    if (game->data->collectibles == game->collected_cols)
        {
            mlx_delete_image(game->mlx, game->finish_locked_image);
            game->exit_valid = 1;
        }
    if (temp_moves != game->moves)
        ft_printf("You have made %i moves.\n", game->moves);
    ft_delete_collectable(game);
}

void    ft_keypress_w(t_game_data *game)
{
    if (game->data->map[game->data->player_y - 1][game->data->player_x] != '1' && (!(game->data->map[game->data->player_y - 1][game->data->player_x] == 'E' && game->exit_valid == 0)))
    {
        if (game->data->map[game->data->player_y - 1][game->data->player_x] == 'C')
            {
                game->data->map[game->data->player_y - 1][game->data->player_x] = '0';                    
                game->collected_cols++;
            }
        game->player_image->instances[0].y -= 64;
        game->player_win_y--;
        game->data->player_y--;
        game->moves++;
        if (game->data->map[game->data->player_y][game->data->player_x] == 'E')
            ft_game_loop_exit(game);
    }
}

void    ft_keypress_s(t_game_data *game)
{
    if (game->data->map[game->data->player_y + 1][game->data->player_x] != '1' && (!(game->data->map[game->data->player_y + 1][game->data->player_x] == 'E' && game->exit_valid == 0)))
    {
        if (game->data->map[game->data->player_y + 1][game->data->player_x] == 'C')
            {
                game->data->map[game->data->player_y + 1][game->data->player_x] = '0';                   
                game->collected_cols++;
            }
        game->player_image->instances[0].y += 64;
        game->player_win_y++;
        game->data->player_y++;
        game->moves++;
        if (game->data->map[game->data->player_y][game->data->player_x] == 'E')
            ft_game_loop_exit(game);
    }
}

void    ft_keypress_a(t_game_data *game)
{
    if (game->data->map[game->data->player_y][game->data->player_x - 1] != '1' && (!(game->data->map[game->data->player_y][game->data->player_x - 1] == 'E' && game->exit_valid == 0)))
    {
        if (game->data->map[game->data->player_y][game->data->player_x - 1] == 'C')
            {
                game->data->map[game->data->player_y][game->data->player_x - 1] = '0';                    
                game->collected_cols++;
            }
        game->player_image->instances[0].x -= 64;
        game->player_win_x--;
        game->data->player_x--;
        game->moves++;
        if (game->data->map[game->data->player_y][game->data->player_x] == 'E')
            ft_game_loop_exit(game);
    }
}

void    ft_keypress_d(t_game_data *game)
{
    if (game->data->map[game->data->player_y][game->data->player_x + 1] != '1' && (!(game->data->map[game->data->player_y][game->data->player_x + 1] == 'E' && game->exit_valid == 0)))
    {
        if (game->data->map[game->data->player_y][game->data->player_x + 1] == 'C')
            {
                game->data->map[game->data->player_y][game->data->player_x + 1] = '0';                    
                game->collected_cols++;
            }
        game->player_image->instances[0].x += 64;
        game->player_win_x++;
        game->data->player_x++;
        game->moves++;        
        if (game->data->map[game->data->player_y][game->data->player_x] == 'E')
            ft_game_loop_exit(game);
    }
}

void    ft_escape_exit(t_game_data *game)
{
    mlx_close_window(game->mlx);
    mlx_terminate(game->mlx);
    ft_free_game_data(game);
    ft_free_lists(game, game->data->images_count, game->data->collectibles);
    ft_free_vector(game->data->map, game->data->rows);
    exit(ft_printf("Game was closed with ESC!\n"));
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

void    ft_game_loop_exit(t_game_data *game)
{
    mlx_close_window(game->mlx);
    mlx_terminate(game->mlx);
    ft_free_lists(game, game->data->images_count, game->data->collectibles);
    ft_printf("Collectibles collected: %i\n", game->data->collectibles);
    ft_free_vector(game->data->map, game->data->rows);   
    exit(ft_printf("SUCCESS!!! You have completed the map with %i moves. Good job!\n", game->moves));    
}

void    ft_free_exit(t_game_data *game)
{
    mlx_close_window(game->mlx);
    mlx_terminate(game->mlx);
    ft_free_lists(game, game->data->images_count, game->data->collectibles);
    ft_free_vector(game->data->map, game->data->rows);   
    exit(ft_printf("Error! Failed to allocate memory!\n"));
}

void    ft_free_lists(t_game_data *game, int nbr_images, int nbr_coll)
{
    int i;
    
    i = 0;
    while (i < nbr_images)
        free(game->image_list[i++]);
    free(game->image_list);
    i = 0;
    while (i < nbr_coll)
        free(game->collectibles_list[i++]);
    free(game->collectibles_list);
}


void    ft_free_collectibles(t_game_data *game, int len)
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

void    ft_collectible_failed_free(t_game_data *game, int len)
{
    ft_free_vector(game->data->map, game->data->rows);
    ft_free_collectibles(game, len);            
    exit(ft_printf("Error! Collectibles list malloc failed!\n"));
}

void    ft_init_mlx_failed(t_game_data *game)
{
    int i;
    
    i = 0;
    ft_free_vector(game->data->map, game->data->rows);
    ft_free_collectibles(game, game->data->collectibles);    
    while (i < game->data->images_count)
        free(game->image_list[i++]->img);
    free(game->image_list);        
    exit(ft_printf("Error! Window initialization failed!\n"));
}