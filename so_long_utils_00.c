/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils_00.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:56:37 by mobouifr          #+#    #+#             */
/*   Updated: 2024/05/13 17:19:03 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_strlen_v2(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	set_dimension(t_game *game)
{
	int		i;
	int		fd;
	char	*str;

	fd = open(game->path, O_RDONLY);
	if (fd < 0)
		return (1);
	str = get_next_line(fd);
	if (str == NULL)
		return (1);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		game->width++;
		i++;
	}
	while (str != NULL)
	{
		game->hight++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	rec_check(t_game game)
{
	int		fd;
	char	*str;

	fd = open(game.path, O_RDONLY);
	str = get_next_line(fd);
	while (str != NULL)
	{
		if (ft_strlen_v2(str) != game.width)
		{
			free(str);
			return (1);
		}
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	char_check_extension(int *tab, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		if (str[i] != '1' && str[i] != '0'
			&& str[i] != 'P' && str[i] != 'C' && str[i] != 'E')
			return (1);
		else if (str[i] == 'P')
			tab[0]++;
		else if (str[i] == 'C')
			tab[1]++;
		else if (str[i] == 'E')
			tab[2]++;
		i++;
	}
	return (0);
}

int	char_check(t_game game)
{
	int		tab[3];
	int		fd;
	char	*str;

	tab[0] = 0;
	tab[1] = 0;
	tab[2] = 0;
	fd = open(game.path, O_RDONLY);
	str = get_next_line(fd);
	while (str != NULL)
	{
		if (char_check_extension(tab, str) == 1)
		{
			free (str);
			return (1);
		}
		free(str);
		str = get_next_line(fd);
	}
	if (tab[0] != 1 || tab[1] < 1 || tab[2] != 1)
		return (1);
	return (0);
}
