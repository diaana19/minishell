#include "libft.h"

void	ft_lstiter(t_node *lst, void (*f)(void *))
{
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst -> next;
	}
}