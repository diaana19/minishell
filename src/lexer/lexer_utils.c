#include "../includes/minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*tmp;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	tmp = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	return (tmp);
}