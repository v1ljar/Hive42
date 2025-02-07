/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils_init_data.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:20:59 by vuljas            #+#    #+#             */
/*   Updated: 2025/01/31 13:21:03 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_allocate_collectibles_list(t_game_data *game);
static void	ft_load_player_textures(t_game_data *game);

void	ft_init_game_data(t_game_data *game, t_map_data *board)
{
	game->mlx = NULL;
	game->data = board;
	game->bg_texture = NULL;
	game->player_texture = NULL;
	game->wall_texture = NULL;
	game->free_texture = NULL;
	game->coll_texture = NULL;
	game->exit_lock_tex = NULL;
	game->exit_open_tex = NULL;
	game->bg_image = NULL;
	game->player_image = NULL;
	game->pl_lef_img = NULL;
	game->pl_rig_img = NULL;
	game->wall_image = NULL;
	game->free_image = NULL;
	game->collectible_image = NULL;
	game->exit_lock_image = NULL;
	game->exit_open_image = NULL;
	game->moves = 0;
	game->exit_x = 0;
	game->exit_y = 0;
	game->exit_valid = 0;
	game->collected_cols = 0;
	ft_allocate_collectibles_list(game);
}

static void	ft_allocate_collectibles_list(t_game_data *game)
{
	int	i;
	int	amount;

	i = 0;
	amount = game->data->collectibles;
	game->coll_list = malloc(sizeof(t_collectible *) * amount);
	if (!(game->coll_list))
	{
		ft_free_vector(game->data->map, game->data->rows);
		exit(ft_printf("Error!\nCollectibles list malloc failed!\n"));
	}
	while (i < game->data->collectibles)
	{
		game->coll_list[i] = malloc(sizeof(t_collectible));
		if (!(game->coll_list[i]))
			ft_collectible_failed_free(game, i);
		game->coll_list[i]->enabled = 1;
		i++;
	}
	game->is_moving = 0;
	game->bg_win_y = 0;
	game->bg_win_x = 0;
}

void	ft_init_mlx_and_textures(t_game_data *game)
{
	int	width;

	width = game->data->line_len * 64;
	game->mlx = mlx_init(width, (64 * game->data->rows), "So long GAME", true);
	if (!(game->mlx))
		ft_init_mlx_failed(game);
	game->bg_texture = mlx_load_png("./textures/bg_f.png");
	if (!game->bg_texture)
		ft_free_exit(game);
	game->wall_texture = mlx_load_png("./textures/wall_fin_64.png");
	if (!game->wall_texture)
		ft_free_exit(game);
	game->free_texture = mlx_load_png("./textures/free_64.png");
	if (!game->free_texture)
		ft_free_exit(game);
	game->coll_texture = mlx_load_png("./textures/collectable_64.png");
	if (!game->coll_texture)
		ft_free_exit(game);
	game->exit_lock_tex = mlx_load_png("./textures/exit_locked_64.png");
	if (!game->exit_lock_tex)
		ft_free_exit(game);
	game->exit_open_tex = mlx_load_png("./textures/exit_opened_64.png");
	if (!game->exit_open_tex)
		ft_free_exit(game);
	ft_load_player_textures(game);
}

static void	ft_load_player_textures(t_game_data *game)
{
	game->player_texture = mlx_load_png("./textures/player_64.png");
	if (!game->player_texture)
		ft_free_exit(game);
	game->pl_left_texture = mlx_load_png("./textures/player_left_64.png");
	if (!game->pl_left_texture)
		ft_free_exit(game);
	game->pl_right_texture = mlx_load_png("./textures/player_right_64.png");
	if (!game->pl_right_texture)
		ft_free_exit(game);
	mlx_get_monitor_size(0, &game->win_x, &game->win_y);
}

void	ft_initialize_map_data(t_map_data *board, char *whole_map, int lines,
	char *map_path)
{
	if (lines < 3 || (ft_strlen(whole_map) < 17))
	{
		free(whole_map);
		exit(ft_printf("Error\n'%s' is not valid map.\n", map_path));
	}
	board->map = ft_split(whole_map, '\n');
	if (!board->map)
	{
		free(whole_map);
		exit(ft_printf("Error\nFailed to allocate map memory.\n"));
	}
	board->map_dup = ft_split(whole_map, '\n');
	if (!board->map_dup)
	{
		free(whole_map);
		ft_free_vector(board->map, board->rows);
		exit(ft_printf("Error\nFailed to allocate map_dup memory.\n"));
	}
	board->line_len = (int)ft_strlen(whole_map) / lines;
	board->rows = lines;
	board->collectibles = 0;
	board->exit_count = 0;
	board->start_count = 0;
	board->images_count = 8;
	free(whole_map);
}
