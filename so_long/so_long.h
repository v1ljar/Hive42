#ifndef SO_LONG_H
# define SO_LONG_H

#include "./libft/libft.h"
#include <fcntl.h>

typedef struct s_map_data
{
    char    **map;
    char    **map_dup;
    int     line_len;
    int     rows;
    int     collectibles;
    int     exit_count;
    int     start_count;
    int     player_x;
    int     player_y;
}   t_map_data;

#endif