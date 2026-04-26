# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 16:57:21 by mobouifr          #+#    #+#              #
#    Updated: 2024/05/20 14:26:04 by mobouifr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long 
SRC = so_long.c\
		so_long_utils_00.c\
		so_long_utils_01.c\
		so_long_mvp_utils.c\
		so_long_utils_02.c\
		so_long_utils_03.c\
		ft_putnbr_nl.c\
      ./get_next_line/get_next_line.c\
	  ./get_next_line/get_next_line_utils.c
OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
MLX_DIR = minilibx-linux
CPPFLAGS = -I$(MLX_DIR)
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lbsd
MLX_BUILD = $(MAKE) -C $(MLX_DIR)
else
MLX_DIR = minilibx_macos_opengl/minilibx_opengl_20191021
CPPFLAGS = -I$(MLX_DIR)
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
MLX_BUILD = $(MAKE) -C $(MLX_DIR)
endif

all: $(NAME)

$(NAME): $(OBJ)
	$(MLX_BUILD)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) -o $(NAME)

%.o: %.c so_long.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJ)