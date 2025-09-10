/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_vertex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshoweky <wshoweky@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:46:13 by wshoweky          #+#    #+#             */
/*   Updated: 2025/09/08 11:41:10 by wshoweky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	update_vertex_colors(t_map *map);
void	update_z_bounds(t_map *map, int z_value, int i, int j);
int		process_line_data(t_map *map, char **numbers, int y);
int		parse_vertex(t_vertex *vertex, const char *str, int x, int y);

int	parse_vertex(t_vertex *vertex, const char *str, int x, int y)
{
	char	**parts;

	parts = ft_split(str, ',');
	if (!parts)
	{
		ft_putendl_fd("Memory failed!", 2);
		return (ERROR);
	}
	vertex->world.x = (float)x;
	vertex->world.y = (float)y;
	vertex->world.z = (float)ft_atoi(parts[0]);
	if (vertex->world.z >= 1000 || vertex->world.z <= -1000)
	{
		free_split(parts);
		ft_putendl_fd("Error: Z value out of range!", 2);
		return (ERROR);
	}
	if (parts[1])
		vertex->color = parse_color(parts[1]);
	else
		vertex->color = WHITE;
	free_split(parts);
	return (SUCCESS);
}

void	update_z_bounds(t_map *map, int z_value, int i, int j)
{
	if (i == 0 && j == 0)
	{
		map->z_min = z_value;
		map->z_max = z_value;
	}
	else
	{
		if (z_value < map->z_min)
			map->z_min = z_value;
		if (z_value > map->z_max)
			map->z_max = z_value;
	}
}

int	process_line_data(t_map *map, char **numbers, int y)
{
	int	x;

	x = 0;
	while (x < map->width)
	{
		if (parse_vertex(&map->vertices[y][x], numbers[x], x, y) != SUCCESS)
			return (ERROR);
		update_z_bounds(map, (int)map->vertices[y][x].world.z, y, x);
		x++;
	}
	return (SUCCESS);
}

void	update_vertex_colors(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->vertices[y][x].color == WHITE)
			{
				map->vertices[y][x].color = get_color(
						(int)map->vertices[y][x].world.z,
						map->z_min,
						map->z_max
						);
			}
			x++;
		}
		y++;
	}
}
