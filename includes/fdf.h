/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/17 19:02:51 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/18 18:46:17 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include <mlx.h>
# include </usr/X11R6/include/X11/X.h>
# include </usr/X11R6/include/X11/Xutil.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>

/*
**		tools
*/
# include "color.h"
# include "keys.h"

# define W_WIDTH		600
# define W_HEIGHT		600

# define PALETTE_SIZE	6

# define COL_MAX		0xFF0000
# define COL_MIN		0x0000FF

# define MOVE_STEP		1

enum
{
	FLG_DISPLAY_COLOR = 1 << 0,
	FLG_RECOMPUTE = 1 << 1,
	FLG_MOVING = 1 << 2,
};

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
	t_vertex	***tab;
}				t_vtx_tab;

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	t_img		*img;
	t_keys		*keys;
	int			*palette;
	int			max_elev;
	t_vtx_tab	vtx_tab;
	t_vtx_tab	vtx_proj;
	int			offset_x;
	int			offset_y;
	char		flags;
}				t_env;

/*
**		env.c
*/
void			free_env(t_env *e);
void			set_default_params(t_env *e);
t_env			*init_env(void);

/*
**		parser.c
*/
void			parse_fd(int fd, t_env *e);

/*
**		mlx_handler.c
*/
void			mlx_handler(t_env *e);

/*
**		vtx_tab.c
*/
void			manage_vtx_tab(t_list *list, t_env *e);

/*
**		projection.c
*/
void			recompute(t_env *e);
void			create_projection(t_env *e);
void			convert_to_parallel(t_env *e);

/*
**		draw_line.c
*/
void			draw_palette(int *palette, int size, t_env *e);
void			draw_line(t_vertex *pt1, t_vertex *pt2, t_env *e);

/*
**		img.c
*/
void			clear_img(t_env *e);
t_img			*create_new_image(t_env *e, int width, int height);

/*
**		my_pixel_put_to_image.c
*/
void			my_pixel_put_to_image(t_img *img, int x, int y, int color);

/*
**		hook.c
*/
int				expose_hook(t_env *e);

/*
**		tools.c
*/
int				get_tab_size(char **tab);

#endif
