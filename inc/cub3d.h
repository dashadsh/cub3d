/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 15:31:17 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/10/06 22:30:24 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// ------------------------- LIBS -------------------------------
# include <stdio.h>
# include <stdlib.h> /* malloc, EXIT_SUCCESS; EXIT_FAILURE*/
# include <fcntl.h> /* open */
# include <math.h>
# include <stdbool.h>

// ------------------------ MINILIBX ----------------------------
# ifdef __APPLE__
#  include "../minilibx_opengl_20191021/mlx.h"
# else
#  include "../minilibx-linux/mlx.h"
# endif

// ------------------------- LIBFT -------------------------------
# include "../libft/libft.h"

// ------------------------- ERRORS ------------------------------
# define ERR_USAGE "Usage: ./cub3d <path/to/map.cub>"
# define ERR_OPEN "Couldn't open file"
# define ERR_EXTENTION "Invalid file extention"
# define ERR_MALLOC "Memory allocation failed"

# define ERR_MAP_NONE "Map: Not found"
# define ERR_MAP_LAST "Map: Should be the last element in file"

# define ERR_MAP_WALLS "Map: Should be surrounded by walls"
# define ERR_MAP_SMALL "Map: Should contain at least 3 lines & walls"
# define ERR_MAP_CHAR "Map: Contains invalid character"
# define ERR_MAP_TAB "Map: Tab instead of space"

# define ERR_MAP_P_MANY "Map: more than one player"
# define ERR_MAP_P_NONE "Map: no player found"
# define ERR_MAP_P_POS "Map: Invalid player position"

/* redundant -  check file retrieve_file_data */
# define ERR_MAP "Map: wrong or incomplete"

# define ERR_TEX "Textures: Invalid"
# define ERR_TEX_NONE "Textures: Missing data"

# define ERR_COL_NONE "Color: Missing"
# define ERR_COL_RGB_VAL "Color: Invalid RGB value"
# define ERR_COL_FC "Colors: Invalid F or C data"
# define ERR_COL_F "Colors: Invalid F data"
# define ERR_COL_C "Colors: Invalid C data"

# define ERR_MLX "Mlx: Startup error"
# define ERR_MLX_WIN "Mlx: Window error"

// -------------------------- DEBUG ------------------------------
# define DEBUG 0

// -------------------- KEYBOARD MACROS --------------------------

# ifdef __APPLE__
#  define W 13
#  define A 0
#  define S 1
#  define D 2
#  define ESC 53
#  define ARROW_LEFT 123
#  define ARROW_RIGHT 124
#  define X 17
# else
#  define W 119
#  define A 97
#  define S 115
#  define D 100
#  define ESC 65307
#  define ARROW_LEFT 65361
#  define ARROW_RIGHT 65363
#  define X 33
# endif

// -------------------------------------------------------

# define TILE_W 128
# define TILE_H 128
# define WIN_W 1200
# define WIN_H 900

# define MOVESPEED 0.0275
# define ROTSPEED 0.015

enum e_texture_index
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
};

enum e_status
{
	FAILURE = -42,
	SUCCESS = 0,
	TEXTURE_ADDED = 1
};

// -------------------------- STRUCT -----------------------------

/* this struct is used only temporary to check validity of the map */
typedef struct s_dfs
{
	char	**map;
	int		h;
	int		w;
	int		valid;
	int		dr[4];
	int		dc[4];
}	t_dfs;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	wall_dist;
	double	wall_x;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

/*
DATA CONTAINS:

2D map, modified so it becomes rectangular:
	char	**map; // data.map

mlx & window data:
	void	*mlx_ptr; // void *mlx
	void	*mlx_win; // void *win
	int		win_height; // added by marve
	int		win_width; // added by marve

saved .cub file:
	char	**cub_file; // s_mapinfo mapinfo.file
	char	*cub_path; // s_mapinfo mapinfo.path
	int		cub_height; // s_mapinfo mapinfo.line_count
	int		cub_fd; // s_mapinfo mapinfo.fd 
	int		map_height; // s_mapinfo mapinfo.height
	int		map_width; // s_mapinfo mapinfo.width
	int		map_end_idx; // s_mapinfo mapinfo.index_end_of_map;

path to texture:
	char	*tex_north; // s_texinfo textures.north
	char	*tex_east; // s_texinfo textures.east
	char	*tex_south; // s_texinfo textures.south
	char	*tex_west; // s_texinfo textures.west

	int		tex_size; // s_texinfo added by marve
	int		tex_index; // s_texinfo added by marve
	double	tex_step;  // s_textinfo added by marve	
	double	tex_pos;  // s_textinfo added by marve	
	int		tex_x;	// s_texinfo added by marve
	int		tex_y;	// s_texinfo added by marve

	int		**textures; // added by marve for textures
	int		**tex_pixels; // add by marve

arrays of 3 rgb int's:
	int		*col_ceiling;
	int		*col_floor;

result calculated from 3 rgb values:
	int	col_ceiling_int; // textures.hex_floor - 
			SIC! we can use INT instead of unsigned long, but SHOULD WE??
	int 	col_floor_int; // textures.hex_floor 

NEWS => direction player is looking:
	char	player_dir; // data->player.dir

idx of player on a **map (temporary used):
	int		player_x;
	int		player_y;

+0.5 to get REAL position on a grid:
	double	player_pos_x; // data->player.pos_x
	double	player_pos_y; // data->player.pos_x

other player data:
	double	player_dir_x; // data->player.dir_x
	double	player_dir_y; // data->player.dir_y
	double	player_plane_x; // data->player.plane_x
	double	player_plane_y; // data->player.plane_y
	int		player_move_x;   // added by marve
	int		player_move_y;   // added by marve
	int		player_rotate; // added by marve
	int		player_has_moved; // added by marve

t_ray	ray;   // added by marve
*/

typedef struct s_data
{
	char	**map;
	void	*mlx_ptr;
	void	*mlx_win;
	int		win_height;
	int		win_width;
	char	**cub_file;
	char	*cub_path;
	int		cub_height;
	int		cub_fd;
	int		map_height;
	int		map_width;
	int		map_end_idx;
	char	*tex_north;
	char	*tex_east;
	char	*tex_south;
	char	*tex_west;
	int		tex_size;
	int		tex_index;
	double	tex_step;
	double	tex_pos;
	int		tex_x;
	int		tex_y;
	int		**textures;
	int		**tex_pixels;
	int		*col_ceiling;
	int		*col_floor;
	int		col_ceiling_int;
	int		col_floor_int;
	char	player_dir;
	int		player_x;
	int		player_y;
	double	player_pos_x;
	double	player_pos_y;
	double	player_dir_x;
	double	player_dir_y;
	double	player_plane_x;
	double	player_plane_y;
	int		player_move_x;
	int		player_move_y;
	int		player_rotate;
	int		player_has_moved;
	t_ray	ray;

}	t_data;

// ------------------------- FILES --------------------------------

//  ------------------------ utils.c ---------------------------
bool	ft_isspace(char c);
void	print_error(char *error_msg);
bool	ft_isprint_no_space(int c);
size_t	ft_strlen_no_newline(const char *str);
size_t	find_max_width(t_data *data, int i);

//  ------------------------ utils2.c ---------------------------
int		open_file(char *filepath, t_data *data);
char	*ft_strdup2(const char *s1, int len);

// -------------------- init.c -----------------------------
void	init_img_null(t_img *img);	// added by marve
void	init_ray(t_ray *ray);
void	init_data_cub_map(t_data *data);
void	init_data_player(t_data *data);
void	init_data(t_data *data);

// -------------------- init_mlx.c -----------------------------
void	init_mlx(t_data *data);

// -------------------- init_textures.c -----------------------------
void	init_texture_pixels(t_data *data);
void	init_texture_img(t_data *data, t_img *image, char *path);
// static int	*xpm_to_img(t_data *data, char *path)
void	init_textures(t_data *data);

void	update_texture_pixels(t_data *data, t_ray *ray, int x);

// -------------------- image.c -----------------------------
// static int	*xpm_to_img(t_data *data, char *path);
void	render_images(t_data *data);

// -------------------- image.c -----------------------------
void	set_image_pixel(t_img *image, int x, int y, int color);
void	init_img(t_data *data, t_img *image, int width, int height);

// -------------------- ray.c -------------------------------
// static void	calculate_line_height(t_ray *ray, t_data *data)
// static void	perform_dda(t_data *data, t_ray *ray)
// static void	set_dda(t_ray *ray, t_data *data)
// static void	init_raycasting_info(int x, t_ray *ray, t_data *data)
int		raycasting(t_data *data);

// ---------------- render.c ------------------------
// static void	set_frame_image_pixel(t_data *data, t_img *image, int x, int y)
// static void	render_frame(t_data *data)
// static void	render_raycast(t_data *data)
void	render_images(t_data *data);
int		render(t_data *data);

// -------------- player_move.c ----------------------------
// static int	move_player_forward(t_data *data)
// static int	move_player_backward(t_data *data)
// static int	move_player_left(t_data *data)
// static int	move_player_right(t_data *data)
int		move_player(t_data *data);

// -------------- player_rotate.c ----------------------------
// static int	rotate_left_right(t_data *data, double rotspeed)
int		rotate_player(t_data *data, double rotdir);

// ------------------ validate_move.c ---------------------------
// static bool	is_valid_pos_in_map(t_data *data, double x, double y);
// static bool	is_valid_pos(t_data *data, double x, double y);
int		validate_move(t_data *data, double new_x, double new_y);

// -------------- get_input.c -------------------------
// static int	key_release_handler(int key, t_data *data)
// static int	key_press_handler(int key, t_data *data)
void	get_input(t_data *data);

// -------------------- parsing.c --------------------------
int		parsing(t_data *data, char **av);

// -------------------- save_file.c ------------------------
int		check_cub_file_extension(char *filename);
int		validate_cub_file(char *filename);
int		line_counter(char *filepath, t_data *data);
void	read_and_save_cub_file(int row, int col, int i, t_data *data);
void	save_cub(char *filepath, t_data *data);

// -------------------- retrieve_file_data.c --------------
// static char	*add_tex_path(char *line, int j)
// static int	add_textures(t_data *data, char *line, int j)
// static int	skip_spaces(t_data *data, char **cub_file, int i, int j)
int		retrieve_file_data(t_data *data, char **map);

// -------------------- add_colors.c -----------------------
// static bool	no_digit_found(char *str);
// static int	*convert_and_add_rgb(char **rgb_to_convert, int *rgb)
int		col_only_digits(char **map);
// static int	*add_rgb(char *line)
int		add_colors(t_data *data, char *line, int j);

// -------------------- add_map.c ---------------------------
// static int	fill_map_2d(t_data *data, char **map, int index)
// static int	count_map_lines(t_data *data, char **file, int i)
int		no_tabs(t_data *data);
// static int	retrieve_map_data(t_data *data, char **cub_file, int i)
int		add_map(t_data *data, char **cub_file, int i);

// -------------------- add_map2.c -------------------------
// static void	fill_line_with_ones(char *new_line, t_data *data)
// static void	copy_line(char *new_line, char *old_line)
void	make_map_rectangular(t_data *data);

// -------------------- validate_walls.c --------------------
void	init_map_data(t_dfs *map_data, t_data *data, char **map_clone);
void	dfs_recursive(t_dfs *map_data, int r, int c);
int		dfs(t_data *data, char **map_clone);
int		validate_walls(t_data *data);

// -------------------- validate_map.c -----------------------
// static int	check_map_is_at_the_end(t_data *data)
// static int	add_player_position(t_data *data, char **map)
// static int	check_map_elements(t_data *data, char **map)
int		validate_map(t_data *data, char **map);

// -------------------- validate_textures.c ------------------
// static unsigned long	rgb_to_int(int *rgb_arr)
// static int	validate_rgb(int *rgb)
int		check_xpm_file_extension(char *filename);
int		validate_xpm_file(char *filename);
int		validate_textures(t_data *data);

// ---------------- add_player_dir.c ------------------
// static void	player_north_south(t_data *data)
// static void	player_east_west(t_player *player)
void	add_player_direction(t_data *data);

// -------------------- free.c --------------------------------
void	free_array_2d(void **array_2d);
void	free_cub(t_data *data);
void	free_textures(t_data *data);
void	free_colors(t_data *data);
void	free_data(t_data *data);

// -------------------- exit.c --------------------------------
void	clean_exit(t_data *data, int exitstatus);
int		quit_cub3d(t_data *data);

// -------------------- debug.c -------------------------------
void	print_array_2d(char **array_2d);
void	print_array_2d_newline(char **array_2d);

#endif