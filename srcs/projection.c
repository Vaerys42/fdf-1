/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 10:50:20 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/18 10:54:21 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			recompute(t_env *e)
{
	size_t		i;
	size_t		j;

	j = 0;
	while (j < e->vtx_tab.n_line)
	{
		i = 0;
		while (i < e->vtx_tab.n_col)
		{
			if (e->vtx_tab.tab[j][i])
			{
				e->vtx_tab.tab[j][i]->x += e->offset_x;
				e->vtx_tab.tab[j][i]->y += e->offset_y;
			}
			i++;
		}
		j++;
	}
}

void			create_projection(t_env *e)
{
	size_t		i;
	size_t		j;
	t_vertex	***tab;

	tab = e->vtx_tab.tab;
	j = 0;
	while (j < e->vtx_tab.n_line)
	{
		i = 0;
		while (i < e->vtx_tab.n_col)
		{
			if (e->vtx_tab.tab[j][i])
			{
				if (i < e->vtx_tab.n_col - 1 && tab[j][i + 1])
					draw_line(tab[j][i], tab[j][i + 1], e);
				if (j < e->vtx_tab.n_line - 1 && tab[j + 1][i])
					draw_line(tab[j][i], tab[j + 1][i], e);
			}
			i++;
		}
		j++;
	}
}

void			convert_to_parallel(t_env *e)
{
	size_t		i;
	size_t		j;
	size_t		tmp_x;
	size_t		tmp_y;

	j = 0;
	while (j < e->vtx_tab.n_line)
	{
		i = 0;
		while (i < e->vtx_tab.n_col)
		{
			if (e->vtx_tab.tab[j][i])
			{
				tmp_x = -2 * e->vtx_tab.tab[j][i]->y
					+ 2 * e->vtx_tab.tab[j][i]->x;
				tmp_y = 2 * e->vtx_tab.tab[j][i]->y + e->vtx_tab.tab[j][i]->x;
				e->vtx_tab.tab[j][i]->x = (W_WIDTH - e->vtx_tab.n_line * 20) / 2
					+ tmp_x * 10;
				e->vtx_tab.tab[j][i]->y = (W_HEIGHT - e->vtx_tab.n_col * 10) / 2
					+ tmp_y * 10 - 2 * e->vtx_tab.tab[j][i]->z;
			}
			i++;
		}
		j++;
	}
}
