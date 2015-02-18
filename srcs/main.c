/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/16 16:22:33 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/18 10:34:23 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
