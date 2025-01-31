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

void	ft_init_coll_texture(t_game_data *game)
{
	int	i;

	i = 0;
	while (i < game->data->collectibles)
	{
		game->collectibles_list[i]->img = mlx_texture_to_image(game->mlx, game->collectible_texture);
		if (!game->collectibles_list[i]->img)
			ft_free_exit(game);
		i++;
	}
}

void	ft_init_images(t_game_data *game)
{
	game->bg_image = mlx_texture_to_image(game->mlx, game->bg_texture);
	if (!(game->bg_image))
		ft_free_exit(game);
	mlx_resize_image(game->bg_image, (64 * game->data->line_len), (64 * game->data->rows));
	game->player_image = mlx_texture_to_image(game->mlx, game->player_texture);
	if (!(game->player_image))
		ft_free_exit(game);
	game->player_left_image = mlx_texture_to_image(game->mlx, game->player_left_texture);
	if (!(game->player_left_image))
		ft_free_exit(game);
	game->player_right_image = mlx_texture_to_image(game->mlx, game->player_right_texture);
	if (!(game->player_right_image))
		ft_free_exit(game);
	game->wall_image = mlx_texture_to_image(game->mlx, game->wall_texture);
	if (!(game->wall_image))
		ft_free_exit(game);
	game->free_image = mlx_texture_to_image(game->mlx, game->free_texture);
	if (!(game->free_image))
		ft_free_exit(game);
	game->finish_opened_image = mlx_texture_to_image(game->mlx, game->finish_opened_texture);
	if (!(game->finish_opened_image))
		ft_free_exit(game);
	game->finish_locked_image = mlx_texture_to_image(game->mlx, game->finish_locked_texture);
	if (!(game->finish_locked_image))
		ft_free_exit(game);
	ft_init_coll_texture(game);
	ft_init_image_list(game);
	ft_fill_images_list(game);
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

void	ft_fill_images_list(t_game_data *game)
{
	int	count;
	int	y;
	int	x;

	count = 1;
	y = 0;
	game->image_list[0]->img = mlx_texture_to_image(game->mlx, game->bg_texture);
	if (!(game->image_list[0]->img))
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
	game->image_list[count]->img = mlx_texture_to_image(game->mlx, game->player_texture);
	if (!(game->image_list[count++]->img))
		ft_free_exit(game);
	game->image_list[count]->img = mlx_texture_to_image(game->mlx, game->player_left_texture);
	if (!(game->image_list[count++]->img))
		ft_free_exit(game);
	game->image_list[count]->img = mlx_texture_to_image(game->mlx, game->player_right_texture);
	if (!(game->image_list[count++]->img))
		ft_free_exit(game);
}

void	ft_fill_wall_images(t_game_data *game, int *count)
{
	int	len;

	len = *count;
	game->image_list[len]->img = mlx_texture_to_image(game->mlx, game->wall_texture);
	if (!(game->image_list[len++]->img))
		ft_free_exit(game);
	*count = len;
}

void	ft_fill_images_ex_wall(t_game_data *game, int y, int x, int *count)
{
	int	len;

	len = *count;
	game->image_list[len]->img = mlx_texture_to_image(game->mlx, game->free_texture);
	if (!(game->image_list[len++]->img))
		ft_free_exit(game);
	if (game->data->map[y][x] == 'C')
	{
		game->image_list[len]->img = mlx_texture_to_image(game->mlx, game->collectible_texture);
		if (!(game->image_list[len++]->img))
			ft_free_exit(game);
	}
	if (game->data->map[y][x] == 'E')
	{
		game->finish_opened_image = mlx_texture_to_image(game->mlx, game->finish_opened_texture);
		if (!(game->finish_opened_image))
			ft_free_exit(game);
		game->image_list[len++]->img = game->finish_opened_image;
		game->finish_locked_image = mlx_texture_to_image(game->mlx, game->finish_locked_texture);
		if (!(game->finish_locked_image))
			ft_free_exit(game);
		game->image_list[len++]->img = game->finish_locked_image;
	}
	*count = len;
}
