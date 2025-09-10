/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshoweky <wshoweky@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:45:09 by wshoweky          #+#    #+#             */
/*   Updated: 2025/09/08 11:49:45 by wshoweky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	parse_color(char *color_str);
int	get_color(int z, int z_min, int z_max);
int	interpolate_color(int start_color, int end_color, float ratio);
int	get_vertex_color(t_vertex *vertex, t_map *map, int color_mode);

/*
** Converts a hexadecimal character to its integer value.
** Handles both lowercase and uppercase hex digits (0-9, a-f, A-F).
*/
static int	hex_to_int(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (0);
}

/*
** Parses a hexadecimal color string to an integer color value.
** Skips "0x" prefix if present and adds full alpha channel (0xFF).
*/
int	parse_color(char *color_str)
{
	int	color;
	int	i;

	if (!color_str)
		return (WHITE);
	color = 0;
	i = 0;
	if (color_str[0] == '0' && (color_str[1] == 'x' || color_str[1] == 'X'))
		i = 2;
	else if (ft_strchr(color_str, 'x') || ft_strchr(color_str, 'X'))
		return (WHITE);
	while (color_str[i] && ft_isdigit_hex(color_str[i]))
	{
		color = color * 16 + hex_to_int(color_str[i]);
		i++;
	}
	return (color << 8 | 0xFF);
}

/*
** Generates a color based on Z-coordinate height for terrain visualization.
** Creates a gradient from blue through green to red with full alpha.
** Returns white if all heights are the same (flat terrain).
*/
int	get_color(int z, int z_min, int z_max)
{
	double	percentage;
	int		red;
	int		green;
	int		blue;

	if (z_max == z_min)
		return (WHITE);
	percentage = (double)(z - z_min) / (z_max - z_min);
	if (percentage < 0.5)
	{
		red = (int)(255 * percentage * 2);
		green = 255;
		blue = 255 - red;
	}
	else
	{
		red = 255;
		green = (int)(255 * (1 - percentage) * 2);
		blue = 0;
	}
	return ((red << 24) | (green << 16) | (blue << 8) | 0xFF);
}

/*
** Interpolate between two colors based on a ratio (0.0 to 1.0).
** ratio = 0.0 returns start_color, ratio = 1.0 returns end_color.
*/
int	interpolate_color(int start_color, int end_color, float ratio)
{
	int	start_rgb[3];
	int	end_rgb[3];
	int	rgb[3];
	int	i;

	if (ratio <= 0.0f)
		return (start_color);
	if (ratio >= 1.0f)
		return (end_color);
	start_rgb[0] = (start_color >> 24) & 0xFF;
	start_rgb[1] = (start_color >> 16) & 0xFF;
	start_rgb[2] = (start_color >> 8) & 0xFF;
	end_rgb[0] = (end_color >> 24) & 0xFF;
	end_rgb[1] = (end_color >> 16) & 0xFF;
	end_rgb[2] = (end_color >> 8) & 0xFF;
	i = 0;
	while (i < 3)
	{
		rgb[i] = start_rgb[i] + (int)((end_rgb[i] - start_rgb[i]) * ratio);
		i++;
	}
	return ((rgb[0] << 24) | (rgb[1] << 16) | (rgb[2] << 8) | 0xFF);
}

/*
** Get vertex color based on color mode.
** color_mode = ON: Use height-based colors or custom colors from map
** color_mode = OFF: Use only original colors from map (WHITE if no custom color)
*/
int	get_vertex_color(t_vertex *vertex, t_map *map, int color_mode)
{
	if (color_mode == OFF)
	{
		if (vertex->color == get_color((int)vertex->world.z,
				map->z_min, map->z_max))
			return (WHITE);
		return (vertex->color);
	}
	return (vertex->color);
}
