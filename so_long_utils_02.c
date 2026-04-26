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

#define TILE_SIZE 45

/* Build each visible tile from the floor image first, then overlay the sprite. */
static void	copy_image_to_image(char *dst, int dst_size_line, char *src,
								int src_size_line, int bytes_per_pixel)
{
	int	y;

	y = 0;
	while (y < TILE_SIZE)
	{
		memcpy(dst + (y * dst_size_line), src + (y * src_size_line), TILE_SIZE
			* bytes_per_pixel);
		y++;
	}
}

static void	overlay_image_with_key(char *dst, int dst_size_line, char *src,
								int src_size_line, int bytes_per_pixel)
{
	int		x;
	int		y;
	char	*key_pixel;

	key_pixel = src;
	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			if (memcmp(src + (y * src_size_line) + (x * bytes_per_pixel),
					key_pixel, bytes_per_pixel) != 0)
				memcpy(dst + (y * dst_size_line) + (x * bytes_per_pixel), src
					+ (y * src_size_line) + (x * bytes_per_pixel), bytes_per_pixel);
			x++;
		}
		y++;
	}
}

/* Composite one map tile in memory before putting it on the window. */
static void	draw_tile(t_game *game, void *sprite, int x, int y)
{
	void	*tile;
	char	*tile_data;
	char	*floor_data;
	char	*sprite_data;
	int		tile_bpp;
	int		tile_size_line;
	int		tile_endian;
	int		floor_bpp;
	int		floor_size_line;
	int		floor_endian;
	int		sprite_bpp;
	int		sprite_size_line;
	int		sprite_endian;
	int		bytes_per_pixel;

	tile = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
	if (tile == NULL)
		return ;
	tile_data = mlx_get_data_addr(tile, &tile_bpp, &tile_size_line,
								&tile_endian);
	floor_data = mlx_get_data_addr(game->floor, &floor_bpp, &floor_size_line,
								&floor_endian);
	if (tile_data == NULL || floor_data == NULL)
	{
		mlx_destroy_image(game->mlx, tile);
		return ;
	}
	bytes_per_pixel = tile_bpp / 8;
	copy_image_to_image(tile_data, tile_size_line, floor_data, floor_size_line,
		bytes_per_pixel);
	if (sprite != NULL)
	{
		sprite_data = mlx_get_data_addr(sprite, &sprite_bpp, &sprite_size_line,
								&sprite_endian);
		if (sprite_data != NULL && sprite_bpp == tile_bpp)
			overlay_image_with_key(tile_data, tile_size_line, sprite_data,
								sprite_size_line, bytes_per_pixel);
	}
	mlx_put_image_to_window(game->mlx, game->window, tile, x, y);
	mlx_destroy_image(game->mlx, tile);
}

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
			if (game->map[j][i] == '1')
				draw_tile(game, game->wall, i * TILE_SIZE, j * TILE_SIZE);
			else if (game->map[j][i] == 'C')
				draw_tile(game, game->collectible, i * TILE_SIZE, j * TILE_SIZE);
			else if (game->map[j][i] == 'E')
				draw_tile(game, game->exit, i * TILE_SIZE, j * TILE_SIZE);
			else if (game->map[j][i] == 'P')
				draw_tile(game, game->player, i * TILE_SIZE, j * TILE_SIZE);
			else
				mlx_put_image_to_window(game->mlx, game->window, game->floor, i
					* TILE_SIZE, j * TILE_SIZE);
		}
	}
}

int	move_player(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		close_window(game);
		return (0);
	}
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
