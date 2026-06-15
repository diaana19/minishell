#include "../includes/minishell.h"

static int	argv_count(char **argv)
{
	int	count;

	count = 0;
	if (!argv)
		return (0);
	while (argv[count] != NULL)
		count++;
	return (count);
}

static int	copy_argv(char **dest, char **src, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
		{
			while (--i >= 0)
				free(dest[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

int	add_to_argv(t_cmd *cmd, const char *word)
{
	int		count;
	char	**new_argv;

	count = argv_count(cmd->argv);
	new_argv = malloc(sizeof(char *) * (count + 2));
	if (!new_argv)
		return (0);
	if (!copy_argv(new_argv, cmd->argv, count))
	{
		free(new_argv);
		return (0);
	}
	new_argv[count] = ft_strdup(word);
	if (!new_argv[count])
	{
		free(new_argv);
		return (0);
	}
	new_argv[count + 1] = NULL;
	free_argv(cmd->argv);
	cmd->argv = NULL;
	cmd->argv = new_argv;
	return (1);
}