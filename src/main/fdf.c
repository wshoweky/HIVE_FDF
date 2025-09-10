/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshoweky <wshoweky@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 12:10:42 by wshoweky          #+#    #+#             */
/*   Updated: 2025/09/08 12:24:33 by wshoweky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	check_file_type(char *path);
static void	print_controls(void);

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (2 != argc)
		error_exit("Usage: ./fdf <filename.fdf>");
	if (ERROR == check_file_type(argv[1]))
		error_exit("Error: Invalid file format, Use .fdf files only!");
	ft_memset(&fdf, 0, sizeof(t_fdf));
	if (SUCCESS != fdf_init(&fdf, argv[1]))
	{
		fdf_cleanup(&fdf);
		error_exit("Error: Initialization failed");
	}
	print_controls();
	fdf_run(&fdf);
	fdf_cleanup(&fdf);
	return (SUCCESS);
}

static int	check_file_type(char *path)
{
	char	*type;

	type = ft_strchr(path, '.');
	if (!type)
		return (ERROR);
	if (ft_strncmp(type, ".fdf", 4) == 0)
		return (SUCCESS);
	else
		return (ERROR);
}

static void	print_controls(void)
{
	ft_printf("\n🎮 FdF - Advanced Controls:\n");
	ft_printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	ft_printf("🔄 Movement:     WASD\n");
	ft_printf("🔍 Zoom:         + (zoom in) / - (zoom out) or Mouse Scroll\n");
	ft_printf("🌀 Rotation:     Q/E (Rotate X) / R/T (Rotate Y)\n");
	ft_printf("🎨 Color Mode:   C (toggle height-based colors)\n");
	ft_printf("🔄 Projection:   P (toggle perspective)\n");
	ft_printf("🚪 Exit:         ESC\n");
	ft_printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
}
