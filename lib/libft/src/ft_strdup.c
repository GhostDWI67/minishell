/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 08:58:05 by dwianni           #+#    #+#             */
/*   Updated: 2024/10/28 21:40:54 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*dest;
	size_t	i;

	dest = (char *) malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen(src))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/*
int	main(void)
{
	char *cpy;
		
	cpy = ft_strdup("0123456789");
	printf("%s\n", cpy);
	printf("%zu\n", ft_strlen(cpy));
	free (cpy);
	return (0);
}
*/
