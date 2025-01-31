/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils_map_initialization.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:50:52 by vuljas            #+#    #+#             */
/*   Updated: 2025/01/30 13:50:55 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_validate_char(t_map_data *board, char c, int i, int j);

int	ft_validate_map(char *map_path, t_map_data *board)
{
	int	len;

	len = ft_strlen(map_path);
	if (ft_memcmp((map_path + len - 4), ".ber", 4) != 0)
		return (-1);
	if ((ft_initialize_board(map_path, board) == -1))
		return (-1);
	if ((ft_validate_parts(board) == -1))
		return (-1);
	if ((ft_validate_amount(board) == -1))
		return (-1);
	if ((ft_validate_path(board) == -1))
		return (-1);
	return (0);
}

int	ft_initialize_board(char *map_path, t_map_data *board)
{
	char	*whole_map;
	int		fd;
	char	*str;
	int		lines;

	fd = open(map_path, O_RDONLY);
	lines = 0;
	whole_map = ft_strdup("");
	str = get_next_line(fd);
	while (str != NULL)
	{
		if (str == NULL)
			break ;
		whole_map = ft_strjoin_gnl((const char *)whole_map, (const char *) str);
		free(str);
		lines++;
		str = get_next_line(fd);
	}
	close(fd);
	if (lines < 3 || (ft_strlen(whole_map) < 17))
		return (free(whole_map), -1);
	ft_initialize_map_data(board, whole_map, lines);
	return (0);
}

void	ft_initialize_map_data(t_map_data *board, char *whole_map, int lines)
{
	board->map = ft_split(whole_map, '\n');
	board->map_dup = ft_split(whole_map, '\n');
	board->line_len = (int)ft_strlen(whole_map) / lines;
	board->rows = lines;
	board->collectibles = 0;
	board->exit_count = 0;
	board->start_count = 0;
	board->images_count = 8;
	free(whole_map);
}

void	ft_validate_char(t_map_data *board, char c, int i, int j)
{
	if (c == 'C')
	{
		board->collectibles++;
		board->images_count += 2;
	}
	else if (c == 'P')
	{
		board->start_count++;
		board->player_x = j;
		board->player_y = i;
	}
	else if (c == 'E')
	{
		board->exit_count++;
	}
	else if (c == '1' || c == '0')
	{
		board->images_count++;
	}
}

int	ft_validate_parts(t_map_data *board)
{
	int	i;
	int	j;

	i = 0;
	while (i < board->rows)
	{
		j = 0;
		while (board->map[i][j] != '\0')
		{
			if (board->map[i][j] == 'C' || board->map[i][j] == 'P' ||
				board->map[i][j] == 'E' || board->map[i][j] == '1' ||
				board->map[i][j] == '0')
			{
				ft_validate_char(board, board->map[i][j], i, j);
				j++;
			}
			else
				break ;
		}		
		if (j != board->line_len)
			return (-1);
		i++;
	}
	return (0);
}

int	ft_validate_amount(t_map_data *b)
{
	int	i;
	int	j;

	if (b->exit_count != 1 || b->start_count != 1 || b->collectibles == 0)
		return (-1);
	i = 0;
	while (i < b->rows)
	{
		j = 0;
		while (b->map[i][j] != '\0')
		{
			if (b->map[0][j] != '1' || b->map[b->rows - 1][j] != '1')
				return (-1);
			if (b->map[i][0] != '1' || b->map[1][b->line_len - 1] != '1')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}
