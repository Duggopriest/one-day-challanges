#include "../includes/pathing.h"

int	run_algo(t_render *r)
{
	if (r->scanned_coins >= r->amount_coins
		&& r->scanned_goals >= r->amount_goals)
	{
		printf("!!!PATH COMPLEATE!!!\n");
		return 0;
	}
	else if (step(r) > 0)
	{
		r->steps++;
		replace('s', 'S', r);
		draw_map(r);
		printf("coins %d scan %d\ngoal %d scan %d\nsteps %d\n", r->amount_coins, r->scanned_coins, r->amount_goals, r->scanned_goals, r->steps);
		return (1);
	}
	else
		printf("!!!FAILED!!!\n");
	draw_map(r);
	return (0);
}

int	keypress(int k, t_render *r)
{
	if (k == 65307 || k == 53)
		exit(1);
	if (k == 49)
		run_algo(r);
	if (k == 15)
		reset_map(r);
	return (0);
}

int	render_next_frame(t_render *r)
{
	if (!run_algo(r))
		reset_map(r);
	draw_map(r);
	//usleep(100000);
	return (1);
}

int	main(int argc, char **argv)
{
	t_render	*r;
	r = malloc(sizeof(t_render));

	r->steps = 0;
	r->amount_coins = 0;
	r->amount_goals = 0;
	r->scanned_coins = 0;
	r->scanned_goals = 0;

	r->map_size = 40;

	//set_up_grid(r, argv[1]);
	randomized_map(r->map_size, r);

	r->win_w = r->map_w * 30; // 100 comes from the size of the img
	r->win_h = r->map_h * 30;
	r->mlx = mlx_init();
	r->mlx_win = mlx_new_window(r->mlx, r->win_w, r->win_h, "pathing algo");

	grab_textures(r);

	draw_map(r);

	mlx_key_hook(r->mlx_win, keypress, r);
	mlx_loop_hook(r->mlx, render_next_frame, r);
	mlx_loop(r->mlx);
}
