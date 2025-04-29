/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_res2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:46:26 by mdegache          #+#    #+#             */
/*   Updated: 2025/04/29 09:59:00 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	*get_actual_word_q(t_init *param, char *word, int i, int len, t_env *env)
{
	char	*sub_word;
	char	*final_word;

	if (i - len == 1 && word[len] == '$')
	{
		sub_word = ft_substr(word, len, i - len + 1);
		if (!sub_word)
			return (NULL);
		if (!ft_strcmp("$?", sub_word))
		{
			free(sub_word);
			return (ft_itoa(param->status));
		}
		else if (!ft_isalnum(word[i]))
		{
			free(sub_word);
			return (ft_strdup("$"));
		}
		else if (!ft_strcmp("$_", sub_word))
		{
			final_word = check_quote(param, sub_word, env);
			free(sub_word);
			return (final_word);
		}
		else
		{
			free(sub_word);
			return(NULL);
		}
	}
	sub_word = ft_substr(word, len, i - len);
	if (!sub_word)
		return (NULL);
	final_word = check_quote_q(param, sub_word, env);
	free(sub_word);
	return (final_word);
}

char	*get_actual_word(t_init *param, char *word, int i, int len, t_env *env)
{
	char	*sub_word;
	char	*final_word;

	if (i - len == 1 && word[len] == '$')
	{
		sub_word = ft_substr(word, len, i - len + 1);
		if (!sub_word)
			return (NULL);
		if (!ft_strcmp("$?", sub_word))
		{
			free(sub_word);
			return (ft_itoa(param->status));
		}
		else if (!ft_strcmp("$_", sub_word))
		{
			final_word = check_quote(param, sub_word, env);
			free(sub_word);
			return (final_word);
		}
		else if (!ft_isalnum(word[i]))
		{
			free(sub_word);
			return (ft_strdup("$"));
		}
		else
		{
			free(sub_word);
			return(NULL);
		}
	}
	sub_word = ft_substr(word, len, i - len);
	if (!sub_word)
		return (NULL);
	final_word = check_quote(param, sub_word, env);
	free(sub_word);
	return (final_word);
}
