/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/16 16:22:33 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/17 20:09:44 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void			free_env(t_env *e)
{
	free(e->img);
	free(e->keys);
	free(e->palette);
	free(e);
}

static int		key_hook(int keycode, t_env *e)
{
	if (keycode == 65307)
	{
		free_env(e);
		exit(0);
	}
	return (0);
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

static t_env	*init_env(void)
{
	t_env	*e;

	if (!(e = malloc(sizeof(t_env))))
		exit(-1);
	if ((e->mlx = mlx_init()) == NULL)
	{
		perror("[MLX]: Connexion to server X failed.");
		exit(-1);
	}
	if (!(e->win = mlx_new_window(e->mlx, W_WIDTH, W_HEIGHT, "-- FdF --")))
	{
		perror("[MLX]: New window creation failed.");
		exit(-1);
	}
	if (!(e->img = create_new_image(e, W_WIDTH, W_HEIGHT)))
		exit(-1);
	if (!(e->keys = init_keys()))
		exit(-1);
	e->max_elev = 1;
	e->vtx_tab.n_col = 0;
	e->vtx_tab.n_line = 0;
	e->vtx_tab.tab = NULL;
	e->offset_x = 0;
	e->offset_y = 0;
	e->palette = gen_gradient_palette(hex_to_rgb(COL_MAX), hex_to_rgb(COL_MIN), PALETTE_SIZE);
	return (e);
}

int				main(int ac, char *av[])
{
	t_env	*e;
	int		fd;

	if (ac > 1)
	{
		if ((fd = open(av[1], O_RDONLY)) == -1)
		{
			perror(av[1]);
			exit(-1);
		}
		e = init_env();
		parse_fd(fd, e);
		close(fd);
		mlx_handler(e);
	}
	else
		ft_putendl("usage : ./fdf map.fdf");
	return (EXIT_SUCCESS);
}
