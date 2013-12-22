/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/17 19:02:51 by ycribier          #+#    #+#             */
/*   Updated: 2013/12/22 22:40:13 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		FDF_H
# define	FDF_H

# define	W_WIDTH		1000
# define	W_HEIGHT	1000

# include "libft.h"

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	void		*img;
}				t_env;

typedef struct	s_img
{
	t_env		*e;
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
	char			is_vtx;
	int				x;
	int				y;
	int				z;
}				t_vertex;

int		set_color(int iter, t_vertex *pt1, t_vertex *pt2);
void	my_pixel_put_to_image(t_img *img, int x, int y, int color);
void	draw_line_2(t_vertex *pt1, t_vertex *pt2, t_img *img);
void	draw_line_1(t_vertex *pt1, t_vertex *pt2, t_img *img);
void	draw_line(t_vertex *pt1, t_vertex *pt2, t_img *img);

void	create_projection(t_img *img, int l, int c, t_vertex (*vtx_tab)[l][c]);
void	convert_to_parallel(int l, int c, t_vertex (*vtx_tab)[l][c]);
void	fill_empty_vtx(int i, int j, int c, t_vertex (*vtx_tab)[][c]);
void	create_vtx_tab(t_list *list, int l, int c, t_vertex (*vtx_tab)[l][c]);
void	manage_vtx_tab(t_env *e, t_list *list, int nb_line, int nb_col);

int		get_ltab_size(char **tab);
void	clean_line(char *line);
void	check_list(t_list *list, int *nb_col);
void	delete_list(t_list **alst);
void	fdf(int fd, t_env *e);

int		expose_hook(t_env *e);
int		key_hook(int keycode, void *param);
t_img	*create_new_image(t_env *e, int width, int height);
int		set_env(t_env *env);

#endif	/* !FDF_H */
