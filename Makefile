NAME = cub3D

SRC = main.c parsing/parsing.c sources/utils.c sources/init.c sources/Raycasting.c sources/Raycasting2.c sources/moove_player.c sources/utils2.c  sources/gnl.c sources/moove_player2.c parsing/parsing2.c parsing/parsing3.c parsing/parsing4.c
OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -fPIE -g3
INCLUDES = -Ilibft -I./minilibx-linux

LIBFTDIR = libft/
LIBFT = $(LIBFTDIR)libft.a

MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a

LDFLAGS = -L$(LIBFTDIR) -L$(MLX_DIR)
LDLIBS = -lmlx -lXext -lX11 -lGL -lm

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LDFLAGS) $(LDLIBS)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFTDIR) -I$(MLX_DIR) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFTDIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all
