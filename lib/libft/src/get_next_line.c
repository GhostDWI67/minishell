/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:31:25 by dwianni           #+#    #+#             */
/*   Updated: 2024/12/13 16:10:49 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strndup(char const *src, int first, int last)
{
	char	*dest;
	int		i;

	dest = (char *) malloc(sizeof(char) * (last - first + 2));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (i < (last - first + 1))
	{
		dest[i] = src[first + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static void	ft_free(char **s1, char **s2, char **s3)
{
	if (s1 != NULL && *s1 != NULL)
	{
		free(*s1);
		*s1 = NULL;
	}
	if (s2 != NULL && *s2 != NULL)
	{
		free(*s2);
		*s2 = NULL;
	}
	if (s3 != NULL && *s3 != NULL)
	{
		free(*s3);
		*s3 = NULL;
	}
}

static char	*ft_read_buffer(int fd, char *buffer)
{
	char	*read_buffer;
	char	*s1;
	char	*tmp;
	ssize_t	nb_read;

	read_buffer = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	s1 = ft_strndup(buffer, 0, BUFFER_SIZE + 1);
	if (read_buffer == NULL || s1 == NULL)
		return (ft_free(&s1, &read_buffer, 0), NULL);
	nb_read = 1;
	while (ft_strchr(s1, '\n') == NULL && nb_read != 0)
	{
		nb_read = read (fd, read_buffer, BUFFER_SIZE);
		if (nb_read == -1)
			return (ft_free(&s1, &read_buffer, 0), NULL);
		read_buffer[nb_read] = '\0';
		tmp = s1;
		s1 = ft_strjoin(tmp, read_buffer);
		if (s1 == NULL)
			return (ft_free(&s1, &tmp, &read_buffer), NULL);
		ft_free(&tmp, 0, 0);
	}
	free (read_buffer);
	return (s1);
}

static int	ft_find_endl(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0 && str[i] != '\n')
		i++;
	if (str[i] == 0)
		i--;
	return (i);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*buffer_read;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	result = NULL;
	buffer_read = ft_read_buffer(fd, buffer);
	if (buffer_read == NULL || buffer_read[0] == 0)
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		return (ft_free(&buffer_read, &result, 0), NULL);
	}
	result = ft_strndup(buffer_read, 0, ft_find_endl(buffer_read));
	ft_bzero(buffer, BUFFER_SIZE + 1);
	if (result == NULL)
		return (ft_free(&result, &buffer_read, 0), NULL);
	ft_memcpy(buffer, buffer_read + (ft_find_endl(buffer_read) + 1),
		ft_strlen(buffer_read) - (ft_find_endl(buffer_read) + 1) + 1);
	ft_free(&buffer_read, 0, 0);
	return (result);
}
