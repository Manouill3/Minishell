/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_res.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:55:11 by mdegache          #+#    #+#             */
/*   Updated: 2025/04/22 14:16:58 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	*expand_quote(t_init *param, char *word, t_env *env)
{
	int i;
    int len;
    char    *actual_word;
    char    *res;
    
    i = 0;
    res = NULL;
    actual_word = NULL;
    while(word[i])
    {
        len = i;
        i++;
        while(word[i] && ft_isalnum(word[i]))
            i++;
        actual_word = get_actual_word(param, word, i, len, env);
        res = ft_strjoin(res, actual_word);
        if (ft_strcmp(res, actual_word))
            free(actual_word);
    }
    return (res);
}

char	*get_result(char *cont, char *word)
{
	int		i;
	int		j;
	int		k;
	char	*result;

	i = 0;
	j = 0;
	k = 0;
	result = ft_calloc(ft_strlen(cont) + count_quote(word) + 1, sizeof(char));
	if (!result)
		return (NULL);
	while (j < (int)ft_strlen(cont) + count_quote(word))
	{
		if (word[i] != 39 && word[i] != '"')
		{
			while (word[i] && word[i] != 39 && word[i] != '"')
				i++;
			while (cont[k])
				result[j++] = cont[k++];
		}
		else
			result[j++] = word[i++];
	}
	free(cont);
	return (result);
}
