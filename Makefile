NAME = cub3D
SRC  = main.c parsing.c utils.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -fPIE
LIBFTDIR = libft/
LIBFT = $(LIBFTDIR)libft.a

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	gcc $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@ -I./

clean:
	rm -rf $(OBJ)
	$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all
