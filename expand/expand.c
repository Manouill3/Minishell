/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:27:05 by mdegache          #+#    #+#             */
/*   Updated: 2025/04/21 23:24:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	*get_final_word(t_init *param, char *word, t_env *env)
{
	t_env	*tmp_env;
	char	*final_word;
	char	*no_quote;
	char	*env_comp;

	tmp_env = env;
	no_quote = all_quote_out(word);
	env_comp = char_out(no_quote, '$');
	if (!ft_strcmp("$?", no_quote))
	{
		final_word = get_result(ft_itoa(param->status), no_quote);
		free(env_comp);
		free(no_quote);
		return (final_word);
	}	
	while (tmp_env && ft_strcmp(env_comp, tmp_env->name))
		tmp_env = tmp_env->next;
	if (!tmp_env)
	{
		free(env_comp);
		free(no_quote);
		return (NULL);
	}
	final_word = get_result(ft_strdup(tmp_env->cont), no_quote);
	free(env_comp);
	free(no_quote);
	return (final_word);
}

char	*check_quote(t_init *param, char *word, t_env *env)
{
	char	*no_quote;
	char	*final_word;
	
	if(word[0] == 39)
	{
		final_word = char_out(word, 39);
		return (word);
	}
	else if (word[0] == '"')
	{
		no_quote = char_out(word, '"');
		final_word = expand_word(param, no_quote, env);
		free(no_quote);
		return (final_word);
	}
	final_word = get_final_word(param, word, env);
	return (final_word);
}

char	*get_actual_word(t_init *param, char *word, int i, int len, t_env *env)
{
	char	*sub_word;
	char	*final_word;
	
	if (i - len == 1 && word[len] == '$')
		sub_word = ft_substr(word, len, i - len + 1);
	else
		sub_word = ft_substr(word, len, i - len);
	if (!sub_word)
		return(NULL);
	final_word = check_quote(param, sub_word, env);
	free(sub_word);
	return (final_word);
}

char	*expand_word(t_init *param, char *word, t_env *env)
{
	int	i;
	int	len;
	char	*actual_word;
	char	*res;

	i = 0;
	res = NULL;
	while (word[i])
	{
		len = i;
		if(word[i] == 39 || word[i] == '"')
		{
			i = get_len_w_q(word, word[i], i);
			i++;
		}
		else
		{
			i++;
			while (word[i] && ft_isalnum(word[i]))
				i++; 
		}
		actual_word = get_actual_word(param, word, i, len, env);
		res = ft_strjoin(res, actual_word);
	}
	return (res);
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
					free(tmp_free);
				}
			}
			i++;
		}
		tmp = tmp->next;
	}
}
