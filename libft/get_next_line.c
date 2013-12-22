/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 12:13:11 by ckleines          #+#    #+#             */
/*   Updated: 2013/12/18 20:16:56 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

static int			gnl_helper(char *buffer, int fd, char **line);
static char			*gnl_join(char *s1, char *s2, int s2len);
static size_t		gnl_len(const char *s);
static int			gnl_read_from_buffer(char *buffer, char **line);

/*
** Check the length of the current string from the start to the
** first occurence of '\n'.
*/
static size_t		gnl_len(const char *s)
{
	size_t		len;

	if (!s)
		return (0);
	len = 0;
	while (s[len] != GNL_TERMINATOR && s[len])
		++len;
	return (len);
}

/*
** Create a new string that contains only the parts before the
** first occurence of '\n' in s1 and s2.
**
** Since s2len is calculated in `gnl_helper`, it is passed as
** an argument to avoid recalculating it.
*/
static char			*gnl_join(char *s1, char *s2, int s2len)
{
	char	*ns;
	char	*orig_ns;

	orig_ns = ns = malloc(gnl_len(s1) + s2len + 1);
	if (s1)
		while (*s1 != GNL_TERMINATOR && *s1)
			*(ns++) = *(s1++);
	if (s2)
		while (*s2 != GNL_TERMINATOR && *s2)
			*(ns++) = *(s2++);
	*ns = '\0';
	return (orig_ns);
}

static int			gnl_read_from_buffer(char *buffer, char **line)
{
	char		*old;
	int			i;

	old = *line;
	i = gnl_len(buffer);
	*line = gnl_join(*line, buffer, i);
	free(old);
	if (buffer[i] == GNL_TERMINATOR && i < GNL_BUFFER_SIZE - 1)
	{
		ft_memcpy(buffer, buffer + i + 1, GNL_BUFFER_SIZE - i - 1);
		buffer[GNL_BUFFER_SIZE - i - 1] = '\0';
		return (GNL_STATUS_READ);
	}
	return (0);
}

/*
** There are three parts to this function:
**
** - The first checks if the buffer is empty. If it isn't, what's left is
** added to the resulting string. If we find a newline, we'll stop here
** but move what's left in the buffer to  it's beginning so we can
** correctly concatenate it on the next call to `get_next_line`.
**
** - The second does the same as described above in a loop until it finds
** a newline.
*/
static int			gnl_helper(char *buffer, int fd, char **line)
{
	int		ret;

	if (buffer[0] && gnl_read_from_buffer(buffer, line) == GNL_STATUS_READ)
			return (GNL_STATUS_READ);
	while ((ret = read(fd, buffer, GNL_BUFFER_SIZE - 1)) > 0)
	{
		buffer[ret] = '\0';
		if (gnl_read_from_buffer(buffer, line) == GNL_STATUS_READ)
			return (GNL_STATUS_READ);
	}
	if (ret == -1)
		return (GNL_STATUS_ERROR);
	if (!*line)
		return (GNL_STATUS_END);
	if (*line)
	{
		if (ret == 0)
			buffer[0] = '\0';
		return (GNL_STATUS_READ);
	}
	return (0);
}

int				get_next_line(int const fd, char **line)
{
	static char		*buffer;
	int				ret;

	if (GNL_BUFFER_SIZE < 2 || fd < 0 || !line)
		return (-1);
	if (!buffer)
	{
		buffer = malloc(GNL_BUFFER_SIZE);
		buffer[0] = buffer[GNL_BUFFER_SIZE - 1] = '\0';
	}
	*line = NULL;
	ret = gnl_helper(buffer, fd, line);
	return (ret);
}
