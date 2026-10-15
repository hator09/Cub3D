#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "../minilibx/mlx.h"

/* Dimensions de la ventana */
# define WIN_WIDTH 1024
# define WIN_HEIGHT 768

/* 1. Estructura de Imágenes / Búfer de MiniLibX */
typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;         /* bits_per_pixel */
	int		line_len;    /* size_line */
	int		endian;
	int		width;
	int		height;
}	t_img;

/* 2. Estructura de Texturas y Colores (Llenada por Persona A) */
typedef struct s_tex
{
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	t_img			north;
	t_img			south;
	t_img			west;
	t_img			east;
	unsigned int	floor_color;   /* Formato 0x00RRGGBB */
	unsigned int	ceiling_color; /* Formato 0x00RRGGBB */
}	t_tex;

/* 3. Estructura del Mapa (Llenada por Persona A) */
typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	char	p_dir;       /* 'N', 'S', 'E' o 'W' */
}	t_map;

/* 4. Estructura del Jugador y Controles (Persona B) */
typedef struct s_player
{
	double	pos_x;       /* Posición X en la cuadrícula */
	double	pos_y;       /* Posición Y en la cuadrícula */
	double	dir_x;       /* Vector de dirección X */
	double	dir_y;       /* Vector de dirección Y */
	double	plane_x;     /* Plano de cámara X (FOV) */
	double	plane_y;     /* Plano de cámara Y (FOV) */
	int		move_w;      /* Flags de movimiento (WASD) */
	int		move_s;
	int		move_a;
	int		move_d;
	int		rotate_left; /* Flecha izquierda */
	int		rotate_right;/* Flecha derecha */
}	t_player;

/* 5. Estructura del Raycasting por columna (Persona B) */
typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;        /* 0 para muros E/O, 1 para N/S */
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
}	t_ray;

/* 6. Estructura Principal del Juego (Contenedor Global) */
typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		frame;    /* Búfer de imagen principal (double buffering) */
	t_map		map;
	t_tex		tex;
	t_player	player;
	t_ray		ray;
}	t_game;

#endif