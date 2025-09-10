#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"

# define WIDTH 1920
# define HEIGHT 1080
# define TITLE "FdF - Wireframe Viewer"

# define ISO 1
# define OFF 0
# define SUCCESS 0
# define ERROR -1

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_Q 113
# define KEY_E 101
# define KEY_R 114
# define KEY_T 116
# define KEY_PLUS 61
# define KEY_MINUS 45

# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}	t_point;

typedef struct s_vertex
{
	t_point	world;
	t_point	screen;
	int		color;
}	t_vertex;

typedef struct s_map
{
	t_vertex	**vertices;
	int			width;
	int			height;
	int			z_min;
	int			z_max;
}	t_map;

typedef struct s_camera
{
	float	zoom;
	float	angle_x;
	float	angle_y;
	float	angle_z;
	float	offset_x;
	float	offset_y;
	int		projection;
	int		color_mode;
}	t_camera;

typedef struct s_line
{
	float	x;
	float	y;
	float	x_inc;
	float	y_inc;
	int		steps;
	int		start_color;
	int		end_color;
}	t_line;

typedef struct s_fdf
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_map		*map;
	t_camera	*camera;
}	t_fdf;

/* Main functions */
void	fdf_run(t_fdf *fdf);
void	fdf_cleanup(t_fdf *fdf);
void	key_hook(mlx_key_data_t keydata, void *param);
void	scroll_hook(double xdelta, double ydelta, void *param);
int		fdf_init(t_fdf *fdf, char *filename);
int		free_and_close(int fd, char *line, char *msg);
void	free_split(char **numbers);
int		error_return(char *msg);
void	error_exit(char *msg);

/* Map functions */
void	map_free(t_map *map);
void	update_vertex_colors(t_map *map);
void	update_z_bounds(t_map *map, int z_value, int i, int j);
int		map_load(t_map *map, char *filename);
int		ft_isdigit_hex(char c);
int		process_line_data(t_map *map, char **numbers, int y);
int		parse_vertex(t_vertex *vertex, const char *str, int x, int y);
int		get_map_dimensions(const char *filename, t_map *map);

/* Render functions */
void	camera_project(t_camera *camera, t_map *map);
void	draw_wireframe(t_fdf *fdf);
void	draw_line(mlx_image_t *img, t_vertex start, t_vertex end, t_fdf *fdf);
void	render_frame(t_fdf *fdf);
int		render_init(t_fdf *fdf);
int		parse_color(char *color_str);
int		get_color(int z, int z_min, int z_max);
int		interpolate_color(int start_color, int end_color, float ratio);
int		get_vertex_color(t_vertex *vertex, t_map *map, int color_mode);

#endif

