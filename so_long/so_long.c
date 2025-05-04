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
void	ft_enemies_loop(void *param);
void	ft_spawn_enemy(t_game_data *game);
void	ft_animate_enemies(t_game_data *game, int spawn_timer);
void	ft_move_enemies(t_game_data *game);

int	main(int argc, char **argv)
{
	static t_map_data	board;
	static t_game_data	game;

	if (argc != 2 || ft_validate_map(argv[1], &board) == -1)
	{
		ft_free_vector(board.map, board.rows);
		ft_free_vector(board.map_dup, board.rows);
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
	mlx_loop_hook(game.mlx, ft_enemies_loop, &game);
	mlx_loop(game.mlx);
	mlx_close_window(game.mlx);
	mlx_terminate(game.mlx);
	ft_free_textures(&game);
	ft_free_lists(&game, game.data->images_count, game.data->collectibles);
	ft_free_vector(game.data->map, game.data->rows);
	ft_free_dragons(&game);
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

void	ft_enemies_loop(void *param)
{
	t_game_data *g;
	static int spawn_timer;

	g = param;
	if (++spawn_timer > 50)
	{
		ft_spawn_enemy(g);
		spawn_timer = 0;
	}
	ft_animate_enemies(g, spawn_timer);
	ft_move_enemies(g);
}

void	ft_spawn_enemy(t_game_data *game)
{
	int empty_count = 0;
	int spawn_x = 0;
	int spawn_y = 0;
	int i, j;

	i = 0;
	while (i < game->data->rows)
	{
		j = 0;
		while (j < game->data->line_len)
		{
			if (game->data->map[i][j] == '0' && (j <= game->player_win_x - 5 || j >= game->player_win_x + 5))
			{
				empty_count++;
				if (rand() % empty_count == 0)
				{
					spawn_x = j;
					spawn_y = i;
				}
			}
			j++;
		}
		i++;
	}
	if (empty_count >= 3 && game->nbr_enemy < game->data->rows)
	{
		static t_enemy *new_enemy;

		new_enemy = malloc(sizeof(t_enemy));
		if (!new_enemy)
			ft_escape_exit(game);
		new_enemy->x = spawn_x;
		new_enemy->y = spawn_y;
		new_enemy->alive = 1;
		new_enemy->move_delay = 50;
		new_enemy->frame = 0;
		new_enemy->action = 0;
		game->nbr_enemy++;
		i = 0;
		while (i < 2)
		{
			if (i == 0)
			{
				new_enemy->sprites[i] = mlx_texture_to_image(game->mlx, game->enemy_texture[i]);
				mlx_image_to_window(game->mlx, new_enemy->sprites[i], spawn_x * 64, spawn_y * 64);
				new_enemy->sprites[i]->instances[0].enabled = true;
			}
			else
			{
				new_enemy->sprites[i] = mlx_texture_to_image(game->mlx, game->enemy_texture[i]);
				mlx_image_to_window(game->mlx, new_enemy->sprites[i], (spawn_x - 0.5) * 64, (spawn_y - 0.5) * 64);
				new_enemy->sprites[i]->instances[0].enabled = false;
			}
			if (!new_enemy->sprites[i])
            {
                // Handle texture loading failure
                free(new_enemy);
				ft_printf("Malloc failed!\n");
                ft_escape_exit(game);
            }
			i++;
		}
		new_enemy->next = game->enemies;
		game->enemies = new_enemy;
	}
}

void	ft_animate_enemies(t_game_data *game, int spawn_timer)
{
	t_enemy *enemy;
	int		i;

	enemy = game->enemies;
	while (enemy)
	{
		if (enemy->alive && spawn_timer == 13)
		{
			enemy->frame = (enemy->frame + 1) % 2;
			i = 0;
			while (i < 2)
			{
				enemy->sprites[i]->instances[0].enabled = (i == enemy->frame);
				i++;
			}
		}
		enemy = enemy->next;
	}
}

void	ft_move_enemies(t_game_data *game)
{
	t_enemy	*enemy;
	int		i;

	enemy = game->enemies;
	while (enemy)
	{
		if (enemy->alive && --enemy->move_delay <= 0)
		{
			enemy->move_delay = 50;
			int move_dir = rand() % 4;
			int new_x = enemy->x;
			int new_y = enemy->y;

			if (move_dir == 0 && game->data->map[enemy->y - 1][enemy->x] != '1')
				new_y--;
			if (move_dir == 1 && game->data->map[enemy->y + 1][enemy->x] != '1')
				new_y++;
			if (move_dir == 2 && game->data->map[enemy->y] [enemy->x - 1] != '1')
				new_x--;
			if (move_dir == 3 && game->data->map[enemy->y][enemy->x + 1] != '1')
				new_x++;
			if (game->data->map[new_y][new_x] != '1')
			{
				enemy->x = new_x;
				enemy->y = new_y;
			}
			i = 0;
			while (i < 2)
			{
				if (i == 0)
				{
					enemy->sprites[i]->instances[0].x = new_x * 64;
					enemy->sprites[i]->instances[0].y = new_y * 64;
				}
				else
				{
					enemy->sprites[i]->instances[0].x = (new_x - 0.5) * 64;
					enemy->sprites[i]->instances[0].y = (new_y - 0.5) * 64;
				}
				i++;
			}
		}
		if (enemy->x == game->player_win_x && enemy->y == game->player_win_y)
			ft_dragon_exit(game);
		enemy = enemy->next;
	}
}

void	ft_free_dragons(t_game_data *game)
{
	t_enemy *enemy;
	t_enemy *temp;

	if (game->enemies)
	{
		enemy = game->enemies;
		while (enemy)
		{
			temp = enemy->next;
			free(enemy);
			enemy = temp;
			temp = NULL;
		}
	}
}

void	ft_dragon_exit(t_game_data *game)
{
	ft_free_textures(game);
	mlx_close_window(game->mlx);
	mlx_terminate(game->mlx);
	ft_free_dragons(game);
	ft_free_lists(game, game->data->images_count, game->data->collectibles);
	ft_free_vector(game->data->map, game->data->rows);
	exit(ft_printf("You are dead! Dragon has eaten you!\n"));
}
