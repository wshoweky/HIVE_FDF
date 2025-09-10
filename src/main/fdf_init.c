/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshoweky <wshoweky@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 12:20:24 by wshoweky          #+#    #+#             */
/*   Updated: 2025/09/08 11:37:38 by wshoweky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	struct_init(t_fdf *fdf);
static void	camera_init(t_camera *camera, t_map *map);
void		fdf_run(t_fdf *fdf);
void		fdf_cleanup(t_fdf *fdf);
int			fdf_init(t_fdf *fdf, char *filename);

int	fdf_init(t_fdf *fdf, char *filename)
{
	if (struct_init(fdf) != SUCCESS)
		return (ERROR);
	if (map_load(fdf->map, filename) != SUCCESS)
	{
		fdf_cleanup(fdf);
		return (ERROR);
	}
	camera_init(fdf->camera, fdf->map);
	fdf->mlx = mlx_init(WIDTH, HEIGHT, TITLE, true);
	if (!fdf->mlx)
	{
		fdf_cleanup(fdf);
		return (ERROR);
	}
	if (render_init(fdf) != SUCCESS)
	{
		fdf_cleanup(fdf);
		return (ERROR);
	}
	return (SUCCESS);
}

static int	struct_init(t_fdf *fdf)
{
	fdf->map = ft_calloc(1, sizeof (t_map));
	if (!fdf->map)
		return (ERROR);
	fdf->camera = ft_calloc(1, sizeof(t_camera));
	if (!fdf->camera)
	{
		free(fdf->map);
		return (ERROR);
	}
	return (SUCCESS);
}

static void	camera_init(t_camera *camera, t_map *map)
{
	camera->zoom = fmin(WIDTH / map->width / 2, HEIGHT / map->height / 2);
	if (camera->zoom < 1)
		camera->zoom = 1;
	camera->angle_x = -0.5;
	camera->angle_y = 0.0;
	camera->angle_z = 0.3;
	camera->offset_x = WIDTH / 2;
	camera->offset_y = HEIGHT / 2;
	camera->projection = ISO;
	camera->color_mode = OFF;
}

void	fdf_run(t_fdf *fdf)
{
	mlx_key_hook(fdf->mlx, &key_hook, fdf);
	mlx_scroll_hook(fdf->mlx, &scroll_hook, fdf);
	render_frame(fdf);
	mlx_loop(fdf->mlx);
}

void	fdf_cleanup(t_fdf *fdf)
{
	if (!fdf)
		return ;
	if (fdf->map)
	{
		map_free(fdf->map);
		free(fdf->map);
		fdf->map = NULL;
	}
	if (fdf->camera)
	{
		free(fdf->camera);
		fdf->camera = NULL;
	}
	if (fdf->mlx)
	{
		if (fdf->img)
			mlx_delete_image(fdf->mlx, fdf->img);
		mlx_terminate(fdf->mlx);
		fdf->mlx = NULL;
	}
}
