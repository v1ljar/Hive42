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

static int		ft_initialize_board(char *map_path, t_map_data *board);
static int		ft_join_whole_map(int fd, char **whole_map, char **str);
static int		ft_validate_parts(t_map_data *board);
static void		ft_validate_char(t_map_data *board, char c, int i, int j);

int	ft_validate_map(char *map_path, t_map_data *board)
{
	int	len;

	len = ft_strlen(map_path);
	if (ft_memcmp((map_path + len - 4), ".ber", 4) != 0)
		exit(ft_printf("Error\nOnly '.ber' files accepted!\n"));
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

static int	ft_initialize_board(char *map_path, t_map_data *board)
{
	char	*whole_map;
	int		fd;
	char	*str;
	int		lines;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		exit(ft_printf("Error\nFailed to open '%s'.\n", map_path));
	whole_map = ft_strdup("");
	if (!whole_map)
		exit(ft_printf("Error\nFailed to allocate whole_map.\n"));
	str = get_next_line(fd);
	if (!str || str[0] != '1')
	{
		free(whole_map);
		free(str);
		close(fd);
		exit(ft_printf("Error\nFailed to allocate first line from fd.\n"));
	}
	lines = ft_join_whole_map(fd, &whole_map, &str);
	close(fd);
	ft_initialize_map_data(board, whole_map, lines, map_path);
	return (0);
}

static int	ft_join_whole_map(int fd, char **whole_map, char **str)
{
	int	lines;

	lines = 0;
	while (*str != NULL)
	{
		*whole_map = ft_strjoin_gnl((const char *)*whole_map,
				(const char *)*str);
		if (!*whole_map)
		{
			free(*whole_map);
			exit(ft_printf("Error\nFailed to allocate joined map.\n"));
		}
		free(*str);
		lines++;
		*str = get_next_line(fd);
	}
	return (lines);
}

static void	ft_validate_char(t_map_data *board, char c, int i, int j)
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

static int	ft_validate_parts(t_map_data *board)
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
