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

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -lmlx -framework OpenGL -framework AppKit $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJ)