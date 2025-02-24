/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:58:40 by dwianni           #+#    #+#             */
/*   Updated: 2024/11/01 14:02:55 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next;

	if (*lst == NULL)
		return ;
	while (*lst != NULL)
	{
		next = (*lst)->next;
		(del)((*lst)->content);
		free(*lst);
		*lst = next;
	}
	*lst = NULL;
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
	while (start != NULL)
	{
		printf("%s\n",(char *)start->content);
		start = start->next;
	}
	ft_lstclear(&test1,free);
	return (0);
}
*/