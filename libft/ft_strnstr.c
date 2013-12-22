/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/26 17:07:54 by ycribier          #+#    #+#             */
/*   Updated: 2013/11/26 19:00:19 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strnstr(char const *str, char const *to_find, size_t n)
{
	size_t	len;

	if (*to_find == '\0')
		return ((char *) str);
	len = ft_strlen(to_find);
	while (*str != '\0' && n >= len)
	{
		if (ft_strncmp(str, to_find, len) == 0)
			return ((char *) str);
		str++;
		n--;
	}
	return (NULL);
}