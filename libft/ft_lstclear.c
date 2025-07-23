/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dianarituay <dianarituay@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 19:26:32 by dirituay          #+#    #+#             */
/*   Updated: 2025/06/22 21:36:50 by dianarituay      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_node **lst, void (*del)(void*))
{
	t_node	*tmp;

	if (!lst || !*lst)
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
	*lst = NULL;
}

/*void	del(void* content)
{
	free(content);
}

int	main(void)
{
	t_list	*nodo1 = ft_lstnew(malloc(6 *sizeof(char)));
	if (nodo1)
		snprintf(nodo1 -> content, 6, "Hello");
	t_list	*nodo2 = ft_lstnew(malloc(6 *sizeof(char)));
	if (nodo2)
		snprintf(nodo2 -> content, 6, "Wolrd");
	nodo1 -> next = nodo2;
	t_list	*tmp = nodo1;
	while (tmp != NULL)
	{
		printf("%s\n", (char *)tmp -> content);
		tmp = tmp -> next;
	}
	ft_lstclear(&nodo1, del);
	if (!nodo1)
		printf("lista vacia");
	return (0);
}*/
