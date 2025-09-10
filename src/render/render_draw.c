/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshoweky <wshoweky@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:36:31 by wshoweky          #+#    #+#             */
/*   Updated: 2025/09/08 11:49:38 by wshoweky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		draw_wireframe(t_fdf *fdf);
static void	draw_line_loop(mlx_image_t *img, t_line *params);
static void	draw_horizontal_line(t_fdf *fdf, int y, int x);
static void	draw_vertical_line(t_fdf *fdf, int y, int x);

static void	draw_horizontal_line(t_fdf *fdf, int y, int x)
{
	if (x < fdf->map->width - 1)
		draw_line(fdf->img, fdf->map->vertices[y][x],
			fdf->map->vertices[y][x + 1], fdf);
}

static void	draw_vertical_line(t_fdf *fdf, int y, int x)
{
	if (y < fdf->map->height - 1)
		draw_line(fdf->img, fdf->map->vertices[y][x],
			fdf->map->vertices[y + 1][x], fdf);
}

void	draw_wireframe(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			draw_horizontal_line(fdf, y, x);
			draw_vertical_line(fdf, y, x);
			x++;
		}
		y++;
	}
}

static void	draw_line_loop(mlx_image_t *img, t_line *params)
{
	int		i;
	int		x;
	int		y;
	int		current_color;
	float	ratio;

	i = 0;
	while (i <= params->steps)
	{
		x = (int)params->x;
		y = (int)params->y;
		if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
		{
			if (params->steps > 0)
				ratio = (float)i / params->steps;
			else
				ratio = 0.0f;
			current_color = interpolate_color(params->start_color,
					params->end_color, ratio);
			mlx_put_pixel(img, x, y, current_color);
		}
		params->x += params->x_inc;
		params->y += params->y_inc;
		i++;
	}
}

void	draw_line(mlx_image_t *img, t_vertex start, t_vertex end, t_fdf *fdf)
{
	int		dx;
	int		dy;
	int		steps;
	t_line	params;

	dx = (int)end.screen.x - (int)start.screen.x;
	dy = (int)end.screen.y - (int)start.screen.y;
	steps = fmax(abs(dx), abs(dy));
	if (!steps)
		return ;
	params.x = start.screen.x;
	params.y = start.screen.y;
	params.x_inc = dx / (float)steps;
	params.y_inc = dy / (float)steps;
	params.steps = steps;
	params.start_color = get_vertex_color(&start,
			fdf->map, fdf->camera->color_mode);
	params.end_color = get_vertex_color(&end,
			fdf->map, fdf->camera->color_mode);
	draw_line_loop(img, &params);
}
