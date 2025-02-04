/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:56:57 by vuljas            #+#    #+#             */
/*   Updated: 2025/01/30 13:57:02 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_update_collectables_amount(void *param);

int	main(int argc, char **argv)
{
	t_map_data	board;
	t_game_data	game;

	if (argc != 2 || ft_validate_map(argv[1], &board) == -1)
	{
		ft_free_vector(board.map, board.rows);
		return (ft_printf("Error!\nMap is not valid!\n"), 1);
	}
	ft_init_game_data(&game, &board);
	ft_init_mlx_and_textures(&game);
	ft_init_images(&game);
	ft_map_on_window(&game);
	ft_map_correct_pos(&game);
	mlx_loop_hook(game.mlx, ft_update_collectables_amount, &game);
	mlx_loop_hook(game.mlx, ft_update_movement, &game);
	mlx_loop_hook(game.mlx, ft_adjust_images, &game);
	mlx_key_hook(game.mlx, (void *)my_keyhook, &game);
	mlx_loop(game.mlx);
	mlx_close_window(game.mlx);
	mlx_terminate(game.mlx);
	ft_free_textures(&game);
	ft_free_lists(&game, game.data->images_count, game.data->collectibles);
	ft_free_vector(game.data->map, game.data->rows);
	return (ft_printf("Exited the game without completing the game!\n"));
}

static void	ft_update_collectables_amount(void *param)
{
	t_game_data	*g;
	int			reminder;
	char		*nbr;

	g = param;
	if (g->coll_decrement < g->collected_cols)
	{
		reminder = g->data->collectibles - g->collected_cols;
		nbr = ft_itoa(reminder);
		mlx_delete_image(g->mlx, g->coll_amount);
		g->coll_amount = mlx_put_string(g->mlx, nbr, 12, 12);
		mlx_resize_image(g->coll_amount, 40, 40);
		free(nbr);
		g->coll_decrement++;
	}
}
