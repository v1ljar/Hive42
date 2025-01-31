/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils_keypress.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:50:44 by vuljas            #+#    #+#             */
/*   Updated: 2025/01/30 13:50:47 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	my_keyhook(t_mlx_key_data keydata, void *param)
{
	t_game_data	*game;
	int			temp_moves;

	game = param;
	temp_moves = game->moves;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		ft_escape_exit(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_W) && game->is_moving == 0)
		ft_keypress_w(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S) && game->is_moving == 0)
	{
		ft_keypress_s(game);
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A) && game->is_moving == 0)
		ft_keypress_a(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D) && game->is_moving == 0)
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

void	ft_keypress_w(t_game_data *game)
{
	if (game->data->map[game->data->player_y - 1][game->data->player_x] != '1' &&
		(!(game->data->map[game->data->player_y - 1][game->data->player_x] == 'E' &&
		game->exit_valid == 0)))
	{
		if (game->data->map[game->data->player_y - 1][game->data->player_x] == 'C')
		{
			game->data->map[game->data->player_y - 1][game->data->player_x] = '0';
			game->collected_cols++;
		}
		game->player_image->instances[0].y -= 64;
		game->player_left_image->instances[0].y -= 64;
		game->player_right_image->instances[0].y -= 64;
		game->player_win_y--;
		game->data->player_y--;
		game->moves++;
		if (game->data->map[game->data->player_y][game->data->player_x] == 'E')
			ft_game_loop_exit(game);
	}
}

void	ft_keypress_s(t_game_data *game)
{
	if (game->data->map[game->data->player_y + 1][game->data->player_x] != '1' &&
		(!(game->data->map[game->data->player_y + 1][game->data->player_x] == 'E' &&
		game->exit_valid == 0)))
	{
		if (game->data->map[game->data->player_y + 1][game->data->player_x] == 'C')
		{
			game->data->map[game->data->player_y + 1][game->data->player_x] = '0';
			game->collected_cols++;
		}
		game->player_image->instances[0].y += 64;
		game->player_left_image->instances[0].y += 64;
		game->player_right_image->instances[0].y += 64;
		game->player_win_y++;
		game->data->player_y++;
		game->moves++;
		if (game->data->map[game->data->player_y][game->data->player_x] == 'E')
			ft_game_loop_exit(game);
	}
}

void	ft_update_movement(void *param)
{
	t_game_data	*game;

	game = param;
	if (game->is_moving == 1)
	{

		if (game->player_left_image->instances[0].x > game->player_right_image->instances[0].x)
			game->player_left_image->instances[0].x -= 8;
		else
		{
			game->is_moving = 0;
			game->player_left_image->instances[0].enabled = false;
			game->player_image->instances[0].enabled = true;
			game->target_x = 0;
		}
	}
	if (game->is_moving == 2)
	{
		if (game->player_right_image->instances[0].x < game->player_left_image->instances[0].x)
			game->player_right_image->instances[0].x += 8;
		else
		{
			game->is_moving = 0;
			game->player_right_image->instances[0].enabled = false;
			game->player_image->instances[0].enabled = true;
			game->target_x = 0;
		}
	}
}

void	ft_animate_movement(t_game_data *game, int way)
{
	if (way == 1)
	{
		game->target_x = game->player_left_image->instances[0].x - 64;
		game->is_moving = 1;
	}
	if (way == 2)
	{
		game->target_x = game->player_right_image->instances[0].x + 64;
		game->is_moving = 2;
	}
}

void	ft_keypress_a(t_game_data *game)
{
	if (game->data->map[game->data->player_y][game->data->player_x - 1] != '1' &&
		(!(game->data->map[game->data->player_y][game->data->player_x - 1] == 'E' &&
		game->exit_valid == 0)))
	{
		if (game->data->map[game->data->player_y][game->data->player_x - 1] == 'C')
		{
			game->data->map[game->data->player_y][game->data->player_x - 1] = '0';
			game->collected_cols++;
		}
		game->player_image->instances[0].enabled = false;
		game->player_left_image->instances[0].enabled = true;
		//game->player_left_image->instances[0].x -= 64;
		game->player_right_image->instances[0].x -= 64;
		game->player_image->instances[0].x -= 64;
		ft_animate_movement(game, 1);
		
		game->player_win_x--;
		game->data->player_x--;
		game->moves++;
		if (game->data->map[game->data->player_y][game->data->player_x] == 'E')
			ft_game_loop_exit(game);
	}
}

void	ft_keypress_d(t_game_data *game)
{
	if (game->data->map[game->data->player_y][game->data->player_x + 1] != '1' &&
		(!(game->data->map[game->data->player_y][game->data->player_x + 1] == 'E' &&
		game->exit_valid == 0)))
	{
		if (game->data->map[game->data->player_y][game->data->player_x + 1] == 'C')
		{
			game->data->map[game->data->player_y][game->data->player_x + 1] = '0';
			game->collected_cols++;
		}
		game->player_image->instances[0].enabled = false;
		game->player_right_image->instances[0].enabled = true;
		game->player_left_image->instances[0].x += 64;
		//game->player_right_image->instances[0].x += 64;
		game->player_image->instances[0].x += 64;
		ft_animate_movement(game, 2);
		//game->player_right_image->instances[0].enabled = false;
		//game->player_image->instances[0].enabled = true;
		game->player_win_x++;
		game->data->player_x++;
		game->moves++;
		if (game->data->map[game->data->player_y][game->data->player_x] == 'E')
			ft_game_loop_exit(game);
	}
}
