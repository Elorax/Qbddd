/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:04:41 by abiersoh          #+#    #+#             */
/*   Updated: 2022/06/20 11:35:11 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include "minilibx/mlx.h"
# include "minilibx/mlx_int.h"
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <time.h>
# include "gnl/get_next_line.h"
# include "libft/libft.h"
# define TRUE 1
# define FALSE 0
# define COLOR_UNSET -1
# define ERROR_BAD_COLOR -2
# define ERROR_FUCK_MALLOC -3
# define ERROR_PARAMETERS  -4

# include <X11/X.h>

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3
# define MESSAGE 4
# define MOVESPEED 5.0
# ifndef FOV
#  define FOV 90.0
# endif
# define PI 3.1415
# define ZOOM_FORCE 3
# define ROTSPEED 0.25


# define RIGHT_CLICK 3
# define LEFT_CLICK 1
# define MIDDLE_CLICK 2
# define R_KEY 114
# define W_KEY 119
# define A_KEY 97
# define Z_KEY 122
# define P_KEY 112
# define Q_KEY 113
# define S_KEY 115
# define D_KEY 100
# define SPACE_BAR 32
# define ESCAPE_KEY 65307
# define SHIFT_KEY 65505
# define UP_KEY 65362
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define DOWN_KEY 65364
# define W_HEIGHT	600
# define W_LENGTH	800
# define CTRL_KEY 65507
# define INITIAL_Z_SPEED 42.42
# define JUMP_HEIGHT 4.69	//0.44 JOLIE VALEUR

typedef int	t_pixel;

typedef struct	s_line
{
	int		facing;
	int		upper_wall;
	int		lower_wall;
	double	x_pix_wall;
}	t_line;

typedef struct s_raycasting
{
	double	ray_x;//cameraX
	double	ray_dir_x;	//rayDirX
	double	ray_dir_y;	//rayDirY
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	diff_dist_x;
	double	diff_dist_y;
	double	dist_perp_wall; //perpWallDist
	int		step_x;	//stepX
	int		step_y;	//stepY	//maybe replacing by cardinal ?
	int		has_hit;	//hit
	int		facing;	//side
	int		line_height;	//lineHeight
	int		upper_wall;	//lowerWall
	int		lower_wall;	//upperWall
	double	x_pix_wall;	//wallX
	t_line	line[10];	//3 a changer maybe
	int		nb_wall;
}	t_raycasting;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		height;
	int		width;
}	t_image;

typedef struct s_movements
{
	int	move_x;
	int	move_y;
	int	try_move_x;
	int	try_move_y;
	int	rotate;
}	t_movements;

typedef struct s_player
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	lookingX;
	double	lookingY;
	double	planeX;
	double	planeY;
	int		zoom;
	int		stamina;
	int		sprint;
	int		try_sprint;
	int		can_sprint;
	double	height;
	double	z_speed;
	double	z_accel;
	int		is_jumping;
	double	ms;
}	t_player;

typedef struct s_data
{
	int			fd;
	int			diff_x;
	int			mouse_pressed;
	int			left_pressed;
	int			mouse_x;
	int			mouse_y;
	int			mouse_initial_x;
	int			mouse_initial_y;
	char		**map;
	char		*path_north;
	char		*path_south;
	char		*path_east;
	char		*path_west;
	t_pixel		Fcolor;
	t_pixel		Ccolor;
	int			nb_param;
	int			begin_map;
	int			end_map;
	int			map_size;
	int			map_length;
	void		*mlx;
	void		*win;
	t_image		img[5];
	t_image		render[2];
	int			frame;
	t_player	*player;
	t_movements	*move;
	clock_t		begin;
	clock_t		current;
	long		current_ms;
	long		begin_ms;
	double		time_diff;
}	t_data;

//# define INITIAL_Z_ACCEL -INITIAL_Z_SPEED*INITIAL_Z_SPEED;

void	update_movements(t_data *data);
void	update_stamina(t_data *data);
void	update_jump(t_data *data);
double	calcul_movespeed(t_data *data);
void	update_player(t_data *data);
void	update_player_y(t_data *data);
void	update_player_x(t_data *data);
void	update_player_direction(t_data *data);
void	update_player_rotation(t_data *data);
void	draw_black_line(t_image *img, int x, int up, int down);


void	draw_black(t_image *img);
void	staminamina_heyhey(t_image *img, t_data *data);
int		init_draw_line(t_data *d, t_raycasting *ray, t_image **img, int *x_img);
int		draw_walls(t_data *data, t_raycasting *ray, t_image **img, int *x_img);

void	set_mouse_position(t_data *data, int x, int y);


//raycasting
void	init_raycasting(int x, t_raycasting *ray, t_player *player);
void	calcul_dist(t_raycasting *ray);
void	calcul_initial_dist(t_raycasting *ray, t_player *player);
void	casting_ray(t_raycasting *ray, t_data *data, int nb_wall);
double	calcul_perpendiculary_dist(t_raycasting ray);
void	calcul_wall_drawing(t_raycasting *ray, t_player *player, int nb_wall);

void	get_intersec(int x, int ray, int *up, int *down);

void	init_movements(t_movements *move);
void	reading(char *av, t_data *data, t_player *player, t_movements *move);
int		init_frames(t_data *data);
void	create_big(t_data *data);
double	double_abs(double d);
void	draw_line(t_image *img, t_data *data, int x, t_raycasting *ray);
void	pixel_put(t_image *img, int x, int y, int color);
void	build_image(t_image *img, t_data *data, t_player *player);
int		get_color(t_image *img, int x, int y);

double	double_abs(double d);
int		handle_no_event(t_data *data);

int		init_images(t_data *data, t_image *img);
int		read_line(char *line, t_data *data);
int		read_color(char *line, t_data *data);
void	free_data(t_data *data);
char	*ft_strstr(const char *str, const char *tofind);
int		is_8bits_int(char *line);
char	*ft_remove_newline_space(char *line);
char	*ft_remove_newline(char *line);
int		is_line_valid(char *line, t_data *data);
int		check_around_zero(char **map, int i, int j);
int		check_map(char **map, t_data *data);
void	ft_freesplit(char **s);
int		countchar(char *line, char c);
char	**formatting_split(char *line, char sep, char *trim);
void	init_data(t_data *data);
int		is_arg_valid(int ac, char **av);
void	read_map_parameters(t_data *data);
void	count_map_size(t_data *data);
void	read_map(t_data *data, char *path);
void	print_data(t_data data);
int		exit_hook(t_data *data);
int		key_hook(int keycode, t_data *data);
void	manage_movement(t_data *data, int keycode);
void	ft_mlx_close_game(t_data *data);
void	ft_mlx_close_croix_rouge_de_ses_morts(t_data *data);

int	key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);
int	mouse_press(int keycode, int x, int y, t_data *data);
int	mouse_release(int keycode, int x, int y, t_data *data);

#endif
