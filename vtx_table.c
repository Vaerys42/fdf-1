/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtx_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/22 14:48:06 by ycribier          #+#    #+#             */
/*   Updated: 2013/12/22 20:21:39 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "fdf.h"
#include "libft.h"

void	create_projection(t_img *img, int l, int c, t_vertex (*vtx_tab)[l][c])
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
					draw_line(&(*vtx_tab)[j][i], &(*vtx_tab)[j][i + 1], img);
				if (j < (l - 1) && ((*vtx_tab)[j + 1][i]).is_vtx == 1)
					draw_line(&(*vtx_tab)[j][i], &(*vtx_tab)[j + 1][i], img);
			}
			i++;
		}
		j++;
	}
}

void	convert_to_parallel(int l, int c, t_vertex (*vtx_tab)[l][c])
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

void	fill_empty_vtx(int i, int j, int c, t_vertex (*vtx_tab)[][c])
{
	while (i < c)
	{
		((*vtx_tab)[j][i]).is_vtx = 0;
		i++;
	}
}

void	create_vtx_tab(t_list *list, int l, int c, t_vertex (*vtx_tab)[l][c])
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
			tab++;
			i++;
		}
		fill_empty_vtx(i, j, c, vtx_tab);
		j++;
		list = list->next;
	}
}

void	manage_vtx_tab(t_env e, t_list *list, int nb_line, int nb_col)
{
	t_img		*img;
	t_vertex	vtx_tab[nb_line][nb_col];

	img = create_new_image(&e, W_WIDTH, W_HEIGHT);
	create_vtx_tab(list, nb_line, nb_col, &vtx_tab);
	convert_to_parallel(nb_line, nb_col, &vtx_tab);
	create_projection(img, nb_line, nb_col, &vtx_tab);
	mlx_put_image_to_window(e.mlx, e.win, img->id, 0, 0);
}
