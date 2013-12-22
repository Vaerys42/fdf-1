/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/16 16:22:33 by ycribier          #+#    #+#             */
/*   Updated: 2013/12/22 22:31:02 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "fdf.h"
#include "libft.h"

int		expose_hook(t_env *e)
{
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (0);
}

int		key_hook(int keycode, void *param)
{
	(void) param;
	if (keycode == 65307)
		exit(0);
	return (0);
}

t_img	*create_new_image(t_env *e, int width, int height)
{
	t_img	*new_img;

	if (!(new_img = malloc(sizeof(t_img))))
	{
		perror("[MLX]: New image alloc failed.");
		exit(-1);
	}
	new_img->e = e;
	if ((new_img->id = mlx_new_image(e->mlx, width, height)) == NULL)
	{
		perror("[MLX]: New image creation failed.");
		exit(-1);
	}
	new_img->width = width;
	new_img->height = height;
	new_img->addr = mlx_get_data_addr(new_img->id, &new_img->bpp,
										&new_img->lsize, &new_img->endian);
	e->img = new_img->id;
	return (new_img);
}

int		set_env(t_env *env)
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

int		main(int argc, char **argv)
{
	t_env	e;
	int		fd;

	if (argc > 1)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
		{
			perror(argv[1]);
			exit(-1);
		}
		set_env(&e);
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
