/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dianarituay <dianarituay@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:17:09 by dirituay          #+#    #+#             */
/*   Updated: 2025/06/22 21:36:31 by dianarituay      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_node **lst, t_node *new)
{
	t_node	*last;

	last = ft_lstlast(*lst);
	if (!last)
	{
		*lst = new;
		return ;
	}
	last -> next = new;
}

/*int	main(void)
{
	int	a = 10;
	int	b = 20;
	int	c = 30;

	t_list	*nodo1 = ft_lstnew(&a);
	t_list	*nodo2 = ft_lstnew(&b);
	t_list	*nodo3 = ft_lstnew(&c);

	ft_lstadd_back(&nodo1, nodo2); //lista 10 y nodo2 10, 20
	ft_lstadd_back(&nodo1, nodo3); //lista 10, 20 y nodo3 10, 20, 20

	t_list	*lista = nodo1;
	while (lista != NULL)
	{
		printf("%d\n", *(int *)lista -> content);
		lista = lista -> next;
	}
	free(nodo1);
	free(nodo2);
	free(nodo3);
	return (0);
}*/
