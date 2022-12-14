#include "../includes/headder.h"

void	run_threads(t_render *r)
{
	int i;

	while (1)
	{
		i = -1;
		while (++i < r->dot_num)
			sim_dot(&r->dots[i], r);
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
