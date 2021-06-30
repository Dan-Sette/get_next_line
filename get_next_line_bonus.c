/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalves-s <dalves-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:28:13 by dalves-s          #+#    #+#             */
/*   Updated: 2021/06/30 17:52:19 by dalves-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	line_break(char *line_buf, size_t len)
{
	size_t	i;

	i = 0;
	if (!line_buf)
		return (i);
	while (i < len)
	{
		if (line_buf[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*point;
	char	*set;
	size_t	i;

	i = 0;
	point = malloc(nmemb * size);
	if (!point)
		return (NULL);
	set = (char *)point;
	while (i < size)
	{
		set[i] = 0;
		i++;
	}
	return (point);
}

char	*new_line(char **line, char **line_buf, int *bytes)
{
	int		i;
	char	*aux;
	int		len;

	len = 0;
	i = 0;
	while ((*line_buf)[i] != '\n' && (*line_buf)[i] != '\0')
		i++;
	*line = ft_substr((*line_buf), 0, i);
	if (*bytes)
	{
		if ((*line_buf)[i] == '\n')
			i++;
		len = ft_strlen((char *)((*line_buf) + i));
		aux = ft_substr((*line_buf), i, len);
		if (!aux)
			return (NULL);
	}
	free((*line_buf));
	if (!*line)
		return (NULL);
	return (aux);
}

char	split_line(int fd, char **line_buf, char **buf, int *bytes)
{
	char	*temp;

	while (*bytes && !(line_break(*line_buf, ft_strlen(*line_buf))))
	{
		*bytes = read(fd, *buf, BUFFER_SIZE);
		(*buf)[*bytes] = 0;
		if (*bytes < 0 || *bytes > BUFFER_SIZE)
		{
			free(buf);
			return (0);
		}		
		temp = *line_buf;
		*line_buf = ft_strjoin(temp, *buf);
		free(temp);
	}
	free(*buf);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*line_buf[RLIMIT_NOFILE];
	char		*buf;
	int			bytes;
	int			check;

	bytes = BUFFER_SIZE;
	if ((fd < 0) || !line || (BUFFER_SIZE <= 0) || fd > RLIMIT_NOFILE)
		return (-1);
	if (!line_buf[fd])
		line_buf[fd] = ft_strdup("");
	buf = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	check = split_line(fd, &line_buf[fd], &buf, &bytes);
	if (!check)
		return (-1);
	line_buf[fd] = new_line(line, &line_buf[fd], &bytes);
	if (!bytes)
		return (0);
	return (1);
}
