/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils_03.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:56:31 by mobouifr          #+#    #+#             */
/*   Updated: 2024/05/20 14:31:45 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_free(t_game *game, int j)
{
	while (j >= 0)
	{
		free(game->map[j]);
		j--;
	}
	free(game->map);
}

int	close_window(t_game *game)
{
	ft_free(game, game->hight);
	mlx_destroy_window(game->mlx, game->window);
	exit(0);
}

void	check_extension(t_game game)
{
	int		i;
	int		j;
	char	*str;

	i = ft_strlen(game.path);
	j = 4;
	str = ".ber";
	if (game.path[i - 5] == '/' || i <= j)
	{
		write(2, "Error\nWrong file extension\n", 27);
		exit(0);
	}
	while (j >= 0)
	{
		if (game.path[i] != str[j])
		{
			write(2, "Error\nWrong file extension\n", 27);
			exit(0);
		}
		i--;
		j--;
	}
}

void	flood_fill(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'E')
		game->map[y][x] = '1';
	if (game->map[y][x] == 'P' || game->map[y][x] == 'C'
		|| game->map[y][x] == '0')
	{
		game->map[y][x] = '*';
		flood_fill(game, x + 1, y);
		flood_fill(game, x - 1, y);
		flood_fill(game, x, y + 1);
		flood_fill(game, x, y - 1);
	}
}

void	check_play(t_game game)
{
	int	i;
	int	j;

	j = 0;
	while (game.map[j] != NULL)
	{
		i = 0;
		while (game.map[j][i] != '\0')
		{
			if (game.map[j][i] == 'E' || game.map[j][i] == 'P'
				|| game.map[j][i] == 'C')
			{
				ft_free(&game, game.hight);
				write(2, "Error\nMap not playable\n", 23);
				exit(0);
			}
			i++;
		}
		j++;
	}
}
