/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/18 18:48:12 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/11 15:56:01 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		get_ltab_size(char **tab)
{
	int		size;

	size = 0;
	if (tab)
	{
		while (*tab)
		{
			size++;
			tab++;
		}
	}
	return (size);
}

void			clean_line(char *line)
{
	if (line)
	{
		while (*line)
		{
			if (!(*line >= '0' && *line <= '9') && *line != '-' && *line != '+')
				*line = ' ';
			line++;
		}
	}
}

static void		check_list(t_list *list, int *nb_col)
{
	char	*line;
	int		line_size;
	char	**tab;

	while (list)
	{
		line = (char *)(list->content);
		clean_line(line);
		tab = ft_strsplit(line, ' ');
		line_size = get_ltab_size(tab);
		if (line_size > *nb_col)
			*nb_col = line_size;
		list = list->next;
		free(tab);
	}
}

static void		delete_list(t_list **alst)
{
	t_list	*tmp;

	if (alst)
	{
		while ((*alst) != NULL)
		{
			free((*alst)->content);
			tmp = *alst;
			free(*alst);
			*alst = (tmp)->next;
		}
	}
}

void			fdf(int fd, t_env *e)
{
	char	*line;
	t_list	*list;
	t_list	*elem;
	int		nb_col;
	int		nb_line;
	int		ret; //6 var

	line = NULL;
	list = NULL;
	nb_line = 0;
	nb_col = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		elem = ft_lstnew(line, (ft_strlen(line) + 1) * sizeof(char));
		ft_lstpush(&list, elem);
		if (line)
			ft_strdel(&line);
		nb_line++;
	}
	if (ret == -1)
		exit(-1);
	check_list(list, &nb_col);
	manage_vtx_tab(e, list, nb_line, nb_col);
	draw_palette(g_palette, PALETTE_SIZE, e); //
	delete_list(&list);
}
