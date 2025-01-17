#include "so_long.h"

int     ft_validate_path(t_map_data *b)
{
    char previous;

    previous = b->map_dup[b->player_y][b->player_x];
    if (previous == '1')
        return (-1);
    ft_flood_fill(b, b->player_y, b->player_x, previous, '1');
    if ((ft_path_is_valid(b) == -1))
        return (-1);
    return (0);
}



void    ft_flood_fill(t_map_data *b, int y, int x, char prev, unsigned char new)
{
    if (b->map_dup[y][x] == '1')
        return ;
    b->map_dup[y][x] = (char)new;
    if (y - 1 >= 0)
        ft_flood_fill(b, y - 1, x, prev, new);
    if (x + 1 < b->line_len)
        ft_flood_fill(b, y, x + 1, prev, new);
    if (y + 1 < b->rows)
        ft_flood_fill(b, y + 1, x, prev, new);
    if (x - 1 >= 0)
        ft_flood_fill(b, y, x - 1, prev, new);
}

int    ft_path_is_valid(t_map_data *b)
{
    int i;
    int j;

    i = 0;
    while (i < b->rows)
    {
        j = 0;
        while (b->map_dup[i][j] != '\0')
        {
            if (b->map_dup[i][j] == '1' || b->map_dup[i][j] == '0')
                j++;
            else
                return (-1);
        }
        i++;
    }
    ft_free_vector(b->map_dup, b->rows);
    return (0);
}

void    ft_free_vector(char **str, int len)
{
    int i;

    i = 0;
    while (i < len)
        free(str[i++]);
    free(str);
}