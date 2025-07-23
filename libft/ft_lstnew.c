/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dianarituay <dianarituay@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:15:22 by dirituay          #+#    #+#             */
/*   Updated: 2025/06/23 13:13:34 by dianarituay      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_node	*ft_lstnew(void *content)
{
	t_node	*nodo;

	nodo = (t_node *)malloc(sizeof(t_node));
	if (!nodo)
		return (NULL);
	nodo -> content = content;
	nodo -> next = NULL;
	return (nodo);
}

/*int	main(void)
{
	int	valor = 42;
	int	valor2 = 40;

	t_list	*nodo = ft_lstnew(&valor);
	t_list	*nodo1 = ft_lstnew(&valor2);
	t_list	*primernodo = nodo; //comenzamos desde el primer nodo

	nodo -> next = nodo1; //enlazamos los nodos
	while (primernodo != NULL)
	{
		printf("%d\n", *(int *)primernodo -> content); 
		//usamos el operador * para acceder al valor de int *
		primernodo = primernodo -> next;
	}
	free(nodo);
	free(nodo1);
	return (0);
}*/
