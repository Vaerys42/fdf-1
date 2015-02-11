/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/17 19:02:51 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/11 18:22:58 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define W_WIDTH		1000
# define W_HEIGHT		1000

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

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	t_img		*img;
	int			max_elev;
}				t_env;

typedef struct	s_vertex
{
	char		is_vtx;
	int			x;
	int			y;
	int			z;
}				t_vertex;

void			draw_line(t_vertex *pt1, t_vertex *pt2, t_env *e);
void			manage_vtx_tab(t_env *e, t_list *list, int n_line, int n_col);
void			clean_line(char *line);
void			fdf(int fd, t_env *e);
t_img			*create_new_image(t_env *e, int width, int height);

void	draw_palette(int *palette, int size, t_env *e);


#endif
