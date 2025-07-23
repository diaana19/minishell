/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dianarituay <dianarituay@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:30:05 by dirituay          #+#    #+#             */
/*   Updated: 2025/06/22 21:37:28 by dianarituay      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_node	*ft_lstlast(t_node *lst)
{
	t_node	*node;

	node = lst;
	if (!lst)
		return (NULL);
	while (node -> next != NULL)
	{
		node = node -> next;
	}
	return (node);
}

/*int	main(void)
{
	int	a = 10;
	int	b = 20;
	int	c = 30;

	t_list *nodo1 = ft_lstnew(&a);
	t_list *nodo2 = ft_lstnew(&b);
	t_list *nodo3 = ft_lstnew(&c);

	nodo1 -> next = nodo2;
	nodo2 -> next = nodo3; //enlazamos los nodos
	
	t_list	*las_nodo = ft_lstlast(nodo1);
	printf("%d\n", *(int *)las_nodo->content);
	free(nodo1);
	free(nodo2);
	free(nodo3);
	return (0);
}*/
