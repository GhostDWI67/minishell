/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:07:54 by dwianni           #+#    #+#             */
/*   Updated: 2024/11/01 17:15:19 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	t_list	*current;
	t_list	*new_node;

	start = NULL;
	current = NULL;
	while (lst != NULL)
	{
		new_node = (t_list *)malloc(sizeof(t_list));
		if (new_node == NULL)
		{
			ft_lstclear(&start, del);
			return (NULL);
		}
		new_node->content = f(lst->content);
		new_node->next = NULL;
		if (start == NULL)
			start = new_node;
		else
			current->next = new_node;
		current = new_node;
		lst = lst->next;
	}
	return (start);
}

/*
static void	*test_upper(void *elem)
{
	void	*res;
	void	*start;

	res = ft_strdup((char *)elem);
	start = res;
	while(*(char *)res != 0)
	{
		*(char *)res = ft_toupper(*(char *)res);
		res++;
	}
	return (start);
}

int	main(void)
{
	t_list	*test1;
	t_list	*test2;
	t_list	*test3;
	t_list	*start;
	t_list	*test;
	
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
	test = ft_lstmap(test1, test_upper, free);
	start = test1;
	while (start != NULL)
	{
		printf("%s\n",(char *)start->content);
		start = start->next;
	}
	start = test;
	while (start != NULL)
	{
		printf("%s\n",(char *)start->content);
		start = start->next;
	}
	return (0);
}
*/