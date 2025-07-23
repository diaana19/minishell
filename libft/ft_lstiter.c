/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dianarituay <dianarituay@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 20:03:47 by dirituay          #+#    #+#             */
/*   Updated: 2025/06/22 21:37:00 by dianarituay      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_node *lst, void (*f)(void *))
{
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst -> next;
	}
}
/*void	print_content(void* content)
{
	printf("%s", (char *)content);
}

int	main(void)
{
	t_list	*nodo1 = ft_lstnew(ft_strdup("Hello"));
	t_list	*nodo2 = ft_lstnew(ft_strdup("Mundo"));

	nodo1 -> next = nodo2;
	ft_lstiter(nodo1, print_content);
	free(nodo1 -> content);
	free(nodo2 -> content);
	free(nodo1);
	free(nodo2);
	return (0);
}*/
