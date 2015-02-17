/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtx_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/22 14:48:06 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/17 20:18:59 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			create_projection(t_env *e)
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
				if (i < e->vtx_proj.n_col - 1 && e->vtx_proj.tab[j][i + 1])
					draw_line(e->vtx_proj.tab[j][i], e->vtx_proj.tab[j][i + 1], e);
				if (j < e->vtx_proj.n_line - 1 && e->vtx_proj.tab[j + 1][i])
					draw_line(e->vtx_proj.tab[j][i], e->vtx_proj.tab[j + 1][i], e);
			}
			i++;
		}
		j++;
	}
}

static void		convert_to_parallel(t_env *e)
{
	size_t		i;
	size_t		j;
	size_t		tmp_x;
	size_t		tmp_y;
	t_vertex	*vtx;

	j = 0;
	while (j < e->vtx_tab.n_line)
	{
		i = 0;
		while (i < e->vtx_tab.n_col)
		{
			vtx = e->vtx_tab.tab[j][i];
			if (vtx)
			{
				tmp_x = -2 * vtx->y + 2 * vtx->x;
				tmp_y = 2 * vtx->y + vtx->x;
				e->vtx_proj.tab[j][i]->x = (W_WIDTH - e->vtx_tab.n_line * 20) / 2 + tmp_x * 10;
				e->vtx_proj.tab[j][i]->y = (W_HEIGHT - e->vtx_tab.n_col * 10) / 2 + tmp_y * 10 - 2 * vtx->z;
			}
			i++;
		}
		j++;
	}
}

void			display_vtx_tab(t_vertex ***tab, t_env *e) //
{
	size_t	i;
	size_t	j;

	j = 0;
	while (j < e->vtx_tab.n_line)
	{
		i = 0;
		while (i < e->vtx_tab.n_col)
		{
			if (tab[j][i])
				printf("%d ", tab[j][i]->z);
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

int				get_max_elev(t_env *e)
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
		while (tmp[i] && i < e->vtx_tab.n_col)
		{
			if (tmp[i])
				e->vtx_tab.tab[j][i] = create_new_vtx(i, j, ft_atoi(tmp[i]));
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

	// printf("l: %zu, :c %zu\n", n_line, n_col);
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

void			dup_vtx_tab(t_vertex ***dest, t_vertex ***src, t_env *e)
{
	size_t		i;
	size_t		j;

	j = 0;
	while (j < e->vtx_tab.n_line)
	{
		i = 0;
		while (i < e->vtx_tab.n_col)
		{
			if (src[j][i])
			{
				dest[j][i] = create_new_vtx(
					src[j][i]->x,
					src[j][i]->y,
					src[j][i]->z
				);
			}
			i++;
		}
		j++;
	}
}

void			manage_vtx_tab(t_list *list, t_env *e)
{
	e->vtx_tab.tab = create_vtx_tab(e->vtx_tab.n_line, e->vtx_tab.n_col);
	if (!e->vtx_tab.tab)
		return ;
	fill_vtx_tab(list, e);
	e->max_elev = get_max_elev(e);
	e->vtx_proj.tab = create_vtx_tab(e->vtx_tab.n_line, e->vtx_tab.n_col);
	if (!e->vtx_proj.tab)
		return ;
	e->vtx_proj.n_line = e->vtx_tab.n_line;
	e->vtx_proj.n_col = e->vtx_tab.n_col;
	dup_vtx_tab(e->vtx_proj.tab, e->vtx_tab.tab, e);
	display_vtx_tab(e->vtx_proj.tab, e);
	convert_to_parallel(e);
	// create_projection(e);
}
