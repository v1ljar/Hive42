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

static void	ft_adjust_image_w(t_game_data *game);
static void	ft_adjust_image_s(t_game_data *game);
static void	ft_adjust_image_a(t_game_data *game);
static void	ft_adjust_image_d(t_game_data *game);

void	ft_adjust_images(void *param)
{
	t_game_data	*g;

	g = param;
	if (mlx_is_key_down(g->mlx, MLX_KEY_W))
		ft_adjust_image_w(g);
	if (mlx_is_key_down(g->mlx, MLX_KEY_S))
	{
		if ((g->player_win_y > ((int)g->win_y / 64) * 3 / 4)
			&& !(g->bg_win_y <= (((int)g->win_y / 64) - g->data->rows)))
			ft_adjust_image_s(g);
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_A))
	{
		if ((g->player_win_x < (g->win_x / 64) / 4)
			&& (int)g->image_list[0]->img->instances[0].x < 0)
			ft_adjust_image_a(g);
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_D))
	{
		if ((g->player_win_x > ((int)g->win_x / 64) * 3 / 4)
			&& !(g->bg_win_x <= (((int)g->win_x / 64) - g->data->line_len)))
			ft_adjust_image_d(g);
	}
}

static void	ft_adjust_image_w(t_game_data *game)
{
	int	i;

	i = 0;
	if ((game->player_win_y < ((game->win_y / 64) / 4))
		&& (int)game->bg_image->instances[0].y < 0)
	{
		while (i < game->data->images_count)
			game->image_list[i++]->img->instances[0].y += 64;
		game->player_win_y++;
		game->bg_win_y++;
	}
}

static void	ft_adjust_image_s(t_game_data *game)
{
	int	i;

	i = 0;
	while (i < game->data->images_count)
		game->image_list[i++]->img->instances[0].y -= 64;
	game->player_win_y--;
	game->bg_win_y--;
}

static void	ft_adjust_image_a(t_game_data *game)
{
	int	i;

	i = 0;
	while (i < game->data->images_count)
		game->image_list[i++]->img->instances[0].x += 64;
	game->player_win_x++;
	game->bg_win_x++;
}

static void	ft_adjust_image_d(t_game_data *game)
{
	int	i;

	i = 0;
	while (i < game->data->images_count)
		game->image_list[i++]->img->instances[0].x -= 64;
	game->player_win_x--;
	game->bg_win_x--;
}
