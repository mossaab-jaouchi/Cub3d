CC = cc
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
FLAGS_MLX = -lmlx -framework OpenGL -framework AppKit
NAME = cube
HEADERS = parisng_file/get_next_line.h cub.h
LBFT = lbft/libft.a
SRCS =  ray-casting/ray-casting.c  parisng_file/check_input.c  parisng_file/stored_map.c  parisng_file/get_next_line.c  parisng_file/free_matrex.c  \
		parisng_file/parse_paths.c  parisng_file/parse_colors.c parisng_file/get_parts_file.c  parisng_file/stored_parts_file.c  parisng_file/new_split.c \
		parisng_file/parse_map.c  parisng_file/split_in_two_parts.c  parisng_file/trim_matrix.c  parisng_file/parse_string_color.c  parisng_file/base_parsing_map.c 

OBJS = $(SRCS:.c=.o)


all : lbftm $(NAME)

$(NAME) : $(OBJS) $(LBFT) $(OBJS_PARS)
	$(CC) $(FLAGS)  $(LBFT) $^ $(FLAGS_MLX) -o $@

lbftm:
	@ make -C lbft

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) -c $<  -o $@

clean:
	rm -rf $(OBJS)
	make -C lbft clean
fclean : clean
	rm -rf $(NAME)
	make -C lbft fclean
re : fclean all
PHONY : clean

