/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils_map_pos.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:48:41 by vuljas            #+#    #+#             */
/*   Updated: 2025/01/30 13:48:48 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_map_correct_pos(t_game_data *game)
{
	game->offset_y = 0;
	game->offset_x = 0;
	ft_count_offset(game);
}

void	ft_count_offset(t_game_data *game)
{
	int	i;

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

void	ft_vertical_offset(t_game_data *game)
{
	game->offset_y = game->data->player_y - (int)game->win_y / 64;
	if (game->offset_y + ((int)game->win_y / 64) > game->data->rows)
		game->offset_y = game->data->rows - ((int)game->win_y / 64);
}

void	ft_horizontal_offset(t_game_data *game)
{
	game->offset_x = game->data->player_x - (int)game->win_x / 64;
	if (game->offset_x + (int)game->win_x / 64 > game->data->line_len)
		game->offset_x = game->data->line_len - (int)game->win_x / 64;
}
