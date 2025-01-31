/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils_init_images.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:50:36 by vuljas            #+#    #+#             */
/*   Updated: 2025/01/30 13:50:39 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_init_coll_texture(t_game_data *game);

void	ft_init_coll_texture(t_game_data *g)
{
	int	i;

	i = 0;
	while (i < g->data->collectibles)
	{
		g->coll_list[i]->img = mlx_texture_to_image(g->mlx, g->collectible_texture);
		if (!g->coll_list[i]->img)
			ft_free_exit(g);
		i++;
	}
}

void	ft_init_images(t_game_data *g)
{
	g->bg_image = mlx_texture_to_image(g->mlx, g->bg_texture);
	if (!(g->bg_image))
		ft_free_exit(g);
	mlx_resize_image(g->bg_image, (64 * g->data->line_len), (64 * g->data->rows));
	g->player_image = mlx_texture_to_image(g->mlx, g->player_texture);
	if (!(g->player_image))
		ft_free_exit(g);
	g->player_left_image = mlx_texture_to_image(g->mlx, g->player_left_texture);
	if (!(g->player_left_image))
		ft_free_exit(g);
	g->player_right_image = mlx_texture_to_image(g->mlx, g->player_right_texture);
	if (!(g->player_right_image))
		ft_free_exit(g);
	g->wall_image = mlx_texture_to_image(g->mlx, g->wall_texture);
	if (!(g->wall_image))
		ft_free_exit(g);
	g->free_image = mlx_texture_to_image(g->mlx, g->free_texture);
	if (!(g->free_image))
		ft_free_exit(g);
	g->finish_opened_image = mlx_texture_to_image(g->mlx, g->finish_opened_texture);
	if (!(g->finish_opened_image))
		ft_free_exit(g);
	g->finish_locked_image = mlx_texture_to_image(g->mlx, g->finish_locked_texture);
	if (!(g->finish_locked_image))
		ft_free_exit(g);
	ft_init_coll_texture(g);
	ft_init_image_list(g);
	ft_fill_images_list(g);
}

void	ft_init_image_list(t_game_data *game)
{
	int	i;

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

void	ft_player_tex_to_img(t_game_data *g, int count)
{
	g->image_list[count]->img = mlx_texture_to_image(g->mlx, g->player_texture);
	if (!(g->image_list[count++]->img))
		ft_free_exit(g);
	g->image_list[count]->img = mlx_texture_to_image(g->mlx, g->player_left_texture);
	if (!(g->image_list[count++]->img))
		ft_free_exit(g);
	g->image_list[count]->img = mlx_texture_to_image(g->mlx, g->player_right_texture);
	if (!(g->image_list[count++]->img))
		ft_free_exit(g);
}

void	ft_fill_images_list(t_game_data *g)
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

void	ft_fill_wall_images(t_game_data *g, int *count)
{
	int	len;

	len = *count;
	g->image_list[len]->img = mlx_texture_to_image(g->mlx, g->wall_texture);
	if (!(g->image_list[len++]->img))
		ft_free_exit(g);
	*count = len;
}

void	ft_fill_images_ex_wall(t_game_data *g, int y, int x, int *count)
{
	int	len;

	len = *count;
	g->image_list[len]->img = mlx_texture_to_image(g->mlx, g->free_texture);
	if (!(g->image_list[len++]->img))
		ft_free_exit(g);
	if (g->data->map[y][x] == 'C')
	{
		g->image_list[len]->img = mlx_texture_to_image(g->mlx, g->collectible_texture);
		if (!(g->image_list[len++]->img))
			ft_free_exit(g);
	}
	if (g->data->map[y][x] == 'E')
	{
		g->finish_opened_image = mlx_texture_to_image(g->mlx, g->finish_opened_texture);
		if (!(g->finish_opened_image))
			ft_free_exit(g);
		g->image_list[len++]->img = g->finish_opened_image;
		g->finish_locked_image = mlx_texture_to_image(g->mlx, g->finish_locked_texture);
		if (!(g->finish_locked_image))
			ft_free_exit(g);
		g->image_list[len++]->img = g->finish_locked_image;
	}
	*count = len;
}
