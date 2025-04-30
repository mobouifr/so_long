/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_mvp_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:56:41 by mobouifr          #+#    #+#             */
/*   Updated: 2024/05/20 14:15:34 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player_up(t_game *game)
{
	if (game->map[game->py - 1][game->px] == 'E' && game->col_count == 0)
	{
		game->moves_count++;
		write(1, "moves count : ", 15);
		ft_putnbr_nl(game->moves_count);
		close_window(game);
	}
	if (game->map[game->py - 1][game->px] == '0' || game->map[game->py
		- 1][game->px] == 'C')
	{
		if (game->map[game->py - 1][game->px] == 'C')
			game->col_count--;
		game->map[game->py - 1][game->px] = 'P';
		game->map[game->py][game->px] = '0';
		game->py--;
		game->moves_count++;
		write(1, "moves count : ", 15);
		ft_putnbr_nl(game->moves_count);
	}
}

void	move_player_down(t_game *game)
{
	if (game->map[game->py + 1][game->px] == 'E' && game->col_count == 0)
	{
		game->moves_count++;
		write(1, "moves count : ", 15);
		ft_putnbr_nl(game->moves_count);
		close_window(game);
	}
	if (game->map[game->py + 1][game->px] == '0' || game->map[game->py
		+ 1][game->px] == 'C')
	{
		if (game->map[game->py + 1][game->px] == 'C')
			game->col_count--;
		game->map[game->py + 1][game->px] = 'P';
		game->map[game->py][game->px] = '0';
		game->py++;
		game->moves_count++;
		write(1, "moves count : ", 15);
		ft_putnbr_nl(game->moves_count);
	}
}

void	move_player_left(t_game *game)
{
	if (game->map[game->py][game->px - 1] == 'E' && game->col_count == 0)
	{
		game->moves_count++;
		write(1, "moves count : ", 15);
		ft_putnbr_nl(game->moves_count);
		close_window(game);
	}
	if (game->map[game->py][game->px - 1] == '0' || game->map[game->py][game->px
		- 1] == 'C')
	{
		if (game->map[game->py][game->px - 1] == 'C')
			game->col_count--;
		game->map[game->py][game->px - 1] = 'P';
		game->map[game->py][game->px] = '0';
		game->px--;
		game->moves_count++;
		write(1, "moves count : ", 15);
		ft_putnbr_nl(game->moves_count);
	}
}

void	move_player_right(t_game *game)
{
	if (game->map[game->py][game->px + 1] == 'E' && game->col_count == 0)
	{
		game->moves_count++;
		write(1, "moves count : ", 15);
		ft_putnbr_nl(game->moves_count);
		close_window(game);
	}
	if (game->map[game->py][game->px + 1] == '0' || game->map[game->py][game->px
		+ 1] == 'C')
	{
		if (game->map[game->py][game->px + 1] == 'C')
			game->col_count--;
		game->map[game->py][game->px + 1] = 'P';
		game->map[game->py][game->px] = '0';
		game->px++;
		game->moves_count++;
		write(1, "moves count : ", 15);
		ft_putnbr_nl(game->moves_count);
	}
}
