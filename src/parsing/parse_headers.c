#include "cub3d.h"

bool load_texture(t_game *instance, char *line)
{
	int	i;

	i = 3;
	while (line[++i])
		if (line[i] != ' ')
			break;
}

// replace with iswhitespace?
bool set_colors(t_game *instance, char *line)
{
	int				i;
	unsigned int	*ptr;

	i = 1;
	while (line[++i])
		if (line[i] != ' ')
			break;
	
}

bool parse_headers(t_game *instance, int fd)
{
	char	*line;
	int		found;
	bool	res;

	found = 0;
	line = mu_gnl(fd);
	res = true;
	while (line)
	{
		if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) ||
				!ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
			res = load_texture(instance, line);
		else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
			res = set_colors(instance, line);
		else if (ft_strlen(line))
			return (false);
		mm_free(line);
		if (!res)
			return (false);
		if (found == 6)
			return (true);
		line = mu_gnl(fd);
	}
	return (false);
}