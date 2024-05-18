#include "cub3d.h"

// NEED TO DOUBLEC CHECK IF TRASH IN HEADERS
bool    parse_file(t_game *game, char *filename)
{
    int     fd;
    bool    ret;

    fd = open(filename, O_RDONLY);
    ret = false;
    if (fd == -1)
        return (false);
    if (parse_headers(game, fd) && parse_map(game, fd))
        ret = true;
    close(fd);
    return (ret);
}