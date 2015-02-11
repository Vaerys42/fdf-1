/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/16 16:22:33 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/11 18:10:45 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		expose_hook(t_env *e)
{
	mlx_put_image_to_window(e->mlx, e->win, e->img->id, 0, 0);
	return (0);
}

static int		key_hook(int keycode, void *param)
{
	(void)param;
	if (keycode == 65307)
		exit(0);
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

static int		set_env(t_env *env)
{
	if ((env->mlx = mlx_init()) == NULL)
	{
		perror("[MLX]: Connexion to server X failed.");
		exit(-1);
	}
	if (!(env->win = mlx_new_window(env->mlx, W_WIDTH, W_HEIGHT, "-- FdF --")))
	{
		perror("[MLX]: New window creation failed.");
		exit(-1);
	}
	return (EXIT_SUCCESS);
}

extern int	*g_palette;

int				main(int argc, char **argv)
{
	t_env	e;
	int		fd;

	g_palette = gen_gradient_palette(hex_to_rgb(COL_RED), hex_to_rgb(COL_BLUE), PALETTE_SIZE);
	if (argc > 1)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
		{
			perror(argv[1]);
			exit(-1);
		}
		set_env(&e);
		e.max_elev = 1;
		fdf(fd, &e);
		mlx_expose_hook(e.win, expose_hook, &e);
		mlx_key_hook(e.win, key_hook, NULL);
		mlx_loop(e.mlx);
		close(fd);
	}
	else
		ft_putendl("usage : ./fdf file1");
	return (EXIT_SUCCESS);
}
