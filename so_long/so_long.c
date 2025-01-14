#include "so_long.h"

int     ft_validate_map(char *map_path, t_map_data *board);
int     ft_all_to_big_str(char *map_path, t_map_data *board);
void    ft_initialize_map_data(t_map_data *board, char *whole_map, int lines);

int main(int argc, char **argv)
{
    t_map_data board;

    if (argc != 2 || ft_validate_map(argv[1], &board) == -1)
        return (ft_printf("Error\n"));
    int i = 0;
    while(i < board.rows)
        ft_printf("%s\n", board.map[i++]);
    i = 0;
    while (i < board.rows)
        free(board.map[i++]);
    free(board.map);
    return (0);
}

int ft_validate_map(char *map_path, t_map_data *board)
{
    ft_all_to_big_str(map_path, board);
    return (0);
}

int ft_all_to_big_str(char *map_path, t_map_data *board)
{
    char    *whole_map;
    int     fd;
    char    *str;
    int     lines;

    fd = open(map_path, O_RDONLY);
    lines = 0;
    whole_map = ft_strdup("");
    while ((str = get_next_line(fd)) != NULL)
    {
        whole_map = ft_strjoin_gnl((const char *)whole_map, (const char *) str);
        free(str);
        lines++;
    }
    close(fd);
    ft_initialize_map_data(board, whole_map, lines);
    return (0);
}

void    ft_initialize_map_data(t_map_data *board, char *whole_map, int lines)
{
    board->map = ft_split(whole_map, '\n');
    board->line_len = (int)ft_strlen(whole_map) / lines;
    board->rows = lines;
    board->collectibles = 0;
    board->exit_count = 0;
    board->start_count = 0;
    free(whole_map);
}