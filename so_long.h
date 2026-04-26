/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:57:15 by mobouifr          #+#    #+#             */
/*   Updated: 2024/05/19 21:48:30 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <limits.h>
# include <mlx.h>
# ifdef __linux__
#  define KEY_ESC 9
#  define KEY_UP 111
#  define KEY_DOWN 116
#  define KEY_LEFT 113
#  define KEY_RIGHT 114
# else
#  define KEY_ESC 53
#  define KEY_UP 126
#  define KEY_DOWN 125
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
# endif
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_game
{
	char	**map;
	char	*path;
	void	*mlx;
	void	*window;
	void	*wall;
	void	*collectible;
	void	*player;
	void	*floor;
	void	*exit;
	int		hight;
	int		width;
	int		w;
	int		h;
	int		px;
	int		py;
	int		ex;
	int		ey;
	int		col_count;
	int		moves_count;
}			t_game;

void		ft_putnbr_nl(int n);
void		n_zero_min(int n);
// so_long_utils_00 :
int			ft_strlen_v2(char *str);
int			set_dimension(t_game *game);
int			rec_check(t_game game);
int			char_check_extension(int *tab, char *str);
int			char_check(t_game game);
// so_long_utils_01 :
void		fill_map_extension(t_game *game, char *str, int fd);
int			fill_map(t_game *game);
int			map_check(t_game game);
int			check_textures_files(void);
// so _long_utils_02 :
void		get_positions(t_game *game);
void		draw_map(t_game *game);
int			move_player(int keycode, t_game *game);
// so_long_mvp_utils :
void		move_player_up(t_game *game);
void		move_player_down(t_game *game);
void		move_player_left(t_game *game);
void		move_player_right(t_game *game);
// so_long_utils_03 :
void		ft_free(t_game *game, int j);
void		check_extension(t_game game);
int			close_window(t_game *game);
void		flood_fill(t_game *game, int x, int y);
void		check_play(t_game game);

#endif