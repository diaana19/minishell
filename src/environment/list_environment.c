#include "../includes/minishell.h"

char	*duplicated_str(t_env *node, char *str_copy, bool is_name)
{
	char	*dupli_str;

	if (!str_copy)
		return (NULL);
	dupli_str = ft_strdup(str_copy);
	if (!dupli_str)
	{
		if (!is_name)
			free(node->name);
		free(node);
		return (NULL);
	}
	return (dupli_str);
}

t_env	*new_env(char *name, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = duplicated_str(new, name, true);
	if (!new->name && name)
		return (NULL);
	new->value = duplicated_str(new, value, false);
	if (!new->value && value)
		return (NULL);
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = *lst;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}