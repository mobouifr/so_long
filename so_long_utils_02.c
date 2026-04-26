/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils_02.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:56:50 by mobouifr          #+#    #+#             */
/*   Updated: 2024/05/20 14:15:55 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_positions(t_game *game)
{
	int	i;
	int	j;

	j = 0;
	while (game->map[j] != NULL)
	{
		i = 0;
		while (game->map[j][i] != '\0')
		{
			if (game->map[j][i] == 'C')
				game->col_count++;
			if (game->map[j][i] == 'P')
			{
				game->px = i;
				game->py = j;
			}
			if (game->map[j][i] == 'E')
			{
				game->ex = i;
				game->ey = j;
			}
			i++;
		}
		j++;
	}
}

void	draw_map(t_game *game)
{
	int	i;
	int	j;

	j = -1;
	while (game->map[++j] != NULL)
	{
		i = -1;
		while (game->map[j][++i] != '\0')
		{
			mlx_put_image_to_window(game->mlx, game->window, game->floor, (i
					* 45), (j * 45));
			if (game->map[j][i] == '1')
				mlx_put_image_to_window(game->mlx, game->window, game->wall, (i
						* 45), (j * 45));
			if (game->map[j][i] == 'C')
				mlx_put_image_to_window(game->mlx, game->window,
					game->collectible, (i * 45), (j * 45));
			if (game->map[j][i] == 'E')
				mlx_put_image_to_window(game->mlx, game->window, game->exit, (i
						* 45), (j * 45));
			if (game->map[j][i] == 'P')
				mlx_put_image_to_window(game->mlx, game->window, game->player,
					(i * 45), (j * 45));
		}
	}
}

int	move_player(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	if (keycode == KEY_DOWN)
		move_player_down(game);
	else if (keycode == KEY_UP)
		move_player_up(game);
	else if (keycode == KEY_LEFT)
		move_player_left(game);
	else if (keycode == KEY_RIGHT)
		move_player_right(game);
	mlx_clear_window(game->mlx, game->window);
	draw_map(game);
	return (0);
}
