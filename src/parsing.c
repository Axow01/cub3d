#include "cub3d.h"

bool    parse_file(t_game *game, char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (false);
    if (!parse_headers(game, fd))
    {
        printf("Failed to parse headers!\n");
        return (false);
    }
    if (!validate_map(game, fd))
    {
        printf("Failed to parse map!\n");
        return (false);
    }
    return (true);
}