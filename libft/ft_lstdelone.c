/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dianarituay <dianarituay@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:06:19 by dirituay          #+#    #+#             */
/*   Updated: 2025/06/22 21:36:55 by dianarituay      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_node *lst, void (*del)(void*))
{
	if (lst != NULL)
	{
		del(lst -> content);
		free(lst);
	}
}

/*void	del(void* content)
{
	free(content);
}

int	main(void)
{
	t_list	*nodo;

	nodo = malloc(sizeof(t_list));
	if (!nodo)
		return (1);
	//asignamos contenido al nodo
	nodo -> content = malloc(6 *sizeof(char));
	if (!nodo -> content)
	{
		free(nodo);
		return (1);
	}
	snprintf(nodo -> content, 6, "Hello");
	nodo -> next = NULL;
	printf("antes de eliminar: %s\n", (char *)nodo -> content);
	ft_lstdelone(nodo, del);
	printf("nodo eliminado");
	return (0);
}*/
