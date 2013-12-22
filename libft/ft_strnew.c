/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 11:11:24 by ycribier          #+#    #+#             */
/*   Updated: 2013/11/27 14:31:26 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

char	*ft_strnew(size_t size)
{
	char	*s;

	s = (char *) malloc((size + 1) * sizeof(char));
	if (s)
		ft_memset(s, '\0', size + 1);
	return (s);
}
