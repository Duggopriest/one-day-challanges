#include "../includes/pathing.h"

void	mark(int x, int y, t_render *r)
{
	if (r->map[y][x] == '0')
		r->map[y][x] = 's';
	else if(r->map[y][x] == 'C')
	{
		r->map[y][x] = 's';
		r->scanned_coins++;
	}
	else if(r->map[y][x] == 'G')
	{
		r->map[y][x] = 's';
		r->scanned_goals++;
	}
}

int	is_walkable(int x, int y, t_render *r)
{
	if (r->map[y][x] == '0' || r->map[y][x] == 'C' || r->map[y][x] == 'G')
		return (1);
	return (0);
}

void	scan_directions(int x, int y, t_render *r)
{
	if (is_walkable(x - 1, y, r)) // left
		mark(x - 1, y, r);
	if (is_walkable(x + 1, y, r)) // right
		mark(x + 1, y, r);
	if (is_walkable(x, y - 1, r)) // up
		mark(x, y - 1, r);
	if (is_walkable(x, y + 1, r)) // down
		mark(x, y + 1, r);


	if (r->map[y][x] != 'P')
		r->map[y][x] = 'X';
	if (r->map[y][x] == 'P')
		r->map[y][x] = 'p';
}

int	step(t_render *r)
{
	int edits;

	edits = 0;
	int x;
	int y;

	y = 1; // set to one cause edges should be walled in anyways
	while(y < r->map_h - 1)
	{
		x = 1;
		while (x < r->map_w - 1)
		{
			if (r->map[y][x] == 'S' || r->map[y][x] == 'P')
			{
				scan_directions(x, y, r);
				edits++;
			}
			x++;
		}
		y++;
	}
	return (edits);
}