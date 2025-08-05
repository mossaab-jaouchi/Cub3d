/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:01:06 by achamdao          #+#    #+#             */
/*   Updated: 2025/08/03 10:07:40 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB
#define CUB

# include "lbft/libft.h"
# include "parisng_file/get_next_line.h"
# include <math.h>
# include <mlx.h>

#define TILE_SIZE 60
#define WIDTH 1080
#define HEIGHT 800
#define DEG_TO_RAD(angle) ((angle) * M_PI / 180.0)

typedef struct s_tool_move {
    double move_x;
    double move_y;
    double angle;
    char signal;

    int key_w;
    int key_a;
    int key_s;
    int key_d;
    int key_left;
    int key_right;
} t_tool_move;


typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		width;
	int		height;
	int		endian;
}	t_img;

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct s_vars {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	**map;
}	t_vars;

typedef struct s_player {
	double	x;
	double	y;
	double	angle;
}	t_player;

typedef struct s_game {
	t_vars		vars;
	t_player	player;
	t_img		img;
	t_color		ceiling_color;
	t_color		floor_color;
	t_tool_move	tool_move;
	t_img		wall_texture;
}	t_game;

typedef struct s_part_file
{
	char	**part_paths;
	char	**part_colors;
	char	**part_map;    
}	t_part_file;


typedef struct s_info_cub
{
	t_color		ceiling;
	t_color		floor;
	char		**map;
	float		x;
	float		y;
	char		angle;
}	t_info_cub;

char	**stored_map(char *name);
char	check_input(int argc, char **argv);
short	free_matrex(char **matrex);
int     count_matrex(char **matrex);
int     get_length_map(char **matrex, short skeep);
char    is_whitespace(char c);
char    check_whitespace(char *str);
char    get_clean_map(char **matrex, char **clean_matrex, short skeep, int size);
char    get_path_color(char **matrex, char **clean_matrex, short skeep, int size);
char    storted_parts(char **file, t_part_file *part_file);
int     count_word(char *str, char *sep);
char	**new_split(char const *s, char* c);
char    parse_paths(t_info_cub *info_cub);
char    check_length(char **matrex, char *sep, int length);
char    parse_colors(t_info_cub *info_cub);
char    parse_map(char **map , t_info_cub *info_cube);
int     is_sep(char *sep, char char_str);
char    **split_in_two_parts(char *str, char *sep);
char	*ft_strndup(const char *src, size_t n);
void    print_matrix(char **matrix);
int     count_char(char *str, char c);
char    trim_matrix(char ***part_colors, char *sep);
char    parse_string_colors(char **temp, char ***numbers);
char    is_colors(char *str);
char    check_correct_char(char *line);
char    is_char_map(char c);
char    is_player_char(char c);
char    base_parsing_map(char *line, char **map, int index, int length_map);


//init
void	init_game(t_game *game, t_info_cub info);


#endif