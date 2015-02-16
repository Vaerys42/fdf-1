/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtx_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/22 14:48:06 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/16 16:07:11 by ycribier         ###   ########.fr       */
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
void			display_vtx_tab(t_env *e)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (j < e->vtx_tab.n_line)
	{
		i = 0;
		while (i < e->vtx_tab.n_col)
		{
			if (e->vtx_tab.tab[j][i])
				printf("%d ", e->vtx_tab.tab[j][i]->z);
			i++;
		}
		printf("\n");
		j++;
	}
}

static t_vertex	*create_new_vtx(int x, int y, int z)
{
	t_vertex	*new_vtx;

	if ((new_vtx = (t_vertex *)malloc(sizeof(t_vertex))))
	{
		new_vtx->x = x;
		new_vtx->y = y;
		new_vtx->z = z;
	}
	return (new_vtx);
}

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
			e->vtx_tab.tab[j][i] = NULL;
			if (tmp[i])
			{
				e->vtx_tab.tab[j][i] = create_new_vtx(i, j, ft_atoi(tmp[i]));
				e->max_elev = fmax(e->max_elev, ft_abs(ft_atoi(tmp[i])));
			}
			else
				break ;
			i++;
		}
		j++;
		list = list->next;
	}
}

t_vertex		***create_vtx_tab(size_t n_line, size_t n_col)
{
	t_vertex	***tab;
	size_t		j;

	if ((tab = malloc(sizeof(t_vertex *) * n_line)))
	{
		j = 0;
		while (j < n_line)
		{
			if (!(tab[j] = malloc(sizeof(t_vertex *) * n_col)))
				return (NULL);
			j++;
		}
	}
	return (tab);
}

void			manage_vtx_tab(t_list *list, t_env *e)
{
	e->vtx_tab.tab = create_vtx_tab(e->vtx_tab.n_line, e->vtx_tab.n_col);
	if (!e->vtx_tab.tab)
		return ;
	fill_vtx_tab(list, e);
	// display_vtx_tab(e);
	// convert_to_parallel(&vtx_tab);
	// create_projection(e, &vtx_tab);
}
