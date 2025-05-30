/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:27:05 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/27 13:41:23 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	*get_result(char *cont, char *sub_word, t_init *param)
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
	res = add_calloc(param->mal, len + 1, sizeof(char));
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
		no_quote = char_out(word, 39, param->mal);
		if (ft_strlen(word) == 0)
			return (NULL);
		return (no_quote);
	}
	if (word[0] == '"')
		return (handle_double_quote(param, word));
	if (!ft_strchr(word, '$'))
		return (ft_strdup(word, param->mal));
	final_word = get_env_value(env, word, param);
	return (final_word);
}

char	**expand_input(t_init *param, char *word, char **inputs)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (word[i])
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
			while (word[i] && (word[i] != '$' && word[i] != '"'
					&& word[i] != 39))
				i++;
		}
		inputs[k++] = get_actual_word(param, word, i, j);
	}
	return (inputs);
}

char	*expand_word(t_init *param, char *word)
{
	int		i;
	int		len;
	char	*res;
	char	**inputs;

	i = 0;
	len = inputs_len(word);
	inputs = add_calloc(param->mal, len + 1, sizeof(char *));
	if (!inputs)
		return (NULL);
	inputs = expand_input(param, word, inputs);
	if (!inputs)
		return (NULL);
	res = add_calloc(param->mal, final_len(inputs, len) + 1, sizeof(char));
	if (!res)
		return (NULL);
	res = get_final_input(res, inputs, len);
	while (i < len)
	{
		if (!inputs[i])
			inputs[i] = ft_strdup(res, param->mal);
		i++;
	}
	return (res);
}

void	expand_arg(t_init *param)
{
	int			i;
	int			j;
	t_list_char	*tmp;

	tmp = param->tok;
	while (tmp)
	{
		i = 0;
		j = 0;
		tmp->len_ind_exp = nb_exp(tmp->cmd);
		tmp->ind_exp = add_calloc(param->mal, sizeof(int), nb_exp(tmp->cmd));
		while (tmp->cmd[i])
		{
			handle_expand(param, tmp, i, &j);
			i++;
		}
		tmp = tmp->next;
	}
}
