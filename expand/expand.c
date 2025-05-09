/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:27:05 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/09 10:40:36 by mdegache         ###   ########.fr       */
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
	j = 0;
	k = 0;
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

char	*check_quote(t_init *param, char *word, t_env *env)
{
	char	*no_quote;
	char	*final_word;

	if (word[0] == 39)
	{
		no_quote = char_out(word, 39);
		if (ft_strlen(word) == 0)
			return(NULL);
		return (no_quote);
	}
	if (word[0] == '"')
	{
		if (ft_strlen(word) == 0)
			return(NULL);
		no_quote = char_out(word, '"');
		if (!ft_strchr(no_quote, '$'))
			return(no_quote);
		final_word = expand_quote(param, no_quote);
		if (!ft_strcmp(final_word, no_quote))
		{
			free(no_quote);
			free(final_word);
			return (ft_strdup(word));
		}
		free(no_quote);
		return(final_word);
	}
	if (!ft_strchr(word, '$'))
		return(ft_strdup(word));
	final_word = get_env_value(env, word);
	return (final_word);
}

char	**expand_input(t_init *param, char *word, char **inputs)
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
		inputs[k++] = get_actual_word(param, word, i, j);
	}
	return (inputs);
}

char	*expand_word(t_init *param, char *word)
{
	int i;
	int		len;
	char	*res;
	char	**inputs;

	i = 0;
	len = inputs_len(word);
	inputs = ft_calloc(len + 1, sizeof(char *));
	if (!inputs)
		return (NULL);
	inputs = expand_input(param, word, inputs);
	if (!inputs)
		return (NULL);
	res = ft_calloc(final_len(inputs, len) + 1, sizeof(char));
	if (!res)
		return(NULL);
	res = get_final_input(res, inputs, len);
	while (i < len)
	{
		if (!inputs[i])
			inputs[i] = ft_strdup(res);
		i++;
	}
	free_tab(inputs);
	return (res);
}

void	expand_arg(t_init *param)
{
	int			i;
	int			j;
	char		*tmp_free;
	t_list_char	*tmp;

	tmp = param->tok;
	while (tmp)
	{
		i = 0;
		tmp->ind_exp = ft_calloc(sizeof(int), nb_exp(tmp->cmd) + 1);
		if (!tmp->ind_exp)
			return ;
		while (tmp->cmd[i])
		{
			j = 0;
			if (ft_strchr(tmp->cmd[i], '$'))
			{
				if (i == 0 || ft_strcmp("<<", tmp->cmd[i - 1]) || ft_strcmp(">", tmp->cmd[i - 1]) || ft_strcmp(">>", tmp->cmd[i - 1]) || ft_strcmp("<", tmp->cmd[i - 1]))
				{
					tmp->ind_exp[j++] = i;
					tmp_free = tmp->cmd[i];
					tmp->cmd[i] = expand_word(param, tmp->cmd[i]);
					free(tmp_free);
				}
			}
			i++;
		}
		tmp = tmp->next;
	}
}
