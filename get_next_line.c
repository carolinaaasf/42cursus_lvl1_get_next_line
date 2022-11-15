/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 19:21:39 by csilva-f          #+#    #+#             */
/*   Updated: 2022/11/15 23:17:14 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_trim_line(char	*str)
{
	size_t	i;
	char	*line;

	i = 0;
	while (str[i] != '\n' || str[i] != '\0')
		i++;
	line = (char *)malloc(i * sizeof(char) + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		line[i] = str[i];
		i++;
		if (str[i] == '\n')
			break ;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_trim_str(char *str)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*str_new;

	i = 0;
	while (str[i] != '\0' || str[i] != '\n')
		i++;
	len = ft_strlen(str);
	if (len == 0)
	{
		free(str);
		return (NULL);
	}
	str_new = (char *)malloc(sizeof(char) * (len - i + 1));
	if (!str_new)
		return (NULL);
	j = 0;
	while (str[++i] != '\0')
		str_new[j++] = str[i];
	str_new[j] = '\0';
	free(str);
	return (str_new);
}

char	*get_str_from_fd(int fd, char *str)
{
	char		*buf_str;
	size_t		nbr;

	buf_str = (char *)malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!buf_str)
		return (NULL);
	while (!ft_strchr(str, '\n') && nbr != 0)
	{
		nbr = read(fd, buf_str, BUFFER_SIZE);
		if (nbr < 0)
		{
			free(buf_str);
			return (NULL);
		}
		buf_str[nbr] = '\0';
		str = ft_strjoin(str, buf_str);
	}
	if (!str)
		return (NULL);
	free(buf_str);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str;
	size_t		nbr;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	str = get_str_from_fd(fd, str);
	if (!str)
		return (NULL);
	line = ft_trim_line(str);
	str = ft_trim_str(str);
	return (line);
}
