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