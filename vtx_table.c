/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtx_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/22 14:48:06 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/13 17:00:17 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void
	create_projection(t_env *e, int l, int c, t_vertex (*vtx_tab)[l][c])
{
	int			i;
	int			j;

	j = 0;
	while (j < l)
	{
		i = 0;
		while (i < c)
		{
			if (((*vtx_tab)[j][i]).is_vtx == 1)
			{
				if (i < (c - 1) && ((*vtx_tab)[j][i + 1]).is_vtx == 1)
					draw_line(&(*vtx_tab)[j][i], &(*vtx_tab)[j][i + 1], e);
				if (j < (l - 1) && ((*vtx_tab)[j + 1][i]).is_vtx == 1)
					draw_line(&(*vtx_tab)[j][i], &(*vtx_tab)[j + 1][i], e);
			}
			i++;
		}
		j++;
	}
}

static void
	convert_to_parallel(int l, int c, t_vertex (*vtx_tab)[l][c])
{
	int		i;
	int		j;
	int		tmp_x;
	int		tmp_y;

	j = 0;
	while (j < l)
	{
		i = 0;
		while (i < c)
		{
			if (((*vtx_tab)[j][i]).is_vtx == 1)
			{
				tmp_x = -2 * ((*vtx_tab)[j][i]).y + 2 * ((*vtx_tab)[j][i]).x;
				tmp_y = 2 * ((*vtx_tab)[j][i]).y + ((*vtx_tab)[j][i]).x;
				((*vtx_tab)[j][i]).x = (W_WIDTH - l * 20) / 2 + tmp_x * 10;
				((*vtx_tab)[j][i]).y = (W_HEIGHT - c * 10) / 2 + tmp_y * 10
										- 2 * ((*vtx_tab)[j][i]).z;
			}
			i++;
		}
		j++;
	}
}

static void
	fill_empty_vtx(int i, int j, int c, t_vertex (*vtx_tab)[][c])
{
	while (i < c)
	{
		((*vtx_tab)[j][i]).is_vtx = 0;
		i++;
	}
}

static void
	create_vtx_tab(t_list *list, int l, int c, t_vertex (*vtx_tab)[l][c], t_env *e)
{
	char		*line;
	char		**tab;
	int			i;
	int			j;

	j = 0;
	while (list && j < l)
	{
		i = 0;
		line = list->content;
		clean_line(line);
		tab = ft_strsplit(line, ' ');
		while (*tab)
		{
			((*vtx_tab)[j][i]).is_vtx = 1;
			((*vtx_tab)[j][i]).x = i;
			((*vtx_tab)[j][i]).y = j;
			((*vtx_tab)[j][i]).z = ft_atoi(*tab);
			e->max_elev = fmax(e->max_elev, ft_abs(((*vtx_tab)[j][i]).z));
			tab++;
			i++;
		}
		fill_empty_vtx(i, j, c, vtx_tab);
		j++;
		list = list->next;
	}
}

void
	manage_vtx_tab(t_env *e, t_list *list, int nb_line, int nb_col)
{
	t_vertex	vtx_tab[nb_line][nb_col];

	e->img = create_new_image(e, W_WIDTH, W_HEIGHT);
	create_vtx_tab(list, nb_line, nb_col, &vtx_tab, e);
	convert_to_parallel(nb_line, nb_col, &vtx_tab);
	create_projection(e, nb_line, nb_col, &vtx_tab);
}
