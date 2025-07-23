/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dianarituay <dianarituay@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:01:12 by dirituay          #+#    #+#             */
/*   Updated: 2025/06/22 21:37:45 by dianarituay      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_node	*ft_lstmap(t_node *lst, void *(*f)(void*), void (*del)(void *))
{
	t_node	*newlst;
	t_node	*nodo;
	void	*trascontent;

	if (!f || !del || !lst)
		return (NULL);
	newlst = NULL;
	while (lst != NULL)
	{
		trascontent = f(lst->content);
		nodo = ft_lstnew(trascontent);
		if (!nodo)
		{
			del(trascontent);
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		ft_lstadd_back(&newlst, nodo);
		lst = lst->next;
	}
	return (newlst);
}

/*void	del(void *content)
{
	free(content);
}

void	*f(void *content)
{
	int	*new;

	new = malloc(sizeof(int));
	*(new) = (*(int *)content) * 2;
	return (new);
}

int	main(void)
{
	t_list	*lst = NULL;
	t_list	*newnodo;
	t_list	*temp;

	int	*num1 = malloc(sizeof(int));
	int	*num2 = malloc(sizeof(int));
	int	*num3 = malloc(sizeof(int));

	*num1 = 10; 
	*num2 = 20;
	*num3 = 30;
	lst = ft_lstnew(num1);//creamos nodos y agregamos a la lista
	lst->next = ft_lstnew(num2);
	lst->next->next = ft_lstnew(num3);
	newnodo = ft_lstmap(lst, f, del);
	temp = newnodo; //imprimir valores antes de liberar la memoria
	while (temp != NULL)
	{
		printf("%d\n", *(int *)temp->content);
		temp = temp-> next;
	}
	ft_lstclear(&lst, del); //liberamos memoria lista original
	ft_lstclear(&newnodo, del);
	return (0);

}*/
