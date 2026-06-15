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