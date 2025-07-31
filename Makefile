CC = cc
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
FLAGS_MLX = -lmlx -framework OpenGL -framework AppKit
NAME = cube
# HEADERS = parisng_file/get_next_line.h cub.h
# LBFT = lbft/libft.a
SRCS =  ray-casting/ray-casting.c 

OBJS = $(SRCS:.c=.o)


all : $(NAME)

$(NAME) : $(OBJS) $(OBJS_PARS)
	$(CC) $(FLAGS)  $^ $(FLAGS_MLX) -o $@


%.o: %.c cub.h
	$(CC) $(FLAGS) -c $<  -o $@

clean:
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all
PHONY : clean

