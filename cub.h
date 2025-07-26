/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamdao <achamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:01:06 by achamdao          #+#    #+#             */
/*   Updated: 2025/07/22 13:36:03 by achamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB
#define CUB

# include "lbft/libft.h"
# include "parisng_file/get_next_line.h"
# include <mlx.h>

typedef struct s_part_file
{
    char    **part_paths;
    char    **part_colors;
    char    **part_map;    
} t_part_file;

typedef struct s_color
{
    int red;
    int green;
    int blue;    
} t_color;

typedef struct s_info_cub
{
    char    *wall_north;
    char    *wall_south;
    char    *wall_west;
    char    *wall_east;
    t_color ceiling;
    t_color floor;
    t_part_file parts_file;
    char    **map;
    float    x;
    float    y;
} t_info_cub;

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

#endif