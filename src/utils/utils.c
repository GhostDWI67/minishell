/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:33:44 by dwianni           #+#    #+#             */
/*   Updated: 2025/05/15 14:52:49 by mpalisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
Duplicate a string between first and last
Return : 1 string
******************************************************************************/
char	*ft_strndup(char const *src, int first, int last)
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

/******************************************************************************
Is white space
Return : 1 true , 0 = false
******************************************************************************/
int	ft_is_white_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

/******************************************************************************
Is white space
Return : 1 true , 0 = false
******************************************************************************/
void	ft_close(int fd)
{
	if (fd > 2)
		close(fd);
}

static bool	is_space(char c)
{
	if (c && (c == ' ' || c == '\n' || c == '\r' || c == '\f' || c == '\t' \
	|| c == '\v'))
		return (true);
	return (false);
}

bool	empty_line(char *line)
{
	int	i;

	if (!line)
		return (false);
	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (i == (int)ft_strlen(line))
	{
		free(line);
		return (true);
	}
	return (false);
}