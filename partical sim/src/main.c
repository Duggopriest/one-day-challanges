#include "../includes/chaos_sim.h"

int	keypress(int k, t_render *r)
{
	
	if (k == 65307 || k == 53)
		exit(1);
		
	return (0);
}

int	render_next_frame(t_render *r)
{
	if (r->sync)
		mlx_put_image_to_window(r->mlx, r->mlx_win, r->img, 0, 0);
	if (r->draw == 1)
	{	
		int x,y;
		mlx_mouse_get_pos(r->mlx_win, &x, &y);
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				r->grid[y + j][x + i].used = 1;
				r->grid[y + j][x + i].type = 1;
				r->grid[y + j][x + i].color = 0x00FFFF00;
			}
		}
	}
	if (r->erase == 1)
	{	
		r->draw = -1;
		int x,y;
		mlx_mouse_get_pos(r->mlx_win, &x, &y);
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				r->grid[y + j][x + i].used = 0;
				r->grid[y + j][x + i].type = 0;
				r->grid[y + j][x + i].color = 0x00000000;
				pixel_put(r, x + i, y + j, 0);
			}
		}
	}
	return (1);
}

void	set_up_grid(t_render *r)
{
	printf("grid ... ");
	r->grid = malloc(sizeof(char *) * r->h + 1);
	int y = 0;
	int	x;
	while (y < r->h)
	{
		//printf("%d\n", y);
		r->grid[y] = malloc(sizeof(t_pixel) * r->w + 1);
		x = 0;
		while (x <= r->w)
		{
			if (y >= r->h)
			{
				r->grid[y][x].used = 1;
				r->grid[y][x].type = 1;
				r->grid[y][x].color = 0x0000FF00;
			}
			else
			{
				r->grid[y][x].used = 0;
				r->grid[y][x].type = 0;
				r->grid[y][x].color = 0;
			}
			x++;
		}
		y++;
	}
	printf("done\n");
}

int	on_click(int button, int x, int y, t_render *r)
{
	if (y > 0 && y < r->h - 10 && x > 0 && x < r->w - 10 && button == 1)
	{
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 50; j++)
			{
				r->grid[y + j][x + i].used = 1;
				r->grid[y + j][x + i].type = 3;
				r->grid[y + j][x + i].color = 0x000000FF;
			}
		}
	}
	else if (y > 0 && y < r->h && x > 0 && x < r->w && button == 2)
		r->draw = -r->draw;
	else if (y > 0 && y < r->h && x > 0 && x < r->w && button == 3)
		r->erase = -r->erase;
	return (1);
}

int	main(int argc, const char **argv)
{
	t_render	*r;
	r = malloc(sizeof(t_render));

	r->draw = -1;
	r->erase = -1;

	r->w = 2550;
	r->h = 1300;
	r->mlx = mlx_init();
	r->mlx_win = mlx_new_window(r->mlx, r->w, r->h, "partical sim");
	r->img = mlx_new_image(r->mlx, r->w, r->h);
	r->addr = mlx_get_data_addr(r->img, &r->bits_per_pixel, &r->line_length, &r->endian);

	set_up_grid(r);

	init_threads(r);

	mlx_key_hook(r->mlx_win, keypress, r);
	mlx_loop_hook(r->mlx, render_next_frame, r);
	mlx_mouse_hook(r->mlx_win, on_click, r);
	mlx_loop(r->mlx);
}
