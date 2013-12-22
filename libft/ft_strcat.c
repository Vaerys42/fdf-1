/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 11:02:16 by ycribier          #+#    #+#             */
/*   Updated: 2013/11/22 11:02:30 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strcat(char *dest, char const *src)
{
	size_t	len;

	len = ft_strlen(dest);
	ft_strcpy(&dest[len], src);
	return (dest);
}
