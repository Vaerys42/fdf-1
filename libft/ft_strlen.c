/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 10:56:27 by ycribier          #+#    #+#             */
/*   Updated: 2013/11/22 10:56:39 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlen(char const *str)
{
	size_t	nchar;

	nchar = 0;
	while (str[nchar] != '\0')
		nchar++;
	return (nchar);
}
