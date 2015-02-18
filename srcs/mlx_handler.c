/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/09 17:52:18 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/18 11:42:18 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	loop_hook(t_env *e)
{
	manage_keys(e);
	if (e->flags & FLG_RECOMPUTE)
	{
		recompute(e);
		mlx_destroy_image(e->mlx, e->img->id);
		if (!(e->img->id = mlx_new_image(e->mlx, W_WIDTH, W_HEIGHT)))
			exit(-1);
		create_projection(e);
		e->flags &= ~(FLG_RECOMPUTE);
		e->offset_x = 0;
		e->offset_y = 0;
	}
	if (e->flags & FLG_DISPLAY_COLOR)
		draw_palette(e->palette, PALETTE_SIZE, e);
	mlx_put_image_to_window(e->mlx, e->win, e->img->id, 0, 0);
	return (0);
}

void		mlx_handler(t_env *e)
{
	mlx_expose_hook(e->win, &expose_hook, e);
	// mlx_mouse_hook(e->win, &mouse_hook, e);
	mlx_hook(e->win, KeyPress, KeyPressMask, &key_press, e);
	mlx_hook(e->win, KeyRelease, KeyReleaseMask, &key_release, e);
	// mlx_hook(e->win, MotionNotify, PointerMotionMask, &pointer_motion_hook, e);
	mlx_loop_hook(e->mlx, &loop_hook, e);
	mlx_loop(e->mlx);
}
