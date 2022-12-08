#include "../includes/chaos_sim.h"

void	spawn_dot(t_render *r)
{
	int i = 0;
	while (i < 10)
	{
		int x =  rand() % r->w;
		int y = 10;
		if (1)//(rand() % 2)
		{
			r->grid[y][x].used = 1;
			r->grid[y][x].type = 2;
			r->grid[y][x].color = 0x00FFFFFF;
		}
		else
		{
			r->grid[y][x].used = 1;
			r->grid[y][x].type = 3;
			r->grid[y][x].color = 0x00aaaaFF;
		}
		i++;
	}
}

void	run_threads(t_render *r)
{
	int x;
	int	y;

	while (1)
	{
		r->sync = 0;
		y = r->h - 5;
		while (--y > 0)
		{
			x = r->w;
			while (--x > 0)
			{
				if (r->grid[y][x].type != 0)
					sim_dot(x, y, r);
			}
		}
		spawn_dot(r);
		y = r->h - 5;
		while (--y > 0)
		{
			x = 0;
			while (++x < r->w)
			{
				if (r->grid[y][x].type != 0)
					sim_dot(x, y, r);
			}
		}
		r->sync = 1;
		usleep(1000);
		spawn_dot(r);
	}
}

void	init_threads(t_render *r)
{
	r->thread = malloc(sizeof(pthread_t));

	printf("thread...");
	pthread_create(r->thread, NULL,
		(void *)run_threads, r);
	printf("created\n");
}
