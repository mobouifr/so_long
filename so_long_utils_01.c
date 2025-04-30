/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils_01.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:47:28 by mobouifr          #+#    #+#             */
/*   Updated: 2024/05/19 21:48:30 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	fill_map_extension(t_game *game, char *str, int fd)
{
	int	i;
	int	j;

	j = -1;
	while (++j < game->hight)
	{
		game->map[j] = malloc(sizeof(char) * (game->width + 1));
		if (game->map[j] == NULL)
		{
			free(str);
			ft_free(game, j);
			write(2, "Error\nAllocation failed\n", 24);
			exit(0);
		}
		i = -1;
		while (++i < game->width)
			game->map[j][i] = str[i];
		game->map[j][i] = '\0';
		free(str);
		str = get_next_line(fd);
	}
	game->map[j] = NULL;
}

int	fill_map(t_game *game)
{
	int		fd;
	char	*str;

	fd = open(game->path, O_RDONLY);
	str = get_next_line(fd);
	fill_map_extension(game, str, fd);
	close(fd);
	return (0);
}

int	map_check(t_game game)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	if (game.map == NULL)
		return (1);
	while (++j < game.hight)
	{
		if (game.map[j][0] != '1' || game.map[j][game.width - 1] != '1')
		{
			ft_free(&game, game.hight);
			return (1);
		}
	}
	while (++i < game.width)
	{
		if (game.map[0][i] != '1' || game.map[game.hight - 1][i] != '1')
		{
			ft_free(&game, game.hight);
			return (1);
		}
	}
	return (0);
}

int	check_textures_files(void)
{
	int	fd;

	fd = open("textures/wall.xpm", O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	fd = open("textures/collectible.xpm", O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	fd = open("textures/player.xpm", O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	fd = open("textures/floor.xpm", O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	fd = open("textures/exit.xpm", O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}
