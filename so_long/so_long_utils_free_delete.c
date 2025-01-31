/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils_free_delete.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:50:15 by vuljas            #+#    #+#             */
/*   Updated: 2025/01/30 13:50:18 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_delete_collectable(t_game_data *game)
{
	int	i;

	i = 0;
	while (i < game->data->collectibles)
	{
		if (game->coll_list[i]->enabled == 1
			&& game->coll_list[i]->x == game->data->player_x
			&& game->coll_list[i]->y == game->data->player_y)
		{
			game->coll_list[i]->enabled = 0;
			game->coll_list[i]->img->instances->enabled = false;
			break ;
		}
		i++;
	}
}

void	ft_free_lists(t_game_data *game, int nbr_images, int nbr_coll)
{
	int	i;

	i = 0;
	while (i < nbr_images)
		free(game->image_list[i++]);
	free(game->image_list);
	i = 0;
	while (i < nbr_coll)
		free(game->coll_list[i++]);
	free(game->coll_list);
}

void	ft_free_collectibles(t_game_data *game, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(game->coll_list[i]->img);
		free(game->coll_list[i]);
		i++;
	}
	free(game->coll_list);
}

void	ft_free_textures(t_game_data *game)
{
	if (game->bg_texture)
		mlx_delete_texture(game->bg_texture);
	if (game->player_texture)
		mlx_delete_texture(game->player_texture);
	if (game->wall_texture)
		mlx_delete_texture(game->wall_texture);
	if (game->free_texture)
		mlx_delete_texture(game->free_texture);
	if (game->collectible_texture)
		mlx_delete_texture(game->collectible_texture);
	if (game->finish_locked_texture)
		mlx_delete_texture(game->finish_locked_texture);
	if (game->finish_opened_texture)
		mlx_delete_texture(game->finish_opened_texture);
	if (game->player_left_texture)
		mlx_delete_texture(game->player_left_texture);
	if (game->player_right_texture)
		mlx_delete_texture(game->player_right_texture);
}
