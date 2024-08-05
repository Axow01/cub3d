/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_headers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 07:07:33 by mmarcott          #+#    #+#             */
/*   Updated: 2024/08/05 11:04:49 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// loads the path -> checks if the variable has already
// been set if so, returns false because duplicate symbol
bool	load_texture(t_game *instance, char *line)
{
	int				i;
	mlx_texture_t	*texture;

	i = 2;
	while (line[++i])
		if (line[i] != ' ')
			break ;
	texture = mlx_load_png(&line[i]);
	if (!texture)
		return (false);
	if (!ft_strncmp(line, "NO ", 3) && !instance->no_texture)
		instance->no_texture = texture;
	else if (!ft_strncmp(line, "SO ", 3) && !instance->so_texture)
		instance->so_texture = texture;
	else if (!ft_strncmp(line, "WE ", 3) && !instance->we_texture)
		instance->we_texture = texture;
	else if (!ft_strncmp(line, "EA ", 3) && !instance->ea_texture)
		instance->ea_texture = texture;
	else
	{
		mlx_delete_texture(texture);
		return (false);
	}
	return (true);
}

// Ugly need rework?
bool	get_color(const char *line, unsigned int *color)
{
	int	i;
	int	curr;
	int	j;

	i = 0;
	*color = 0;
	j = 0;
	if (ft_strlen(line) > 11)
		return (false);
	while (j < 3)
	{
		curr = ft_atoi(&line[i]);
		if (curr > 255 || curr < 0)
			return (false);
		while (line[i] && ft_isdigit(line[i]))
			i++;
		if (line[i] && line[i] == ',')
			i++;
		if ((line[i] && !ft_isdigit(line[i])) || (!line[i] && j < 2))
			return (false);
		*color += curr << (8 * (3 - j));
		j++;
	}
	*color += 255;
	return (j == 3 && !line[i]);
}

// replace with iswhitespace?
bool	color_from_text(t_game *instance, char *line)
{
	int				i;
	static bool		floor = false;
	static bool		ceiling = false;
	unsigned int	color;

	i = 1;
	color = 0;
	while (line[++i])
		if (line[i] != ' ')
			break ;
	if (!get_color(&line[i], &color))
		return (false);
	if (line[0] == 'C' && !ceiling)
	{
		ceiling = true;
		instance->ceiling_color = color;
	}
	else if (line[0] == 'F' && !floor)
	{
		floor = true;
		instance->floor_color = color;
	}
	else
		return (false);
	return (true);
}

// bool	test_norm(char *line, t_game *instance, bool *res, int fd)
// {
// 	int	found;

// 	found = 0;
// }

bool	parse_headers(t_game *instance, int fd)
{
	char	*line;
	bool	res;
	int		found;

	line = get_next_line(fd);
	res = true;
	found = 0;
	while (line)
	{
		if (ft_strchr(line, '\n'))
			*ft_strchr(line, '\n') = 0;
		if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
			|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
			res = load_texture(instance, line);
		else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
			res = color_from_text(instance, line);
		else if (ft_strlen(line) < 1)
		{
			mms_free(line);
			line = get_next_line(fd);
			continue ;
		}
		mms_free(line);
		if (!res)
			return (false);
		found++;
		if (found == 6)
			return (true);
		line = get_next_line(fd);
	}
	return (false);
}
