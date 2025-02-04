/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils_init_images.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:50:36 by vuljas            #+#    #+#             */
/*   Updated: 2025/02/01 16:34:29 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_init_image_list(t_game_data *game);
static void	ft_fill_images_list(t_game_data *game);
static void	ft_fill_wall_images(t_game_data *game, int *count);
static void	ft_fill_images_ex_wall(t_game_data *game, int i, int j, int *count);

void	ft_init_images(t_game_data *g)
{
	g->bg_image = mlx_texture_to_image(g->mlx, g->bg_texture);
	if (!(g->bg_image))
		ft_free_exit(g);
	mlx_resize_image(g->bg_image, (64 * g->data->line_len),
		(64 * g->data->rows));
	g->wall_image = mlx_texture_to_image(g->mlx, g->wall_texture);
	if (!(g->wall_image))
		ft_free_exit(g);
	g->free_image = mlx_texture_to_image(g->mlx, g->free_texture);
	if (!(g->free_image))
		ft_free_exit(g);
	g->exit_open_image = mlx_texture_to_image(g->mlx, g->exit_open_tex);
	if (!(g->exit_open_image))
		ft_free_exit(g);
	g->exit_lock_image = mlx_texture_to_image(g->mlx, g->exit_lock_tex);
	if (!(g->exit_lock_image))
		ft_free_exit(g);
	ft_init_coll_player_texture(g);
	ft_init_image_list(g);
	ft_fill_images_list(g);
}

static void	ft_init_image_list(t_game_data *g)
{
	int	i;

	g->image_list = malloc(sizeof(t_image_list *) * g->data->images_count);
	if (!(g->image_list))
	{
		ft_free_exit(g);
		exit(ft_printf("Error!\nImages list malloc failed!\n"));
	}
	i = 0;
	while (i < g->data->images_count)
	{
		g->image_list[i] = malloc(sizeof(t_image_list *));
		i++;
	}
}

static void	ft_fill_images_list(t_game_data *g)
{
	int	count;
	int	y;
	int	x;

	count = 1;
	y = 0;
	g->image_list[0]->img = mlx_texture_to_image(g->mlx, g->bg_texture);
	if (!(g->image_list[0]->img))
		ft_free_exit(g);
	while (y < g->data->rows)
	{
		x = 0;
		while (x < g->data->line_len)
		{
			if (g->data->map[y][x] == '1')
				ft_fill_wall_images(g, &count);
			else
				ft_fill_images_ex_wall(g, y, x, &count);
			x++;
		}
		y++;
	}
	ft_player_tex_to_img(g, count);
}

static void	ft_fill_wall_images(t_game_data *g, int *count)
{
	int	len;

	len = *count;
	g->image_list[len]->img = mlx_texture_to_image(g->mlx, g->wall_texture);
	if (!(g->image_list[len++]->img))
		ft_free_exit(g);
	*count = len;
}

static void	ft_fill_images_ex_wall(t_game_data *g, int y, int x, int *count)
{
	int	len;

	len = *count;
	g->image_list[len]->img = mlx_texture_to_image(g->mlx, g->free_texture);
	if (!(g->image_list[len++]->img))
		ft_free_exit(g);
	if (g->data->map[y][x] == 'C')
	{
		g->image_list[len]->img = mlx_texture_to_image(g->mlx, g->coll_texture);
		if (!(g->image_list[len++]->img))
			ft_free_exit(g);
	}
	if (g->data->map[y][x] == 'E')
	{
		g->exit_open_image = mlx_texture_to_image(g->mlx, g->exit_open_tex);
		if (!(g->exit_open_image))
			ft_free_exit(g);
		g->image_list[len++]->img = g->exit_open_image;
		g->exit_lock_image = mlx_texture_to_image(g->mlx, g->exit_lock_tex);
		if (!(g->exit_lock_image))
			ft_free_exit(g);
		g->image_list[len++]->img = g->exit_lock_image;
	}
	*count = len;
}
