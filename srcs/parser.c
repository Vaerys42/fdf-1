/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/18 18:48:12 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/16 16:01:24 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			display_list(t_list *list)
{
	while (list)
	{
		printf("%s\n", (char *)(list->content));
		list = list->next;
	}
}

static int		get_tab_size(char **tab)
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

static void		check_list_and_recover_map_sizes(t_list *list, t_env *e)
{
	char	*line;
	int		line_size;
	char	**tab;

	while (list)
	{
		line = (char *)(list->content);
		tab = ft_strsplit(line, ' ');
		line_size = get_tab_size(tab);
		e->vtx_tab.n_col = fmax(line_size, e->vtx_tab.n_col);
		e->vtx_tab.n_line += 1;
		list = list->next;
		free_tab(&tab);
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

t_list			*recover_lines(int fd)
{
	t_list	*list;
	t_list	*elem;
	char	*line;
	int		ret;

	list = NULL;
	line = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		clean_line(line);
		elem = ft_lstnew(line, (ft_strlen(line) + 1) * sizeof(char));
		ft_lstpush(&list, elem);
		if (line)
			ft_strdel(&line);
	}
	if (ret == -1)
		exit(-1);
	return (list);
}

void			parse_fd(int fd, t_env *e)
{
	t_list	*list;

	list = recover_lines(fd);
	if (!list)
	{
		ft_putendl("File empty!");
		exit(-1);
	}
	check_list_and_recover_map_sizes(list, e);
	// display_list(list);
	manage_vtx_tab(list, e);
	delete_list(&list);
}
