/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshoweky <wshoweky@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:21:34 by wshoweky          #+#    #+#             */
/*   Updated: 2025/09/08 11:49:50 by wshoweky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate_x(t_point *point, float angle);
static void	rotate_y(t_point *point, float angle);
static void	rotate_z(t_point *point, float angle);
static void	project_vertex(t_vertex *vertex, t_camera *camera);
void		camera_project(t_camera *camera, t_map *map);

static void	rotate_x(t_point *point, float angle)
{
	float	prev_y;

	prev_y = point->y;
	point->y = prev_y * cos(angle) + point->z * sin(angle);
	point->z = -prev_y * sin(angle) + point->z * cos(angle);
}

static void	rotate_y(t_point *point, float angle)
{
	float	prev_x;

	prev_x = point->x;
	point->x = prev_x * cos(angle) + point->z * sin(angle);
	point->z = -prev_x * sin(angle) + point->z * cos(angle);
}

static void	rotate_z(t_point *point, float angle)
{
	float	prev_x;

	prev_x = point->x;
	point->x = prev_x * cos(angle) - point->y * sin(angle);
	point->y = prev_x * sin(angle) + point->y * cos(angle);
}

static void	project_vertex(t_vertex *vertex, t_camera *camera)
{
	t_point	point;

	point = vertex->world;
	rotate_x(&point, camera->angle_x);
	rotate_y(&point, camera->angle_y);
	rotate_z(&point, camera->angle_z);
	if (camera->projection == ISO)
	{
		vertex->screen.x = (point.x - point.y) * cosf(0.523599);
		vertex->screen.y = (point.x + point.y) * sinf(0.523599) - point.z;
	}
	else
	{
		vertex->screen.x = point.x;
		vertex->screen.y = point.y;
	}
	vertex->screen.x *= camera->zoom;
	vertex->screen.y *= camera->zoom;
	vertex->screen.x += camera->offset_x;
	vertex->screen.y += camera->offset_y;
}

void	camera_project(t_camera *camera, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			project_vertex(&map->vertices[y][x], camera);
			x++;
		}
		y++;
	}
}
