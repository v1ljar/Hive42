/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils_movement.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:45:38 by vuljas            #+#    #+#             */
/*   Updated: 2025/02/01 14:45:40 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_update_movement(void *param)
{
	t_game_data	*g;

	g = param;
	if (g->is_moving == 1)
	{
		if (g->pl_lef_img->instances[0].x > g->pl_rig_img->instances[0].x)
			g->pl_lef_img->instances[0].x -= g->move_size;
		else
		{
			g->is_moving = 0;
			g->pl_lef_img->instances[0].enabled = false;
			g->player_image->instances[0].enabled = true;
		}
	}
	if (g->is_moving == 2)
	{
		if (g->pl_rig_img->instances[0].x < g->pl_lef_img->instances[0].x)
			g->pl_rig_img->instances[0].x += g->move_size;
		else
		{
			g->is_moving = 0;
			g->pl_rig_img->instances[0].enabled = false;
			g->player_image->instances[0].enabled = true;
		}
	}
}

void	ft_animate_movement(t_game_data *game, int way)
{
	if (way == 1)
	{
		game->target_x = game->pl_lef_img->instances[0].x - 64;
		game->is_moving = 1;
	}
	if (way == 2)
	{
		game->target_x = game->pl_rig_img->instances[0].x + 64;
		game->is_moving = 2;
	}
}
