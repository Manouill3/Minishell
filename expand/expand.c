/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:27:05 by mdegache          #+#    #+#             */
/*   Updated: 2025/04/25 15:34:09 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	len_get_exit_value(int status, char *word)
{
	
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
	while (word[len])
		len++;
	len--;
	final_word = ft_calloc(len + 1, sizeof(char));
	if (!final_word)
		return (NULL);
	len = 0;
	while (word[i] && word[i] != '$')
		final_word[j++] = word[i++];
	while (value[len])
		final_word[j++] = value[len++]; 
	while (word[i])
		final_word[j++] = word[i++];
	return (final_word);
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

char	*get_actual_word_q(t_init *param, char *word, int i, int len, t_env *env)
{
	char	*sub_word;
	char	*final_word;

	if (i - len == 1 && word[len] == '$')
	{
		sub_word = ft_substr(word, len, i - len + 1);
		if (!sub_word)
			return (NULL);
		printf("sub_word = %s\n", sub_word);
		if (!ft_strcmp("$?", sub_word))
		{
			free(sub_word);
			return (ft_itoa(param->status));
		}
		if (!ft_isalnum(word[i]))
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
	printf("sub_word_out = %s\n", sub_word);
	final_word = check_quote_q(param, sub_word, env);
	free(sub_word);
	return (final_word);
}

char	**expand_input_q(t_init *param, char *word, t_env *env, char **inputs)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while(word[i])
	{
		if (i > 0 && word[i] == '?' && word[i - 1] == '$')
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

char	*expand_quote(t_init *param, t_env *env, char *word)
{
	int		i;
	int		len;
	char	*res;
	char	**inputs;

	len = inputs_len(word);
	inputs = ft_calloc(len + 1, sizeof(char *));
	if (!inputs)
		return (NULL);
	inputs = expand_input_q(param, word, env, inputs);
	if (!inputs)
		return (NULL);
	res = ft_calloc(final_len(inputs, len) + 1, sizeof(char));
	if (!res)
		return(NULL);
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

char	*get_final_input(char *res, char **inputs, int len)
{
	int	i;
	int	j;
	int	k;
	
	i = 0;
	k = 0;
	while (i < len)
	{
		j = 0;
		while (j < (int)ft_strlen(inputs[i]))
			res[k++] = inputs[i][j++];
		i++;
	}
	return (res);
}

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

char	*check_quote(t_init *param, char *word, t_env *env)
{
	char	*no_quote;
	char	*final_word;

	if (word[0] == 39)
	{
		if (ft_strlen(word) == 0)
			return(NULL);
		final_word = char_out(word, 39);
		return (final_word);
	}
	if (word[0] == '"')
	{
		if (ft_strlen(word) == 0)
			return(NULL);
		no_quote = char_out(word, '"');
		if (!ft_strchr(no_quote, '$'))
			return(no_quote);
		final_word = expand_quote(param, env, no_quote);
		free(no_quote);
		return(final_word);
	}
	if (!ft_strchr(word, '$'))
		return(ft_strdup(word));
	final_word = get_env_value(env, word);
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
		printf("sub_word = %s\n", sub_word);
		if (!ft_strcmp("$?", sub_word))
		{
			free(sub_word);
			return (ft_itoa(param->status));
		}
		if (!ft_isalnum(word[i]))
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
	printf("sub_word_out = %s\n", sub_word);
	final_word = check_quote(param, sub_word, env);
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
		if (i > 0 && word[i] == '?' && word[i - 1] == '$')
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
		inputs[k++] = get_actual_word(param, word, i, j, env);
	}
	return (inputs);
}

char	*expand_word(t_init *param, char *word, t_env *env)
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
	inputs = expand_input(param, word, env, inputs);
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
					printf("cmd = %s\n", tmp->cmd[i]);
				}
			}
			i++;
		}
		tmp = tmp->next;
	}
}
