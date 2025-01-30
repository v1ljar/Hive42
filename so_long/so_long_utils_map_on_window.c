/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils_map_on_window.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:49:21 by vuljas            #+#    #+#             */
/*   Updated: 2025/01/30 13:49:27 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_map_on_window(t_game_data *game)
{
	int	y;
	int	x;
	int	img_index;

	y = 0;
	img_index = 0;
	game->col_count = 0;
	if (mlx_image_to_window(game->mlx, game->bg_image, 0, 0) < 0)
	{
		ft_free_collectibles(game, game->data->collectibles);
		exit(ft_printf("Error! Background to the window failed!\n"));
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

void	ft_draw_map(t_game_data *game, int y, int x, int *index)
{
	int	img_index;

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

void	ft_init_exit_pos(t_game_data *game, int x, int y)
{
	game->exit_x = x;
	game->exit_y = y;
}
