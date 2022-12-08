
#ifndef CHAOS_SIM_H
# define CHAOS_SIM_H

# include "mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <pthread.h>

typedef	struct s_pixel
{
	char	used;
	char	type;
	int		color;
} t_pixel;


typedef struct s_render {
	pthread_t	*thread;

	char 		sync;
	char		draw;
	char		erase;

	t_pixel		**grid;

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

void    sim_dot(int y, int x, t_render *r);
void	pixel_put(t_render *r, int x, int y, int color);
void	init_threads(t_render *r);

#endif