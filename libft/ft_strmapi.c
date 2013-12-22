/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 15:25:35 by ycribier          #+#    #+#             */
/*   Updated: 2013/11/27 14:57:09 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*dst;
	int		i;

	if (s && f)
	{
		dst = ft_strnew(ft_strlen(s));
		i = 0;
		while (s[i] != '\0')
		{
			dst[i] = f(i, s[i]);
			i++;
		}
		return (dst);
	}
	return (NULL);
}
