/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 09:03:54 by dwianni           #+#    #+#             */
/*   Updated: 2024/11/01 14:50:43 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst != NULL)
	{
		(f)(lst->content);
		lst = lst->next;
	}
}
/*
static void	test_upper(void *elem)
{
	int	i;

	i = 0;
	while(*(char *)elem != 0)
	{
		*(char *)elem = ft_toupper(*(char *)elem);
		elem++;
	}
}

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
	while (start != NULL)
	{
		printf("%s\n",(char *)start->content);
		start = start->next;
	}
	ft_lstiter(test1,test_upper);
	start = test1;
	while (start != NULL)
	{
		printf("%s\n",(char *)start->content);
		start = start->next;
	}
	return (0);
}
*/