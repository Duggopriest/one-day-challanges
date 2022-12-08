#include "../includes/chaos_sim.h"

void    pixel_put(t_render *r, int x, int y, int color)
{
        if (x >= r->w || x <= 0 || y <= 0 || y >= r->h)
                return ;

        char    *dst;

        dst = r->addr + (y * r->line_length + x * (r->bits_per_pixel / 8));
        *(unsigned int *)dst = color;
}

int     pixel_get(t_render *r, int x, int y)
{
        char    *dst;

        dst = r->addr + (y * r->line_length + x * (r->bits_per_pixel / 8));
        return (*(unsigned int *)dst);
}

void    draw_square(t_render *r, int x, int y, int color)
{
        int size = 0;
        if (size == 0)
        {
                pixel_put(r, x, y, color);
                return ;
        }
        for (int ox = -size; ox < size; ox++)
        {
                for (int oy = -size; oy < size; oy++)
                {
                        pixel_put(r, x + ox, y + oy, color);
                }
        }
}

void	movePixel(int oy, int ox, int ny, int nx, t_render *r)
{
	pixel_put(r, ox, oy, 0);


	r->grid[ny][nx].used = 1;
	r->grid[ny][nx].type = r->grid[oy][ox].type;
	r->grid[ny][nx].color = r->grid[oy][ox].color;

	r->grid[oy][ox].used = 0;
	r->grid[oy][ox].type = 0;
	r->grid[oy][ox].color = 0;

	pixel_put(r, nx, ny, r->grid[ny][nx].color);
}

void	dust(int x, int y, t_render *r)
{
	if (r->grid[y + 1][x].type == 3)
	{
		if ((rand() % 3 ? 0:1))
		{
			r->grid[y][x].type = 3;
			r->grid[y][x].color = 0x000000FF;
			r->grid[y + 1][x].type = 2;
			r->grid[y + 1][x].color = 0x00FFFFFF;
			pixel_put(r, x, y + 1, r->grid[y + 1][x].color);
			pixel_put(r, x, y, r->grid[y][x].color);
		}
	}
	else if (r->grid[y + 1][x + 1].used == 0 && r->grid[y + 1][x - 1].used == 0)
		movePixel(y, x, y + 1, (rand() % 2 ? x-1:x+1), r);
	else if (r->grid[y + 1][x].used == 0 && r->grid[y + 1][x - 1].used != 0)
		movePixel(y, x, y + 1, x + 1, r);
	else if (r->grid[y + 1][x].used == 0 && r->grid[y + 1][x + 1].used != 0)
		movePixel(y, x, y + 1, x - 1, r);
	else if (r->grid[y + 1][x].used == 0)
		movePixel(y, x, y + 1, x, r);
	else if (r->grid[y + 1][x + 1].used == 0 && r->grid[y][x + 1].used == 0)
		movePixel(y, x, y + 1, x + 1, r);
	else if (r->grid[y + 1][x - 1].used == 0 && r->grid[y][x - 1].used == 0)
		movePixel(y, x, y + 1, x - 1, r);
	
}

void	liquid(int x, int y, t_render *r)
{
	if (r->grid[y + 1][x + 1].used == 0 && r->grid[y + 1][x - 1].used == 0)
		movePixel(y, x, y + 1, (rand() % 2 ? x-1:x+1), r);
	else if (r->grid[y + 1][x].used == 0)
		movePixel(y, x, y + 1, x, r);
	else if (r->grid[y + 1][x + 1].used == 0 && r->grid[y][x + 1].used == 0)
		movePixel(y, x, y + 1, x + 1, r);
	else if (r->grid[y + 1][x - 1].used == 0 && r->grid[y][x - 1].used == 0)
		movePixel(y, x, y + 1, x - 1, r);
	else if (r->grid[y + 1][x].used == 1 && r->grid[y][x - 1].used != 1 || r->grid[y][x + 1].used != 1)
	{
		int L = x - 1;
		int R = x + 1;
		while (L > 0 && r->grid[y][L].used == 0)
		{
			if (r->grid[y + 1][L].used == 0 || -L - x > 100)
				break ;
			L--;
		}
		while (R < r->w && r->grid[y][R].used == 0)
		{
			if (r->grid[y + 1][R].used == 0 || R - x > 100)
				break ;
			R++;
		}
		L -= x;
		R -= x;
		if (-L == R)
			movePixel(y, x, y, (rand() % 2 ? x-1:x+1), r);
		else if(R > -L)
			movePixel(y, x, y, x + ((int)(R * .8) % R), r);
		else if (-L > R)
			movePixel(y, x, y, x - ((int)(-L * .8) % -L), r);
	}
}

// set current spot to black thn change color of next spot
void    sim_dot(int x, int y, t_render *r)
{
	if (r->grid[y][x].type == 2)
		dust(x, y, r);
	else if (r->grid[y][x].type == 3)
		liquid(x, y, r);
	else if (r->grid[y][x].type == 1)
		pixel_put(r, x, y, 0x00FFFF00);
}
