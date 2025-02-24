/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:05:28 by dwianni           #+#    #+#             */
/*   Updated: 2024/11/01 13:36:35 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	if (*lst != NULL)
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;
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
	printf("%p\n",test1);
	printf("%p\n",test1->next);
	printf("%p\n",test2);
	printf("%p\n",test2->next);
	printf("%p\n",test3);
	printf("%p\n",test3->next);
	start = test2;
	ft_lstadd_front(&start, test1);
	ft_lstadd_back(&start, test3);
	printf("%p\n",test1->next);
	printf("%p\n",test2->next);
	printf("%p\n",test3->next);
	start = test1;
	while (start != NULL)
	{
		printf("%s\n",(char *)start->content);
		start = start->next;
	}
	return (0);
}
*/