/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/18 16:24:38 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/18 11:52:37 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		set_color(double percent, t_vertex *pt1, t_vertex *pt2, t_env *e)
{
	double	offset;
	int		index;

	int _abs = pt2->z - pt1->z;
	offset = percent * _abs;
	index = (int)((PALETTE_SIZE / 2)
		- (((double)pt1->z + offset) / (e->max_elev + 1)) * PALETTE_SIZE / 2);
	return (e->palette[index]);
}

void			draw_palette(int *palette, int size, t_env *e)
{
	int	x;
	int	y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < 20)
		{
			my_pixel_put_to_image(e->img, x, y, palette[y]);
			x++;
		}
		y++;
	}
}

static void		draw_line_1(t_vertex *pt1, t_vertex *pt2, t_env *e)
{
	int	x;
	int	y;
	int	color;

	x = pt1->x;
	while (x <= pt2->x)
	{
		color = set_color((double)(x - pt1->x) / (pt2->x - pt1->x), pt1, pt2, e);
		y = pt1->y + ((pt2->y - pt1->y) * (x - pt1->x)) / (pt2->x - pt1->x);
		my_pixel_put_to_image(e->img, x, y, color);
		x++;
	}
}

static void		draw_line_2(t_vertex *pt1, t_vertex *pt2, t_env *e)
{
	int	x;
	int	y;
	int	color;

	y = pt1->y;
	if (pt1->x == pt2->x && pt1->y == pt2->y)
	{
		color = set_color(0, pt1, pt2, e);
		my_pixel_put_to_image(e->img, pt1->x, pt1->y, color);
		return ;
	}
	while (y <= pt2->y)
	{
		color = set_color((double)(y - pt1->y) / (pt2->y - pt1->y), pt1, pt2, e);
		x = pt1->x + ((pt2->x - pt1->x) * (y - pt1->y)) / (pt2->y - pt1->y);
		my_pixel_put_to_image(e->img, x, y, color);
		y++;
	}
}

void			draw_line(t_vertex *pt1, t_vertex *pt2, t_env *e)
{
	int		delta_x;
	int		delta_y;

	delta_x = ft_abs(pt1->x - pt2->x);
	delta_y = ft_abs(pt1->y - pt2->y);
	if (delta_x > delta_y)
	{
		if (pt1->x < pt2->x)
			draw_line_1(pt1, pt2, e);
		else
			draw_line_1(pt2, pt1, e);
	}
	else
	{
		if (pt1->y < pt2->y)
			draw_line_2(pt1, pt2, e);
		else
			draw_line_2(pt2, pt1, e);
	}
}
