#include "cub3d.h"

void    add_line(t_map *old, char *addition)
{
    t_line  *new;

    new = mms_alloc(old->size, sizeof(t_line));
    if (!old->grid)
    {
        new->line = addition;
        new->size = ft_strlen(addition);
    }
    else
    {
        ft_memcpy(new, old->grid, (old->size - 1) * sizeof(t_line));
        new[old->size - 1].line = addition;
        new[old->size - 1].size = ft_strlen(addition);
        mms_free(old->grid);
    }
    old->grid = new;
}

// Checks for invalid chars in the map and sets everything to spaces
// to get ready for floodfill

// change to use api!
bool    check_transform(t_game *game, t_map *map)
{
    size_t i;
    size_t j;

    i = 0;
    while (i < map->size)
    {
        j = 0;
        while (j < map->grid[i].size)
        {
            if (!ft_strchr(ALLOWED_CHARS, map->grid[i].line[j]))
            {
                printf("Char: %d\n", map->grid[i].line[j]);
                return (false);
            }
            if (map->grid[i].line[j] == '0')
                map->grid[i].line[j] = ' ';
            else if (map->grid[i].line[j] == 'N' || map->grid[i].line[j] == 'S' ||
                    map->grid[i].line[j] == 'W' || map->grid[i].line[j] == 'E')
            {
                printf("playerx: %lu, playery: %lu\n", j, i);
                set_pos(map, j, i, ' ');
                game->player.px = j + 0.5;
                game->player.py = i + 0.5;
            }
            j++;
        }
        i++;
    }
    return (true);
}


// change the way i remove backslash to make cleaner
bool    load_map(t_game *game, int fd)
{
    char    *line;
    char    *backslash;

    game->map.size = 0;
    game->map.grid = NULL;
    line = get_next_line(fd);
    while (ft_strlen(line) <= 1)
        line = get_next_line(fd);
    while (line)
    {
        backslash = ft_strchr(line, '\n');
        if (backslash)
            *backslash = 0;
        if (ft_strlen(line) <= 1)
            return (false);
        game->map.size++;
        add_line(&game->map, line);
        line = get_next_line(fd);
    }
    if (!check_transform(game, &game->map))
        return (false);
    return (true);
}

void    print_map(t_map *map)
{
    size_t i;

    i = 0;
    while (i < map->size)
    {
        printf("%s\n", map->grid[i].line);
        i++;
    }
}

bool    flood_fill(t_map *map, int x, int y)
{
    if (!at_pos(map, x, y))
        return (false);
    if (at_pos(map, x, y) == '1' || at_pos(map, x, y) == '0')
        return (true);
    set_pos(map, x, y, '0');
    if (!flood_fill(map, x + 1, y))
        return (false);
    if (!flood_fill(map, x - 1, y))
        return (false);
    if (!flood_fill(map, x, y + 1))
        return (false);
    if (!flood_fill(map, x, y - 1))
        return (false);
    return (true);
}

bool    parse_map(t_game *game, int fd)
{
    if (!load_map(game, fd))
    {
        printf("Failed to load map!\n");
        return (false);
    }
    if (!flood_fill(&game->map, 26, 11))
    {
        printf("Invalid map\n");
        return (false);
    }
    print_map(&game->map);
    return (true);
}