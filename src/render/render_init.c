/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshoweky <wshoweky@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:22:02 by wshoweky          #+#    #+#             */
/*   Updated: 2025/09/08 11:49:41 by wshoweky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	clear_image(mlx_image_t *img);
void		render_frame(t_fdf *fdf);
int			render_init(t_fdf *fdf);

int	render_init(t_fdf *fdf)
{
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (!fdf->img)
	{
		ft_putendl_fd("mlx error!", 2);
		return (ERROR);
	}
	if (mlx_image_to_window(fdf->mlx, fdf->img, 0, 0) < 0)
	{
		ft_putendl_fd("mlx error!", 2);
		return (ERROR);
	}
	return (SUCCESS);
}

void	render_frame(t_fdf *fdf)
{
	clear_image(fdf->img);
	camera_project(fdf->camera, fdf->map);
	draw_wireframe(fdf);
}

static void	clear_image(mlx_image_t *img)
{
	unsigned int	*pixel;
	unsigned int	i;

	pixel = (unsigned int *)img->pixels;
	i = 0;
	while (i < img->width * img->height)
	{
		pixel[i] = 0x000000;
		i++;
	}
}
