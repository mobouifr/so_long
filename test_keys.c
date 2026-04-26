#include "so_long.h"
#include <stdio.h>

int	debug_key(int keycode, void *param)
{
	(void)param;
	printf("Keycode received: %d\n", keycode);
	fflush(stdout);
	return (0);
}

int	main(void)
{
	void	*mlx;
	void	*window;

	mlx = mlx_init();
	if (!mlx)
	{
		printf("MLX init failed\n");
		return (1);
	}
	window = mlx_new_window(mlx, 800, 600, "Key Test - Press arrow keys");
	if (!window)
	{
		printf("Window creation failed\n");
		return (1);
	}
	printf("Window created. Press arrow keys (UP, DOWN, LEFT, RIGHT) and ESC\n");
	printf("Keycodes will be printed below:\n");
	mlx_key_hook(window, debug_key, NULL);
	mlx_hook(window, 17, 0, debug_key, NULL);
	mlx_loop(mlx);
	return (0);
}
