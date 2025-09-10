/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshoweky <wshoweky@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:57:00 by wshoweky          #+#    #+#             */
/*   Updated: 2025/09/08 12:19:12 by wshoweky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			map_load(t_map *map, char *filename);
void		map_free(t_map *map);
void		free_split(char **numbers);
static int	process_single_line(t_map *map, int fd, int i);
static int	fill_map_data(t_map *map, const char *filename);

int	map_load(t_map *map, char *filename)
{
	int	i;

	i = 0;
	if (get_map_dimensions(filename, map) != SUCCESS)
		return (ERROR);
	map->vertices = ft_calloc(map->height, sizeof(t_vertex *));
	if (!map->vertices)
		return (ERROR);
	while (i < map->height)
	{
		map->vertices[i] = ft_calloc(map->width, sizeof(t_vertex));
		if (!map->vertices[i])
		{
			map_free(map);
			return (ERROR);
		}
		i++;
	}
	if (fill_map_data(map, filename) != SUCCESS)
	{
		map_free(map);
		return (ERROR);
	}
	update_vertex_colors(map);
	return (SUCCESS);
}

static int	process_single_line(t_map *map, int fd, int i)
{
	char	*line;
	char	**numbers;

	line = get_next_line(fd);
	if (!line)
		return (ERROR);
	if (line[0] == '\n' || line[0] == '\0' || ft_strlen(line) <= 1)
	{
		free(line);
		return (ERROR);
	}
	numbers = ft_split(line, ' ');
	free(line);
	if (!numbers || !numbers[0])
	{
		free_split(numbers);
		return (ERROR);
	}
	if (process_line_data(map, numbers, i) != SUCCESS)
	{
		free_split(numbers);
		return (ERROR);
	}
	free_split(numbers);
	return (SUCCESS);
}

static int	fill_map_data(t_map *map, const char *filename)
{
	int	fd;
	int	i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ERROR);
	i = 0;
	while (i < map->height)
	{
		if (process_single_line(map, fd, i) != SUCCESS)
		{
			close (fd);
			return (ERROR);
		}
		i++;
	}
	close (fd);
	return (SUCCESS);
}

void	free_split(char **numbers)
{
	int	i;

	i = 0;
	if (!numbers)
		return ;
	while (numbers[i])
		free(numbers[i++]);
	free(numbers);
}

void	map_free(t_map *map)
{
	int	i;

	i = 0;
	if (!map || !map->vertices)
		return ;
	while (i < map->height)
	{
		if (map->vertices[i])
			free(map->vertices[i]);
		i++;
	}
	free(map->vertices);
	map->vertices = NULL;
}
