/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 10:34:16 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/18 10:34:47 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			clear_img(t_env *e)
{
	size_t		x;
	size_t		y;

	y = 0;
	while (y < W_HEIGHT)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			my_pixel_put_to_image(e->img, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

t_img			*create_new_image(t_env *e, int width, int height)
{
	t_img	*img;

	if (!(img = malloc(sizeof(t_img))))
	{
		perror("[MLX]: New image alloc failed.");
		exit(-1);
	}
	if ((img->id = mlx_new_image(e->mlx, width, height)) == NULL)
	{
		perror("[MLX]: New image creation failed.");
		exit(-1);
	}
	img->width = width;
	img->height = height;
	img->addr = mlx_get_data_addr(img->id, &img->bpp,
										&img->lsize, &img->endian);
	return (img);
}
