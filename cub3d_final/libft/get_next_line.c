/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 12:54:00 by cquiana           #+#    #+#             */
/*   Updated: 2020/11/07 00:52:10 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*check_tail(char **tail, char **line)
{
	char *ptr_nl;

	ptr_nl = NULL;
	if (*tail)
	{
		if ((ptr_nl = ft_strchr(*tail, '\n')))
		{
			*ptr_nl = '\0';
			*line = ft_strdup(*tail);
			ft_strcpy(*tail, ++ptr_nl);
		}
		else
		{
			*line = ft_strdup(*tail);
			free(*tail);
			*tail = NULL;
		}
	}
	else
		*line = ft_strdup("");
	return (ptr_nl);
}

int		get_next_line(int fd, char **line)
{
	static char		*tail;
	char			buf[BUFFER_SIZE + 1];
	char			*ptr_nl;
	char			*tmp;
	int				byte;

	if (fd < 0 || BUFFER_SIZE < 1 || !line || read(fd, buf, 0) < 0)
		return (-1);
	ptr_nl = check_tail(&tail, line);
	while (!ptr_nl && (byte = read(fd, buf, BUFFER_SIZE)))
	{
		buf[byte] = '\0';
		if ((ptr_nl = ft_strchr(buf, '\n')))
		{
			*ptr_nl = '\0';
			free(tail);
			tail = ft_strdup(++ptr_nl);
		}
		tmp = *line;
		*line = ft_strjoin(*line, buf);
		free(tmp);
	}
	return (!byte && !ptr_nl) ? 0 : 1;
}
