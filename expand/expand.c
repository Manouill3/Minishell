/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:27:05 by mdegache          #+#    #+#             */
/*   Updated: 2025/04/22 22:06:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	*get_result(char *cont, char *sub_word)
{
	int		i;
	int		j;
	int		k;
	int		len;
	char	*res;

	i = 0;
	len = count_quote(sub_word) + ft_strlen(cont);
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (sub_word[i] == 39 || sub_word[i] == '"')
		res[i++] = sub_word[j++];
	while (cont[k])
		res[i++] = cont[k++];
	while (sub_word[j] && sub_word[j] != 39 && sub_word[j] != '"')
		j++;
	while (sub_word[j] == 39 || sub_word[j] == '"')
		res[i++] = sub_word[j++];
	return (res);
}

char	*get_env_value(t_env *env, char *sub_word)
{
	char	*no_quote;
	char	*env_comp;
	char	*final_word;
	t_env	*tmp;

	no_quote = all_quote_out(sub_word);
	env_comp = char_out(no_quote, '$');
	tmp = env;
	while (tmp && ft_strcmp(env->cont, tmp->name))
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

char	*check_quote(char *word, t_env *env)
{
	char	*no_quote;
	char	*final_word;

	if (word[0] == 39)
	{
		final_word = char_out(word, 39);
		return (final_word);
	}
	if (word[0] == '"')
	{
		no_quote = char_out(word, '"');
		final_word = get_env_value(env, no_quote);
		free(no_quote);
		return(final_word);
	}
	final_word = get_env_value(env, word);
	return (final_word);
}

char	*get_actual_word(t_init *param, char *word, int i, int len, t_env *env)
{
	char	*sub_word;
	char	*final_word;

	if (i - len == 1 && word[len] == '$')
	{
		sub_word = ft_substr(word, len, i - len);
		if (!sub_word)
			return (NULL);
		if (!ft_strcmp(sub_word, "$?"))
		{
			free(sub_word);
			return (ft_itoa(param->status));
		}
	}
	sub_word = ft_substr(word, len, i - len);
	if (!sub_word)
		return (NULL);
	final_word = check_quote(sub_word, env);
	free(sub_word);
	return (final_word);
}

char	**expand_input(t_init *param, char *word, t_env *env, char **inputs)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while(word[i])
	{
		j = i;
		if (word[i] == '"' || word[i] == 39)
			i = get_len_w_q(word, word[i], i);
		else if (word[i] == '$')
			i = get_len_w_d(word, i);
		else
		{
			while (word[i] && word[i] != '$')
				i++;
		}
		inputs[k++] = get_actual_word(param, word, i, j, env);
	}
	return (inputs);
}

char	*expand_word(t_init *param, char *word, t_env *env)
{
	int		i;
	int	len;
	char	**inputs;

	len = inputs_len(word);
	printf("len = %d\n", len);
	inputs = ft_calloc(len + 1, sizeof(char *));
	if (!inputs)
		return (NULL);
	inputs = expand_input(param, word, env, inputs);
	if (!inputs)
		return (NULL);
	i = 0;
	while (inputs[i])
	{
		printf("inputs[%d] = %s\n", i, inputs[i]);
		i++;
	}
	return (inputs[0]);
}

void	expand_arg(t_init *param)
{
	int			i;
	char		*tmp_free;
	t_list_char	*tmp;

	tmp = param->tok;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd[i])
		{
			if (ft_strchr(tmp->cmd[i], '$'))
			{
				if (i == 0 || ft_strcmp("<<", tmp->cmd[i - 1]))
				{
					tmp_free = tmp->cmd[i];
					tmp->cmd[i] = expand_word(param, tmp->cmd[i], param->lst_env);
					printf("cmd = %s\n", tmp->cmd[i]);
					free(tmp_free);
				}
			}
			i++;
		}
		tmp = tmp->next;
	}
}
