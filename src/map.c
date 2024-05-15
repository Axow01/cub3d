#include "cub3d.h"


// Returns char at positon NULL if out of bounds
char    at_pos(t_map *map, size_t x, size_t y)
{
    if (y >= map->size)
        return (0);
    if (x >= map->grid[y].size)
        return (0);
    return (map->grid[y].line[x]);
}

void    set_pos(t_map *map, size_t x, size_t y, char val)
{
    if (y >= map->size)
        return ;
    if (x >= map->grid[y].size)
        return ;
    map->grid[y].line[x] = val;
}