/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_res.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:55:11 by mdegache          #+#    #+#             */
/*   Updated: 2025/04/29 09:45:52 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	**expand_input_q(t_init *param, char *word, t_env *env, char **inputs)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while(word[i])
	{
		if (i > 0 && (word[i] == '?' || word[i] == '_') && word[i - 1] == '$')
			i++;
		j = i;
		if (word[i] == '"' || word[i] == 39)
			i = get_len_w_q(word, word[i], i);
		else if (word[i] == '$')
			i = get_len_w_d(word, i);
		else
		{
			while (word[i] &&
				(word[i] != '$' && word[i] != '"' && word[i] != 39))
				i++;
		}
		inputs[k++] = get_actual_word_q(param, word, i, j, env);
	}
	return (inputs);
}

char	*check_quote_q(t_init *param, char *word, t_env *env)
{
	char	*no_quote;
	char	*final_word;

	
	no_quote = char_out(word, 39);
	if (!ft_strcmp(no_quote, "$?"))
	{
		free(no_quote);
		return (get_exit_value(param, word));
	}
	if (ft_strlen(no_quote) == 1 && no_quote[0] == '$')
	{
		free(no_quote);
		return (ft_strdup(word));
	}
	free (no_quote);
	if (!ft_strchr(word, '$'))
		return(ft_strdup(word));
	final_word = get_env_value(env, word);
	return (final_word);
}

char	*get_exit_value(t_init *param, char *word)
{
	int i;
	int	j;
	int len;
	char	*value;
	char	*final_word;

	i = 0;
	j = 0;
	len = len_get_exit_value(param->status, word);
	value = ft_itoa(param->status);
	final_word = ft_calloc(len + 1, sizeof(char));
	if (!final_word)
		return (NULL);
	len = 0;
	while (word[i] && word[i] != '$')
		final_word[j++] = word[i++];
	while (value[len])
		final_word[j++] = value[len++];
	while (word[i] && (word[i] == '$' || word[i] == '?'))
		i++;
	while (word[i])
		final_word[j++] = word[i++];
	free (value);
	return (final_word);
}

int	len_get_exit_value(int status, char *word)
{
	int	i;
	int	j;
	int	count;
	char *value;

	i = 0;
	j = 0;
	count = 0;
	value = ft_itoa(status);
	while (word[i] && word[i++] != '$')
		count++;
	while (value[j++])
		count++;
	while (word[i] && (word[i] == '$' || word[i] == '?'))
		i++;
	while (word[i++])
		count++;
	free (value);	
	return (count);
}

int final_len(char **inputs, int l)
{
    int i;
    int j;
    int len;

    i = 0;
    len = 0;
    while (i < l)
    {
        j = 0;
        while (j < (int)ft_strlen(inputs[i]))
        {
            j++;
            len++;
        }
        i++;
    }
    return (len);
}
