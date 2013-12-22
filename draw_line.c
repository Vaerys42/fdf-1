/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/18 16:24:38 by ycribier          #+#    #+#             */
/*   Updated: 2013/12/22 22:28:01 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "fdf.h"
#include "libft.h"

int		set_color(int iter, t_vertex *pt1, t_vertex *pt2)
{
	int	color;

	(void) iter;
	if (pt1->z > 0 && pt1->z == pt2->z)
		color = 0xFF8200;
	else
		color = 0x2282F5;
	return (color);
}

void	my_pixel_put_to_image(t_img *img, int x, int y, int color)
{
	int				i;
	int				mask;
	char			tmp_clr;
	int				offset;

	i = 0;
	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		while (i < (img->bpp / 8))
		{
			if (img->endian == 1)
				offset = img->bpp - 8 * (i + 1);
			else
				offset = 8 * i;
			mask = 0xFF << offset;
			tmp_clr = (color & mask) >> offset;
			img->addr[y * (img->lsize) + x * (img->bpp / 8) + i] = tmp_clr;
			i++;
		}
	}
}

void	draw_line_1(t_vertex *pt1, t_vertex *pt2, t_img *img)
{
	int	x;
	int	y;
	int	color;

	x = pt1->x;
	while (x <= pt2->x)
	{
		color = set_color((pt2->x - x), pt1, pt2);
		y = pt1->y + ((pt2->y - pt1->y) * (x - pt1->x)) / (pt2->x - pt1->x);
		my_pixel_put_to_image(img, x, y, color);
		x++;
	}
}

void	draw_line_2(t_vertex *pt1, t_vertex *pt2, t_img *img)
{
	int	x;
	int	y;
	int	color;

	y = pt1->y;
	if (pt1->x == pt2->x && pt1->y == pt2->y)
	{
		color = set_color(0, pt1, pt2);
		my_pixel_put_to_image(img, pt1->x, pt1->y, color);
		return ;
	}
	while (y <= pt2->y)
	{
		color = set_color((pt2->y - y), pt1, pt2);
		x = pt1->x + ((pt2->x - pt1->x) * (y - pt1->y)) / (pt2->y - pt1->y);
		my_pixel_put_to_image(img, x, y, color);
		y++;
	}
}

void	draw_line(t_vertex *pt1, t_vertex *pt2, t_img *img)
{
	if ((ft_abs(pt1->x - pt2->x) > ft_abs(pt1->y - pt2->y)))
	{
		if (pt1->x < pt2->x)
			draw_line_1(pt1, pt2, img);
		else
			draw_line_1(pt2, pt1, img);
	}
	else
	{
		if (pt1->y < pt2->y)
			draw_line_2(pt1, pt2, img);
		else
			draw_line_2(pt2, pt1, img);
	}
}
