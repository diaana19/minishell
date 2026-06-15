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