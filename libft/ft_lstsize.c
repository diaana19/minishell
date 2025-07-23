/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dianarituay <dianarituay@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:13:08 by dirituay          #+#    #+#             */
/*   Updated: 2025/06/22 21:38:11 by dianarituay      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_node *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst -> next;
	}
	return (i);
}

/*int	main(void)
{
	int	a = 42;
	int	b = 84;
	int	c = 21;

	t_list *nodo = ft_lstnew(&a);
	ft_lstadd_front(&nodo, ft_lstnew(&b));
	ft_lstadd_front(&nodo, ft_lstnew(&c));
	int	size = ft_lstsize(nodo);
	printf("%d\n", size);
	return (0);
}*/
