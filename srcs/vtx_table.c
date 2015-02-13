/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtx_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/22 14:48:06 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/13 19:42:12 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*static void
	create_projection(t_env *e, t_vertex (*vtx_tab)[l][c])
{
	int			i;
	int			j;

	j = 0;
	while (j < e->vtx_tab.n_line)
	{
		i = 0;
		while (i < e->vtx_tab.n_col)
		{
			if (((*vtx_tab)[j][i]).is_vtx == 1)
			{
				if (i < (e->vtx_tab.n_col - 1) && ((*vtx_tab)[j][i + 1]).is_vtx == 1)
					draw_line(&(*vtx_tab)[j][i], &(*vtx_tab)[j][i + 1], e);
				if (j < (e->vtx_tab.n_line - 1) && ((*vtx_tab)[j + 1][i]).is_vtx == 1)
					draw_line(&(*vtx_tab)[j][i], &(*vtx_tab)[j + 1][i], e);
			}
			i++;
		}
		j++;
	}
}

static void
	convert_to_parallel(t_vertex (*vtx_tab)[l][c])
{
	int		i;
	int		j;
	int		tmp_x;
	int		tmp_y;

	j = 0;
	while (j < e->vtx_tab.n_line)
	{
		i = 0;
		while (i < e->vtx_tab.n_col)
		{
			if (((*vtx_tab)[j][i]).is_vtx == 1)
			{
				tmp_x = -2 * ((*vtx_tab)[j][i]).y + 2 * ((*vtx_tab)[j][i]).x;
				tmp_y = 2 * ((*vtx_tab)[j][i]).y + ((*vtx_tab)[j][i]).x;
				((*vtx_tab)[j][i]).x = (W_WIDTH - e->vtx_tab.n_line * 20) / 2
									+ tmp_x * 10;
				((*vtx_tab)[j][i]).y = (W_HEIGHT - e->vtx_tab.n_col * 10) / 2
									+ tmp_y * 10 - 2 * ((*vtx_tab)[j][i]).z;
			}
			i++;
		}
		j++;
	}
}
*/
// static void
// 	fill_empty_vtx(int i, int j, int c, t_vertex (*vtx_tab)[][c])
// {
// 	while (i < c)
// 	{
// 		((*vtx_tab)[j][i]).is_vtx = 0;
// 		i++;
// 	}
// }

static void		fill_vtx_tab(t_list *list, t_env *e)
{
	char		**tmp;
	size_t		i;
	size_t		j;

	j = 0;
	while (list && j < e->vtx_tab.n_line)
	{
		i = 0;
		tmp = ft_strsplit((char *)(list->content), ' ');
		while (i < e->vtx_tab.n_col)
		{
			if (tmp[i])
			{
				e->vtx_tab.tab[j][i] = (t_vertex *)malloc(sizeof(t_vertex));
				e->vtx_tab.tab[j][i]->x = i;
				e->vtx_tab.tab[j][i]->y = j;
				e->vtx_tab.tab[j][i]->z = ft_atoi(tmp[i]);
				e->max_elev = fmax(e->max_elev, ft_abs(e->vtx_tab.tab[j][i]->z));
			}
			else
				e->vtx_tab.tab[j][i] = NULL;
			i++;
		}
		j++;
		list = list->next;
	}
}

t_vertex	**create_vtx_tab(size_t n_line, size_t n_col)
{
	t_vertex	**tab;
	size_t		i;

	if ((tab = malloc(sizeof(t_vertex *) * n_line)))
	{
		i = 0;
		while (i < n_line)
		{
			if (!(tab[i] = (t_vertex *)malloc(sizeof(t_vertex *) * n_col)))
				return (NULL);
			i++;
		}
	}
	return (tab);
}

void		manage_vtx_tab(t_list *list, t_env *e)
{
	e->vtx_tab.tab = create_vtx_tab(e->vtx_tab.n_line, e->vtx_tab.n_col);
	if (!e->vtx_tab.tab)
		return ;
	fill_vtx_tab(list, e);
	// convert_to_parallel(&vtx_tab);
	// create_projection(e, &vtx_tab);
}
