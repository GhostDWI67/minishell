/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:07:36 by dwianni           #+#    #+#             */
/*   Updated: 2024/11/01 17:11:40 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*res;

	res = (t_list *)malloc(sizeof(t_list));
	if (res == NULL)
		return (NULL);
	res->content = content;
	res->next = NULL;
	return (res);
}
/*
int	main(void)
{
	t_list	*test1;

	test1 = ft_lstnew("test1");
	printf("%s\n",(char *)test1->content);
	free(test1);
	return (0);
}
*/