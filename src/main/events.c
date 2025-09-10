/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshoweky <wshoweky@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:02:18 by wshoweky          #+#    #+#             */
/*   Updated: 2025/09/08 12:47:36 by wshoweky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	handle_zoom(mlx_key_data_t keydata, t_fdf *fdf);
static void	handle_rotation(mlx_key_data_t keydata, t_fdf *fdf);
static void	handle_movement(mlx_key_data_t keydata, t_fdf *fdf);
void		key_hook(mlx_key_data_t keydata, void *param);
void		scroll_hook(double xdelta, double ydelta, void *param);

static void	handle_movement(mlx_key_data_t keydata, t_fdf *fdf)
{
	if (keydata.key == MLX_KEY_W
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		fdf->camera->offset_y -= 10;
	else if (keydata.key == MLX_KEY_S
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		fdf->camera->offset_y += 10;
	else if (keydata.key == MLX_KEY_A
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		fdf->camera->offset_x -= 10;
	else if (keydata.key == MLX_KEY_D
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		fdf->camera->offset_x += 10;
}

static void	handle_rotation(mlx_key_data_t keydata, t_fdf *fdf)
{
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
		fdf->camera->angle_x += 0.2;
	else if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
		fdf->camera->angle_x -= 0.2;
	else if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
		fdf->camera->angle_y += 0.2;
	else if (keydata.key == MLX_KEY_T && keydata.action == MLX_PRESS)
		fdf->camera->angle_y -= 0.2;
}

static void	handle_zoom(mlx_key_data_t keydata, t_fdf *fdf)
{
	if (keydata.key == MLX_KEY_EQUAL && keydata.action == MLX_PRESS)
	{
		fdf->camera->zoom *= 1.1;
		if (fdf->camera->zoom > 100)
			fdf->camera->zoom = 100;
	}
	else if (keydata.key == MLX_KEY_MINUS && keydata.action == MLX_PRESS)
	{
		fdf->camera->zoom *= 0.9;
		if (fdf->camera->zoom < 0.1)
			fdf->camera->zoom = 0.1;
	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(fdf->mlx);
	else if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
		fdf->camera->projection = !fdf->camera->projection;
	else if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
		fdf->camera->color_mode = !fdf->camera->color_mode;
	else
	{
		handle_movement(keydata, fdf);
		handle_rotation(keydata, fdf);
		handle_zoom(keydata, fdf);
	}
	render_frame(fdf);
}

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_fdf	*fdf;

	(void)xdelta;
	fdf = (t_fdf *)param;
	if (ydelta > 0)
	{
		fdf->camera->zoom *= 1.1;
		if (fdf->camera->zoom > 100)
			fdf->camera->zoom = 100;
	}
	else if (ydelta < 0)
	{
		fdf->camera->zoom *= 0.9;
		if (fdf->camera->zoom < 0.1)
			fdf->camera->zoom = 0.1;
	}
	render_frame(fdf);
}
