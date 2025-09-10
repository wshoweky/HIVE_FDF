/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshoweky <wshoweky@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:48:48 by wshoweky          #+#    #+#             */
/*   Updated: 2025/09/08 11:40:03 by wshoweky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	count_numbers(const char *line, char delimiter);
static int	validate_line_width(const char *line, int expected_width);
static int	count_map_lines(int fd, int width, int *height);
int			get_map_dimensions(const char *filename, t_map *map);

static int	count_numbers(const char *line, char delimiter)
{
	int	count;
	int	in_point;

	count = 0;
	in_point = 0;
	if (!line)
		return (0);
	while (*line)
	{
		if (*line != delimiter && !ft_isspace(*line) && !in_point)
		{
			in_point = 1;
			count++;
		}
		else if (*line == delimiter || ft_isspace(*line))
			in_point = 0;
		line++;
	}
	return (count);
}

static int	validate_line_width(const char *line, int expected_width)
{
	int	actual_width;

	actual_width = count_numbers(line, ' ');
	if (!actual_width)
	{
		ft_putendl_fd("Error: Map file contains empty lines", 2);
		return (ERROR);
	}
	if (actual_width != expected_width || actual_width == 1)
	{
		ft_putendl_fd("Error: Map is not rectangular!", 2);
		return (ERROR);
	}
	return (SUCCESS);
}

static int	count_map_lines(int fd, int width, int *height)
{
	char	*line;

	*height = 0;
	while (set_next_line(fd, &line))
	{
		if (!line)
			break ;
		if (validate_line_width(line, width) != SUCCESS)
		{
			free(line);
			return (ERROR);
		}
		(*height)++;
		free(line);
	}
	return (SUCCESS);
}

int	get_map_dimensions(const char *filename, t_map *map)
{
	int		fd;
	char	*line;
	int		width;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error_return("File does not exist or cannot be opened"));
	if (!set_next_line(fd, &line) || !line)
		return (free_and_close(fd, line, "Map file is empty or invalid"));
	width = count_numbers(line, ' ');
	if (width <= 1)
		return (free_and_close(fd, line, "Map file is empty or invalid"));
	if (validate_line_width(line, width) != SUCCESS)
		return (free_and_close(fd, line, "Map file is empty or invalid"));
	free(line);
	if (count_map_lines(fd, width, &map->height) != SUCCESS)
		return (free_and_close(fd, NULL, "Map is not rectangular!"));
	close(fd);
	map->width = width;
	map->height++;
	return (SUCCESS);
}
