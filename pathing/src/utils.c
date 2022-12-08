#include "../includes/pathing.h"

void	draw_map(t_render *r)
{
	int x;
	int y;

	int size = 30;

	y = 0;
	while(y < r->map_h)
	{
		x = 0;
		while(x < r->map_w)
		{
			if (r->map[y][x] == '1')
				mlx_put_image_to_window(r->mlx, r->mlx_win, r->wall, x * size, y * size);
			else if (r->map[y][x] == '0')
				mlx_put_image_to_window(r->mlx, r->mlx_win, r->ground, x * size, y * size);	
			else if (r->map[y][x] == 'C')
				mlx_put_image_to_window(r->mlx, r->mlx_win, r->coin, x * size, y * size);	
			else if (r->map[y][x] == 'G')
				mlx_put_image_to_window(r->mlx, r->mlx_win, r->goal, x * size, y * size);
			else if (r->map[y][x] == 'X')
				mlx_put_image_to_window(r->mlx, r->mlx_win, r->scanned, x * size, y * size);	
			else if (r->map[y][x] == 'S')
				mlx_put_image_to_window(r->mlx, r->mlx_win, r->scanner, x * size, y * size);
			else if (r->map[y][x] == 'P' || r->map[y][x] == 'p')
			{
				mlx_put_image_to_window(r->mlx, r->mlx_win, r->ground, x * size, y * size);	
				mlx_put_image_to_window(r->mlx, r->mlx_win, r->player, x * size, y * size);
			}
			x++;
		}
		y++;
	}
}

void	count_obj(char *str, t_render *r)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'C')
			r->amount_coins++;
		else if (str[i] == 'G')
			r->amount_goals++;
		i++;
	}
}

void	grab_textures(t_render *r)
{
	int w,h;

	r->wall = mlx_xpm_file_to_image(r->mlx, "./img/wall.xpm", &w, &h);
	r->ground = mlx_xpm_file_to_image(r->mlx, "./img/ground.xpm", &w, &h);
	r->coin = mlx_xpm_file_to_image(r->mlx, "./img/coin.xpm", &w, &h);
	r->goal = mlx_xpm_file_to_image(r->mlx, "./img/goal.xpm", &w, &h);
	r->scanner = mlx_xpm_file_to_image(r->mlx, "./img/scanner.xpm", &w, &h);
	r->scanned = mlx_xpm_file_to_image(r->mlx, "./img/scanned.xpm", &w, &h);
	r->player = mlx_xpm_file_to_image(r->mlx, "./img/player.xpm", &w, &h);
}

void	replace(char target, char replacement, t_render *r)
{
	int x;
	int y;

	y = 1;
	while(y < r->map_h - 1)
	{
		x = 1;
		while (x < r->map_w - 1)
		{
			if (r->map[y][x] == target)
				r->map[y][x] = replacement;
			x++;
		}
		y++;
	}
}

void	set_up_grid(t_render *r, char *path)
{
	int fd;
	int i;

	r->map = malloc(sizeof(char *) * 100); // map cant be more then 100 high

	fd = open(path, O_RDONLY);

	i = 0;
	while (1)
	{
		r->map[i] = get_next_line(fd);
		if (r->map[i] == NULL)
			break ;
		count_obj(r->map[i], r);
		i++;
	}
	r->map_h = i;
	r->map_w = ft_strlen(r->map[1]) - 1;
	close(fd);
}

int randomRange(int min, int max){
   return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

void	randomized_map(int map_size, t_render *r)
{
	int x;
	int y;
	int	ran;

	srand(time(0));

	r->map_h = map_size;
	r->map_w = map_size * 2;

	r->map = malloc(sizeof(char *) * map_size);

	y = 0;
	while (y < map_size)
	{
		r->map[y] = malloc(map_size * 2);
		x = 0;
		while (x < map_size * 2)
		{
			ran = rand() % 100;
			if (ran < 10)
				r->map[y][x] = 'C';
			if (ran >= 10 && ran < 35)
				r->map[y][x] = '1';
			if (ran >= 35 && ran <= 100)
				r->map[y][x] = '0';
			if (x == 0 || x == r->map_w - 1 || y == 0 || y == r->map_h - 1)
				r->map[y][x] = '1';
			x++;
		}
		count_obj(r->map[y], r);
		y++;
	}
	r->amount_goals++;
	r->map[randomRange(1, map_size - 2)][randomRange(1, map_size - 2)] = 'G';
	r->map[randomRange(1, map_size - 2)][randomRange(1, map_size - 2)] = 'P';
	printf("random map created\n");
}

void	randomized_set_map(int map_size, t_render *r)
{
	int x;
	int y;
	int	ran;
	static int randti = 0;

	srand(time(0) + randti++);

	r->map_h = map_size;
	r->map_w = map_size * 2;


	y = 0;
	while (y < map_size)
	{
		x = 0;
		while (x < map_size * 2)
		{
			ran = rand() % 100;
			if (ran < 10)
				r->map[y][x] = 'C';
			if (ran >= 10 && ran < 50)
				r->map[y][x] = '1';
			if (ran >= 50 && ran <= 100)
				r->map[y][x] = '0';
			if (x == 0 || x == r->map_w - 1 || y == 0 || y == r->map_h - 1)
				r->map[y][x] = '1';
			x++;
		}
		count_obj(r->map[y], r);
		y++;
	}
	r->amount_goals++;
	r->map[randomRange(1, map_size - 2)][randomRange(1, map_size - 2)] = 'G';
	r->map[randomRange(1, map_size - 2)][randomRange(1, map_size - 2)] = 'P';
	printf("random map created\n");
}

void	reset_map(t_render *r)
{
	r->steps = 0;
	r->amount_coins = 0;
	r->amount_goals = 0;
	r->scanned_coins = 0;
	r->scanned_goals = 0;
	randomized_set_map(r->map_size, r);
	draw_map(r);
}
