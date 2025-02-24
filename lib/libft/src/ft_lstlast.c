/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:16:03 by dwianni           #+#    #+#             */
/*   Updated: 2024/11/01 13:40:23 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst != NULL && lst->next != NULL)
		lst = lst->next;
	return (lst);
}
/*
int	main(void)
{
	t_list	*test1;
	t_list	*test2;
	t_list	*test3;
	t_list	*start;
	
	test1 = ft_lstnew(ft_strdup("test1"));
	test2 = ft_lstnew(ft_strdup("test2"));
	test3 = ft_lstnew(ft_strdup("test3"));
	start = test2;
	ft_lstadd_front(&start, test1);
	ft_lstadd_back(&start, test3);
	start = test1;
	printf("%s\n",(char *)(ft_lstlast(start))->content);
	return (0);
}
*/