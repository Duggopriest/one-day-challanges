#include "../includes/headder.h"

#define MODULO(a, n) fmod((a), (n)) + (((a) < 0) * (n))
#define INVERSE(theta) fmod((theta)+M_PI, 2*M_PI)

void	pixel_put(t_render *r, int x, int y, int color)
{
	if (x >= r->w || x <= 0 || y <= 0 || y >= r->h)
		return ;

	char	*dst;

	dst = r->addr + (y * r->line_length + x * (r->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void    drawLine(t_render *r, t_dot *dot, int color)
{
	double ox = dot->x;
	double oy = dot->y;

	for (int i = 0; i < 10; i++)
	{
		ox += cos(dot->d * 180 / 3.14);
		oy += sin(dot->d * 180 / 3.14);
		pixel_put(r, ox, oy, color);
	}

}
double	get_distance(double ax, double ay, double bx, double by)
{
	return (sqrt(pow(bx - ax, 2) + pow(by - ay, 2)));
}

double	min(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

float getRotation(double ax, double ay, double bx, double by) {
     //return atan2(-(ax - bx), (ay - by));
	 return (ax * bx + ay * by / sqrt(pow(ax, 2) + pow(ay, 2) * sqrt(pow(bx, 2) + pow(by, 2))));
}

void	open_box(t_dot *dot, t_render *r)
{
	if (dot->x < 10)
		dot->x = r->w - 15;
	else if (dot->x > r->w - 10)
		dot->x = 15;
	else if (dot->y < 10)
		dot->y = r->h - 15;
	else if (dot->y > r->h - 10)
		dot->y = 15;
}

double	AVG_X;
double	AVG_Y;
double	AVG_DIR;
int		NUM;
double	DIST;
double	CLOS;

// set current spot to black thn change color of next spot
void    sim_dot(t_dot *dot, t_render *r)
{
	//pixel_put(r, dot->x, dot->y, 0x00000000);
	drawLine(r, dot, 0);

	AVG_X = 0;
	AVG_Y = 0;
	AVG_DIR = 0;
	NUM = 0;
	CLOS = -1;
	int i = -1;
	while (++i < r->dot_num)
	{
		if (dot == &r->dots[i])
			continue;
		DIST = get_distance(dot->x, dot->y, r->dots[i].x, r->dots[i].y);
		if (DIST < 50 && DIST > 2 && dot != &r->dots[i])
		{
			AVG_X += r->dots[i].x;
			AVG_Y += r->dots[i].y;
			AVG_DIR += r->dots[i].d;
			NUM++;
		}
		if (DIST < CLOS || CLOS == -1)
			CLOS = DIST;
	}

	
	if (NUM > 0)
	{

		AVG_X /= NUM;
		AVG_Y /= NUM;
		AVG_DIR /= NUM;

		double targetRot = AVG_DIR - dot->d;

		if ((fabs(dot->d - AVG_DIR) > 0.05 && NUM > 5) || CLOS < 5)
			targetRot = getRotation(dot->x, dot->y, AVG_X, AVG_Y) - dot->d;

		targetRot = MODULO(targetRot, 2*M_PI);

		if (targetRot > M_PI)
			targetRot = INVERSE(targetRot)-M_PI;

		if (targetRot > 0.001 || targetRot < -0.001)
			targetRot = (targetRot > 0 ? 0.001 : -0.001);
		dot->d = fmod(dot->d + targetRot, 2*M_PI);	
	}

	dot->x += cos(dot->d * 180 / 3.14) * SPEED;
    dot->y += sin(dot->d * 180 / 3.14) * SPEED;	

	open_box(dot, r);
	//pixel_put(r, dot->x, dot->y, 0x0000FF00);
	drawLine(r, dot, 0x0000FF00);
}
