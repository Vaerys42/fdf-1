/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 15:07:58 by ycribier          #+#    #+#             */
/*   Updated: 2013/11/27 17:05:06 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*dst;
	int		i;

	if (s && f)
	{
		dst = ft_strnew(ft_strlen(s));
		i = 0;
		while (s[i] != '\0')
		{
			dst[i] = f(s[i]);
			i++;
		}
		return (dst);
	}
	return (NULL);
}
