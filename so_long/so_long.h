#ifndef SO_LONG_H
# define SO_LONG_H

#include "./libft/libft.h"
#include <fcntl.h>

typedef struct s_map_data
{
    char    **data;
    int     line_len;
    int     columns;
    int     collectible;
    int     exit_count;
    int     start_count;
}   t_map_data;

#endif