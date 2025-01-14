#include "so_long.h"

int validate_map(char *map_path, t_map_data *map);

int main(int argc, char **argv)
{
    t_map_data map;

    if (argc != 2 || validate_map(argv[1], &map) == -1)
        return (ft_printf("Error\n"));
    int i = 0;
    while (i < map.columns)
        ft_printf("%s\n", map.data[i++]);
    ft_printf("Map is valid, Yeeii!\n");
    i = 0;
    while (i < map.columns)
        free(map.data[i++]);
    free(map.data);
    return (0);
}

void    ft_initialize_map_data(char *whole_map, t_map_data *map, int lines_count)
{
    map->data = ft_split(whole_map, '\n');
    map->columns = lines_count;
    map->line_len = ((int)ft_strlen(whole_map) / lines_count);
    map->collectible = 0;
    map->exit_count = 0;
    map->start_count = 0;
}
char *ft_map_to_big_str(char *map_path, t_map_data *map)
{
    char    *whole_map;
    int     fd;
    char    *str;
    int     lines_count;

    whole_map = ft_strdup("");
    if (!whole_map)
        return (NULL);
    fd = open(map_path, O_RDONLY);
    if (fd < 0)
        return (NULL);
    lines_count = 0;
    while ((str = get_next_line(fd)) != NULL)
    {
        whole_map = ft_strjoin_gnl((const char *)whole_map,(const char *) str);
        if (!whole_map)
        {
            int i = 0;
            while (i < map->columns)
                free(map->data[i++]);
            free(map->data);
            return (NULL);
        }
        free(str);
        lines_count++;
    }
    close(fd);
    ft_initialize_map_data(whole_map, map, lines_count);
    return (whole_map);
}

int validate_map(char *map_path, t_map_data *map)
{
    char    *whole_map;

    whole_map = ft_map_to_big_str(map_path, map);
    if (!whole_map)
        return (-1);
    free(whole_map);
    return (0);
}
