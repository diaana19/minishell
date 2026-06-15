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