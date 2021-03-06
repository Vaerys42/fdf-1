/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/07 12:19:31 by ycribier          #+#    #+#             */
/*   Updated: 2014/02/19 16:13:41 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "dlist.h"

t_dlist		*dlist_create(void)
{
	t_dlist	*dlist;

	dlist = malloc(sizeof(t_dlist));
	if (!dlist)
	{
		ft_perror(NULL);
		return (NULL);
	}
	dlist->count = 0;
	dlist->first = NULL;
	dlist->last = NULL;
	return (dlist);
}

void		dlist_destroy(t_dlist *dlist)
{
	t_dlist_node		*cur;

	cur = dlist->first;
	while (cur != NULL)
	{
		if (cur->prev)
		{
			free(cur->prev);
		}
		cur = cur->next;
	}
	free(dlist->last);
	free(dlist);
}

void		dlist_clear(t_dlist *dlist)
{
	t_dlist_node		*cur;

	cur = dlist->first;
	while (cur != NULL)
	{
		free(cur->value);
		cur = cur->next;
	}
}

void		dlist_clear_destroy(t_dlist *dlist)
{
	dlist_clear(dlist);
	dlist_destroy(dlist);
}
