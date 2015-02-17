/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/09 17:52:18 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/17 20:17:35 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		recompute(t_env *e)
{
	size_t		i;
	size_t		j;

	j = 0;
	while (j < e->vtx_tab.n_line)
	{
		i = 0;
		while (i < e->vtx_tab.n_col)
		{
			if (e->vtx_proj.tab[j][i])
			{
				e->vtx_proj.tab[j][i]->x += e->offset_x;
				e->vtx_proj.tab[j][i]->y += e->offset_y;
			}
			i++;
		}
		j++;
	}
}

int			key_release(int keycode, t_env *e)
{
	if (keycode == KEY_ESC)
	{
		free_env(e);
		exit(0);
	}
	if (keycode == KEY_RIGHT)
		e->keys->right = FALSE;
	if (keycode == KEY_LEFT)
		e->keys->left = FALSE;
	if (keycode == KEY_UP)
		e->keys->up = FALSE;
	if (keycode == KEY_DOWN)
		e->keys->down = FALSE;
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
		e->offset_y += MOVE_STEP;
		recompute(e);
	}
	if (e->keys->down == TRUE)
	{
		e->offset_y -= MOVE_STEP;
		recompute(e);
	}
	if (e->keys->right == TRUE)
	{
		e->offset_x += MOVE_STEP;
		recompute(e);
	}
	if (e->keys->left == TRUE)
	{
		e->offset_x -= MOVE_STEP;
		recompute(e);
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
