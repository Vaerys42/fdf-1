/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 10:12:15 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/18 12:04:30 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		free_env(t_env *e)
{
	free(e->img);
	free(e->keys);
	free(e->palette);
	free(e);
}

void		set_default_params(t_env *e)
{
	t_color		col1;
	t_color		col2;

	col1 = hex_to_rgb(COL_MAX);
	col2 = hex_to_rgb(COL_MIN);
	e->offset_x = 0;
	e->offset_y = 0;
	e->flags = 0;
	e->flags |= FLG_RECOMPUTE;
	e->palette = gen_gradient_palette(col1, col2, PALETTE_SIZE);
}

t_env		*init_env(void)
{
	t_env	*e;

	if (!(e = malloc(sizeof(t_env))))
		exit(-1);
	if ((e->mlx = mlx_init()) == NULL)
	{
		perror("[MLX]: Connexion to server X failed.");
		exit(-1);
	}
	if (!(e->win = mlx_new_window(e->mlx, W_WIDTH, W_HEIGHT, "-- FdF --")))
	{
		perror("[MLX]: New window creation failed.");
		exit(-1);
	}
	if (!(e->img = create_new_image(e, W_WIDTH, W_HEIGHT)))
		exit(-1);
	if (!(e->keys = init_keys()))
		exit(-1);
	e->max_elev = 1;
	e->vtx_tab.n_col = 0;
	e->vtx_tab.n_line = 0;
	e->vtx_tab.tab = NULL;
	set_default_params(e);
	return (e);
}
