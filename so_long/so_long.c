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

int	main(int argc, char **argv)
{
	t_map_data	board;
	t_game_data	game;

	if (argc != 2 || ft_validate_map(argv[1], &board) == -1)
	{
		ft_free_vector(board.map, board.rows);
		ft_free_vector(board.map_dup, board.rows);
		return (ft_printf("Error! Map is not valid!\n"), 1);
	}
	ft_init_game_data(&game, &board);
	ft_init_mlx_and_textures(&game);
	ft_init_images(&game);
	ft_map_on_window(&game);
	ft_map_correct_pos(&game);
	mlx_loop_hook(game.mlx, ft_adjust_images, &game);
	mlx_key_hook(game.mlx, (void *)my_keyhook, &game);
	mlx_loop(game.mlx);
	mlx_close_window(game.mlx);
	mlx_terminate(game.mlx);
	ft_free_vector(game.data->map, game.data->rows);
	return (ft_printf("Exited the game without completing the game!\n"));
}
