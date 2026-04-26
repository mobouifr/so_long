/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:56:19 by mobouifr          #+#    #+#             */
/*   Updated: 2024/05/20 14:27:17 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	var_init(t_game *game)
{
	game->col_count = 0;
	game->moves_count = 0;
	game->width = 0;
	game->hight = 0;
	game->ex = 0;
	game->ey = 0;
	game->px = 0;
	game->py = 0;
	game->w = 0;
	game->h = 0;
}

void	map_alloc(t_game *game)
{
	game->map = malloc((sizeof(char *)) * (game->hight + 1));
	if (game->map == NULL)
		return ;
}

void	mlx_utils(t_game game)
{
	game.mlx = mlx_init();
	if (game.mlx == NULL)
	{
		write(2, "Error\nMLX initialization failed\n", 32);
		exit(1);
	}
	game.window = mlx_new_window(game.mlx, (game.width * 45), (game.hight * 45),
			"so_long");
	if (game.window == NULL)
	{
		write(2, "Error\nWindow initialization failed\n", 35);
		exit(1);
	}
	game.wall = mlx_xpm_file_to_image(game.mlx, "textures/wall.xpm", &game.w,
			&game.h);
	game.collectible = mlx_xpm_file_to_image(game.mlx,
			"textures/collectible.xpm", &game.w, &game.h);
	game.player = mlx_xpm_file_to_image(game.mlx, "textures/player.xpm",
			&game.w, &game.h);
	game.floor = mlx_xpm_file_to_image(game.mlx, "textures/floor.xpm", &game.w,
			&game.h);
	game.exit = mlx_xpm_file_to_image(game.mlx, "textures/exit.xpm", &game.w,
			&game.h);
	if (game.wall == NULL || game.collectible == NULL || game.player == NULL
		|| game.floor == NULL || game.exit == NULL)
	{
		write(1, "Error\nInvalid asset\n", 20);
		close_window(&game);
	}
	draw_map(&game);
	mlx_key_hook(game.window, move_player, &game);
	mlx_hook(game.window, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
}

void	game_make(t_game game)
{
	map_alloc(&game);
	fill_map(&game);
	get_positions(&game);
	if (map_check(game) == 1)
	{
		write(2, "Error\nInvalid map\n", 18);
		exit(0);
	}
	flood_fill(&game, game.px, game.py);
	check_play(game);
	ft_free(&game, game.hight);
	map_alloc(&game);
	fill_map(&game);
	mlx_utils(game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		write(2, "Error\nInvalid number of arguments\n", 34);
		exit(0);
	}
	if (check_textures_files() == 1)
	{
		write(2, "Error\nAsset file missing\n", 25);
		exit(0);
	}
	game.path = argv[1];
	check_extension(game);
	var_init(&game);
	set_dimension(&game);
	if (rec_check(game) == 1 || char_check(game) == 1)
	{
		write(2, "Error\nInvalid map\n", 18);
		exit(0);
	}
	game_make(game);
	return (0);
}
