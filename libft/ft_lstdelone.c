#include "libft.h"

void	ft_lstdelone(t_node *lst, void (*del)(void*))
{
	if (lst != NULL)
	{
		del(lst -> content);
		free(lst);
	}
}