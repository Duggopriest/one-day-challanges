
#ifndef PATHING_H
# define PATHING_H

# include "mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <time.h>

typedef struct s_render {
	int			map_size;
	int			steps;
	int			amount_coins;
	int			amount_goals;

	int			scanned_coins;
	int			scanned_goals;

	char 		**map;
	int			map_h;
	int			map_w;

	int			win_h;
	int			win_w;
	void		*mlx;
	void		*mlx_win;

	void		*wall;
	void		*ground;
	void		*coin;
	void		*goal;
	void		*scanner;
	void		*scanned;
	void		*player;

}	t_render;

char	*get_next_line(int fd);
int		ft_strlen(char *str);
void	draw_map(t_render *r);
void	set_up_grid(t_render *r, char *path);
void	grab_textures(t_render *r);
int		step(t_render *r);
void	replace(char target, char replacement, t_render *r);
void	randomized_map(int map_size, t_render *r);
void	randomized_set_map(int map_size, t_render *r);
int		run_algo(t_render *r);
void	loop_map(t_render *r);
void	reset_map(t_render *r);

#endif