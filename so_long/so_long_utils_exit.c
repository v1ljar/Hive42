/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils_exit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:50:05 by vuljas            #+#    #+#             */
/*   Updated: 2025/01/30 13:50:09 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_escape_exit(t_game_data *game)
{
	ft_free_textures(game);
	mlx_close_window(game->mlx);
	mlx_terminate(game->mlx);
	ft_free_dragons(game);
	ft_free_lists(game, game->data->images_count, game->data->collectibles);
	ft_free_vector(game->data->map, game->data->rows);
	exit(ft_printf("Error!\nGame was closed with ESC!\n"));
}

void	ft_game_loop_exit(t_game_data *game)
{
	ft_free_textures(game);
	mlx_close_window(game->mlx);
	mlx_terminate(game->mlx);
	ft_free_dragons(game);
	ft_free_lists(game, game->data->images_count, game->data->collectibles);
	ft_printf("Collectibles collected: %i\n", game->data->collectibles);
	ft_free_vector(game->data->map, game->data->rows);
	ft_printf("SUCCESS!!! Great job!");
	ft_printf("You have completed the map with %i moves. \n", game->moves);
	exit(EXIT_SUCCESS);
}

void	ft_free_exit(t_game_data *game)
{
	ft_free_textures(game);
	mlx_close_window(game->mlx);
	mlx_terminate(game->mlx);
	ft_free_dragons(game);
	ft_free_lists(game, game->data->images_count, game->data->collectibles);
	ft_free_vector(game->data->map, game->data->rows);
	exit(ft_printf("Error!\nFailed to allocate memory!\n"));
}

void	ft_collectible_failed_free(t_game_data *game, int len)
{
	ft_free_vector(game->data->map, game->data->rows);
	ft_free_collectibles(game, len);
	exit(ft_printf("Error!\nCollectibles list malloc failed!\n"));
}

void	ft_init_mlx_failed(t_game_data *game)
{
	int	i;

	i = 0;
	ft_free_vector(game->data->map, game->data->rows);
	ft_free_collectibles(game, game->data->collectibles);
	while (i < game->data->images_count)
		free(game->image_list[i++]->img);
	free(game->image_list);
	exit(ft_printf("Error!\nWindow initialization failed!\n"));
}
