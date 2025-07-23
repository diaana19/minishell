/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dianarituay <dianarituay@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:33:12 by dirituay          #+#    #+#             */
/*   Updated: 2025/06/22 21:36:40 by dianarituay      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_node **lst, t_node *new)
{
	new -> next = *lst;
	*lst = new;
}

/*void	ft_lstprint(t_list *lst)
{
	while (lst)
	{
		printf("%d\n", *(int *)lst->content);
		lst = lst -> next;
	}
}
int	main(void)
{
	int	a = 42;
	int	b = 84;
	int	c = 21;

	t_list	*nodo = ft_lstnew(&a);
	ft_lstadd_front(&nodo, ft_lstnew(&b));
	ft_lstadd_front(&nodo, ft_lstnew(&c));
	ft_lstprint(nodo);
	return (0);
}*/
