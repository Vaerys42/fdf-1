/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/17 19:02:51 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/13 19:21:48 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define W_WIDTH		1000
# define W_HEIGHT		1000

# define COL_MAX		0xFF0000
# define COL_MIN		0x0000FF

# define PALETTE_SIZE	360

# include <mlx.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include "libft.h"
# include "color.h"

# define KEY_SPACE		32

typedef struct	s_img
{
	void		*id;
	int			width;
	int			height;
	char		*addr;
	int			bpp;
	int			lsize;
	int			endian;
}				t_img;

typedef struct	s_vertex
{
	int			x;
	int			y;
	int			z;
}				t_vertex;

typedef struct	s_vtx_tab
{
	size_t		n_col;
	size_t		n_line;
	t_vertex	**tab;
}				t_vtx_tab;

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	t_img		*img;
	int			*palette;
	int			max_elev;
	t_vtx_tab	vtx_tab;
}				t_env;

void			draw_line(t_vertex *pt1, t_vertex *pt2, t_env *e);
void			clean_line(char *line);
void			parse_fd(int fd, t_env *e);
t_img			*create_new_image(t_env *e, int width, int height);

void			manage_vtx_tab(t_list *list, t_env *e);

void	draw_palette(int *palette, int size, t_env *e);

#endif
