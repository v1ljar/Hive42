/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils_assign_textures.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:23:07 by vuljas            #+#    #+#             */
/*   Updated: 2025/02/01 16:23:14 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_init_coll_player_texture(t_game_data *g)
{
	int	i;

	i = 0;
	while (i < g->data->collectibles)
	{
		g->coll_list[i]->img = mlx_texture_to_image(g->mlx, g->coll_texture);
		if (!g->coll_list[i]->img)
			ft_free_exit(g);
		i++;
	}
	g->player_image = mlx_texture_to_image(g->mlx, g->player_texture);
	if (!(g->player_image))
		ft_free_exit(g);
	g->pl_lef_img = mlx_texture_to_image(g->mlx, g->pl_left_texture);
	if (!(g->pl_lef_img))
		ft_free_exit(g);
	g->pl_rig_img = mlx_texture_to_image(g->mlx, g->pl_right_texture);
	if (!(g->pl_rig_img))
		ft_free_exit(g);
}

void	ft_player_tex_to_img(t_game_data *g, int count)
{
	g->image_list[count]->img = mlx_texture_to_image(g->mlx, g->player_texture);
	if (!(g->image_list[count++]->img))
		ft_free_exit(g);
	g->image_list[count]->img = mlx_texture_to_image(g->mlx,
			g->pl_left_texture);
	if (!(g->image_list[count++]->img))
		ft_free_exit(g);
	g->image_list[count]->img = mlx_texture_to_image(g->mlx,
			g->pl_right_texture);
	if (!(g->image_list[count++]->img))
		ft_free_exit(g);
}
