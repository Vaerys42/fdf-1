/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/09 17:52:18 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/18 11:54:45 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			key_release(int keycode, t_env *e)
{
	if (keycode == KEY_RIGHT)
		e->keys->right = FALSE;
	if (keycode == KEY_LEFT)
		e->keys->left = FALSE;
	if (keycode == KEY_UP)
		e->keys->up = FALSE;
	if (keycode == KEY_DOWN)
		e->keys->down = FALSE;
	if (keycode == KEY_ESC)
	{
		free_env(e);
		exit(0);
	}
	if (keycode == KEY_C)
	{
		e->flags ^= FLG_DISPLAY_COLOR;
		e->flags |= FLG_RECOMPUTE;
	}
	return (0);
}

int			key_press(int keycode, t_env *e)
{
	if (keycode == KEY_RIGHT)
		e->keys->right = TRUE;
	if (keycode == KEY_LEFT)
		e->keys->left = TRUE;
	if (keycode == KEY_UP)
		e->keys->up = TRUE;
	if (keycode == KEY_DOWN)
		e->keys->down = TRUE;
	return (0);
}

void		manage_keys(t_env *e)
{
	if (e->keys->up == TRUE)
	{
		e->offset_y -= MOVE_STEP;
		e->flags |= FLG_RECOMPUTE;
	}
	if (e->keys->down == TRUE)
	{
		e->offset_y += MOVE_STEP;
		e->flags |= FLG_RECOMPUTE;
	}
	if (e->keys->right == TRUE)
	{
		e->offset_x += MOVE_STEP;
		e->flags |= FLG_RECOMPUTE;
	}
	if (e->keys->left == TRUE)
	{
		e->offset_x -= MOVE_STEP;
		e->flags |= FLG_RECOMPUTE;
	}
}

t_keys		*init_keys(void)
{
	t_keys		*keys;

	keys = malloc(sizeof(keys));
	if (keys == NULL)
		exit(EXIT_FAILURE);
	keys->up = FALSE;
	keys->down = FALSE;
	keys->right = FALSE;
	keys->left = FALSE;
	return (keys);
}
