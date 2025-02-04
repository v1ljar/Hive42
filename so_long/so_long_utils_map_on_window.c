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

static void	ft_draw_player_images(t_game_data *g, int count);
static void	ft_draw_map(t_game_data *game, int y, int x, int *index);
static void	ft_init_exit_pos(t_game_data *game, int x, int y);

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
		exit(ft_printf("Error!\nBackground to the window failed!\n"));
	}
	game->image_list[img_index++]->img = game->bg_image;
	while (y < game->data->rows)
	{
		x = 0;
		while (x < game->data->line_len)
		{
			ft_draw_map(game, y * 64, x * 64, &img_index);
			x++;
		}
		y++;
	}
	ft_draw_player_images(game, img_index);
}

static void	ft_draw_player_images(t_game_data *g, int count)
{
	int		img_index;
	int		width;
	int		height;
	int		nbr_colls;
	char	*nr;

	img_index = count;
	width = 64 * g->data->player_x;
	height = 64 * g->data->player_y;
	mlx_image_to_window(g->mlx, g->player_image, width, height);
	g->image_list[img_index++]->img = g->player_image;
	mlx_image_to_window(g->mlx, g->pl_lef_img, width, height - 32);
	g->image_list[img_index++]->img = g->pl_lef_img;
	g->pl_lef_img->instances[0].enabled = false;
	mlx_image_to_window(g->mlx, g->pl_rig_img, width, height - 32);
	g->image_list[img_index++]->img = g->pl_rig_img;
	g->pl_rig_img->instances[0].enabled = false;
	nbr_colls = g->data->collectibles;
	nr = ft_itoa(nbr_colls);
	g->coll_amount = mlx_put_string(g->mlx, nr, 12, 12);
	mlx_resize_image(g->coll_amount, 40, 40);
	free(nr);
	g->coll_decrement = 0;
}


static void	ft_draw_map(t_game_data *g, int y, int x, int *index)
{
	int	img_index;

	img_index = *index;
	if (g->data->map[y / 64][x / 64] == '1')
		mlx_image_to_window(g->mlx, g->image_list[img_index++]->img, x, y);
	else
	{
		mlx_image_to_window(g->mlx, g->image_list[img_index++]->img, x, y);
		if (g->data->map[y / 64][x / 64] == 'C')
		{
			mlx_image_to_window(g->mlx, g->coll_list[g->col_count]->img, x, y);
			g->image_list[img_index++]->img = g->coll_list[g->col_count]->img;
			g->coll_list[g->col_count]->x = x / 64;
			g->coll_list[g->col_count++]->y = y / 64;
		}
		if (g->data->map[y / 64][x / 64] == 'E')
		{
			ft_init_exit_pos(g, x / 64, y / 64);
			mlx_image_to_window(g->mlx, g->image_list[img_index++]->img, x, y);
			mlx_image_to_window(g->mlx, g->image_list[img_index++]->img, x, y);
		}
	}
	*index = img_index;
}

static void	ft_init_exit_pos(t_game_data *game, int x, int y)
{
	game->exit_x = x;
	game->exit_y = y;
}
