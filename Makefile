NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBS = -lmlx -framework OpenGL -framework AppKit


SRCS = main.c \

OBJCT = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJCT)
	$(CC) $(CFLAGS) $(OBJCT) $(LIBS) -o $(NAME) 

clean :
	rm -f $(OBJCT)

fclean : clean
	rm -f $(NAME)

re : fclean all