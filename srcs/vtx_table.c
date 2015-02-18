/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtx_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/22 14:48:06 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/18 20:28:54 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_vertex		*create_new_vtx(int x, int y, int z)
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

static int			get_max_elev(t_env *e)
{
	size_t		i;
	size_t		j;
	int			max_elev;

	max_elev = 1;
	j = 0;
	while (j < e->vtx_tab.n_line)
	{
		i = 0;
		while (i < e->vtx_tab.n_col)
		{
			if (e->vtx_tab.tab[j][i])
				max_elev = fmax(max_elev, e->vtx_tab.tab[j][i]->z);
			i++;
		}
		j++;
	}
	return (max_elev);
}

static void			fill_vtx_tab(t_list *list, t_env *e)
{
	char		**tmp;
	size_t		i;
	size_t		j;

	j = 0;
	while (list && j < e->vtx_tab.n_line)
	{
		i = 0;
		tmp = ft_strsplit((char *)(list->content), ' ');
		while (tmp[i] && i < e->vtx_tab.n_col)
		{
			if (tmp[i])
				e->vtx_tab.tab[j][i] = create_new_vtx(i, j, ft_atoi(tmp[i]));
			i++;
		}
		j++;
		list = list->next;
		free_tab(&tmp);
	}
}

static t_vertex		***create_vtx_tab(size_t n_line, size_t n_col)
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
			ft_bzero(tab[j], sizeof(t_vertex *) * n_col);
			j++;
		}
	}
	return (tab);
}

void				manage_vtx_tab(t_list *list, t_env *e)
{
	e->vtx_tab.tab = create_vtx_tab(e->vtx_tab.n_line, e->vtx_tab.n_col);
	if (!e->vtx_tab.tab)
		return ;
	fill_vtx_tab(list, e);
	e->max_elev = get_max_elev(e);
	convert_to_parallel(e);
}
