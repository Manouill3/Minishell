/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_res2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:46:26 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/07 13:18:04 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	*get_env_value(t_env *env, char *sub_word)
{
	char	*no_quote;
	char	*env_comp;
	char	*final_word;
	t_env	*tmp;

	no_quote = all_quote_out(sub_word);
	env_comp = char_out(no_quote, '$');
	tmp = env;
	while (tmp && ft_strcmp(env_comp, tmp->name))
		tmp = tmp->next;
	if (!tmp)
	{
		free(no_quote);
		free(env_comp);
		return (NULL);
	}
	final_word = get_result(tmp->cont, sub_word);
	free(no_quote);
	free(env_comp);
	return (final_word);
}

char	*expand_quote(t_init *param, char *word)
{
	int		i;
	int		len;
	char	*res;
	char	**inputs;

	len = inputs_len(word);
	inputs = ft_calloc(len + 1, sizeof(char *));
	if (!inputs)
		return (NULL);
	inputs = expand_input_q(param, word, inputs);
	if (!inputs)
		return (NULL);
	res = ft_calloc(final_len(inputs, len) + 1, sizeof(char));
	if (!res)
		return (NULL);
	res = get_final_input(res, inputs, len);
	i = 0;
	while (i < len)
	{
		if (!inputs[i])
			inputs[i] = ft_strdup(res);
		i++;
	}
	free_tab(inputs);
	return (res);
}

char	*get_actual_word_q(t_init *param, char *word, int i, int len)
{
	char	*sub_word;
	char	*final_word;

	if (i - len == 1 && word[len] == '$')
	{
		sub_word = ft_substr(word, len, i - len + 1);
		if (!sub_word)
			return (NULL);
		final_word = one_char_test(param, word, sub_word, i);
		return (final_word);
	}
	sub_word = ft_substr(word, len, i - len);
	if (!sub_word)
		return (NULL);
	final_word = check_quote_q(param, sub_word, param->lst_env);
	free(sub_word);
	return (final_word);
}

char	*get_actual_word(t_init *param, char *word, int i, int len)
{
	char	*sub_word;
	char	*final_word;

	if (i - len == 1 && word[len] == '$')
	{
		sub_word = ft_substr(word, len, i - len + 1);
		if (!sub_word)
			return (NULL);
		final_word = one_char_test(param, word, sub_word, i);
		free(sub_word);
		return (final_word);
	}
	sub_word = ft_substr(word, len, i - len);
	if (!sub_word)
		return (NULL);
	final_word = check_quote(param, sub_word, param->lst_env);
	free(sub_word);
	return (final_word);
}

char	*one_char_test(t_init *param, char *word, char *sub_word, int i)
{
	char	*final_word;

	if (!ft_strcmp("$?", sub_word))
		return (ft_itoa(param->status));
	else if (!ft_strcmp("$_", sub_word))
	{
		final_word = check_quote(param, sub_word, param->lst_env);
		return (final_word);
	}
	else if (word[i] == '"' || word[i] == 39)
		return (NULL);
	else if (!ft_isalnum(word[i]))
		return (ft_strdup("$"));
	else
		return (NULL);
}
