#include "../includes/minishell.h"

static char	*append_segment(char *current_result, const char *source, int len)
{
	char	*segment;
	char	*new_result;

	if (len < 0)
		len = ft_strlen(source);
	segment = ft_strndup(source, len);
	if (!segment)
	{
		free(current_result);
		return (NULL);
	}
	new_result = ft_strjoin(current_result, segment);
	free(current_result);
	free(segment);
	return (new_result);
}

static char	*expand_one_var(char *dollar_pos, t_data *data, int *len_orig)
{
	t_parse_re	result_parser;
	char		*expand_value;

	result_parser = get_var_name(dollar_pos, 0, *data);
	*len_orig = result_parser.i;
	if (result_parser.content)
		expand_value = result_parser.content;
	else
	{
		if (*len_orig == 0 || (*len_orig == 1 && (dollar_pos[1] == ' '
					|| dollar_pos[1] == '\0')))
		{
			expand_value = ft_strdup("$");
			if (!expand_value)
				return (NULL);
			*len_orig = 1;
		}
		else
		{
			expand_value = ft_strdup("");
			if (!expand_value)
				return (NULL);
		}
	}
	return (expand_value);
}

char	*handle_empty_line(const char *line)
{
	if (!line)
		return (ft_strdup(""));
	else
		return (ft_strdup(line));
}

static char	*process_expansion(char *result, char *dollar_pos, t_data *data,
		int *len_after_dollar)
{
	char	*expanded_value;

	expanded_value = expand_one_var(dollar_pos, data, len_after_dollar);
	if (!expanded_value)
	{
		free(result);
		return (NULL);
	}
	result = append_segment(result, expanded_value, -1);
	free(expanded_value);
	return (result);
}

char	*process_dollar_loop(char *result, char *current_i, t_data *data)
{
	char	*dollar_pos;
	int		len_after_dollar;

	dollar_pos = ft_strchr(current_i, '$');
	while (dollar_pos != NULL)
	{
		result = append_segment(result, current_i, dollar_pos - current_i);
		if (!result)
			return (NULL);
		result = process_expansion(result, dollar_pos, data, &len_after_dollar);
		if (!result)
			return (NULL);
		current_i = dollar_pos + len_after_dollar;
		dollar_pos = ft_strchr(current_i, '$');
	}
	result = append_segment(result, current_i, -1);
	return (result);
}