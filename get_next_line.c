/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlucka <mlucka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 13:16:41 by mlucka            #+#    #+#             */
/*   Updated: 2026/06/29 13:34:58 by mlucka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*helper1(char *buffer, char *stash)
{
	free(buffer);
	buffer = NULL;
	free(stash);
	stash = NULL;
	return (NULL);
}

char	*helper2(char *stash)
{
	free(stash);
	stash = NULL;
	return (NULL);
}

static char	*read_file(int fd, char *stash)
{
	char	*buffer;
	int		bytes;
	char	*temp;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(stash, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (helper1(buffer, stash));
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		temp = ft_strjoin(stash, buffer);
		if (!temp)
			return (helper1(buffer, stash));
		free(stash);
		stash = temp;
	}
	free(buffer);
	return (stash);
}

static char	*clean_stash(char *stash)
{
	int		i;
	int		j;
	char	*new_stash;

	i = 0;
	j = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (helper2(stash));
	i++;
	new_stash = malloc(sizeof(char) * (ft_strlen(&stash[i]) + 1));
	if (!new_stash)
		return (helper2(stash));
	while (stash[i])
	{
		new_stash[j++] = stash[i++];
	}
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_file(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = clean_stash(stash);
	return (line);
}
