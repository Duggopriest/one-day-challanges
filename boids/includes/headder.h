
#ifndef HEADDER_H
# define HEADDER_H

# include "mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <pthread.h>

extern double SPEED;

typedef struct s_dot
{
    double  x;
    double  y;
	double  vx;
    double  vy;
    double  d;
}   t_dot;

typedef struct s_render {
	int			dot_num;
	t_dot			*dots;
	pthread_t	*thread;

	int			h;
	int			w;
	void		*mlx;
	void		*mlx_win;

	void		*img;
	char		*addr;
	int			endian;
	int			line_length;
	int			bits_per_pixel;
}	t_render;

void    sim_dot(t_dot *dot, t_render *r);
void	pixel_put(t_render *r, int x, int y, int color);
void	init_threads(t_render *r);

#endif