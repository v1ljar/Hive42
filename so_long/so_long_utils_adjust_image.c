/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils_adjust_image.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:49:53 by vuljas            #+#    #+#             */
/*   Updated: 2025/01/30 13:49:58 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_adjust_images(void *param)
{
	t_game_data	*game;

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

void	ft_adjust_image_w(t_game_data *game)
{
	int	i;

	i = 0;
	while (i < game->data->images_count)
		game->image_list[i++]->img->instances[0].y += 64;
	game->player_win_y++;
	game->bg_win_y++;
}

void	ft_adjust_image_s(t_game_data *game)
{
	int	i;

	i = 0;
	while (i < game->data->images_count)
		game->image_list[i++]->img->instances[0].y -= 64;
	game->player_win_y--;
	game->bg_win_y--;
}

void	ft_adjust_image_a(t_game_data *game)
{
	int	i;

	i = 0;
	while (i < game->data->images_count)
		game->image_list[i++]->img->instances[0].x += 64;
	game->player_win_x++;
	game->bg_win_x++;
}

void	ft_adjust_image_d(t_game_data *game)
{
	int	i;

	i = 0;
	while (i < game->data->images_count)
		game->image_list[i++]->img->instances[0].x -= 64;
	game->player_win_x--;
	game->bg_win_x--;
}
