/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:27:05 by mdegache          #+#    #+#             */
/*   Updated: 2025/04/01 14:04:34 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	*all_quote_out(char *str)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (str[i] != 39 && str[i] != '"')
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	return (new);
}

char	*char_out(char *str, char c)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (str[i] != c)
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	return (new);
}

char	*change_word(char *word, t_env *lst_env)
{
	char	*tmp;
	char	*tmp_word;
	char	*tmp_quote;
	t_env	*tmp_env;

	tmp_env = lst_env;
	word = char_out(word, '$');
	tmp_quote = char_out(word, 39);
	while (tmp_env && ft_strcmp(tmp_env->name, tmp_quote))
		tmp_env = tmp_env->next;
	if (!tmp_env)
		return (NULL);
	tmp_word = ft_substr(tmp_env->cont, ft_strlen(tmp_env->name) + 1,
			ft_strlen(tmp_env->cont));
	tmp = word;
	word = get_final_word(word, tmp_word);
	free(tmp);
	free(tmp_word);
	free(tmp_quote);
	return (word);
}

char	*expand_word(char *word, t_env *lst_env)
{
	char	*tmp;
	char	*tmp_free;

	tmp = ft_strdup(word);
	tmp_free = tmp;
	if (tmp[0] != tmp[ft_strlen(word) - 1])
	{
		tmp = all_quote_out(tmp);
		free(tmp_free);
		tmp_free = tmp;
		tmp = change_word(tmp, lst_env);
		free(tmp_free);
	}
	if (tmp[0] == 39)
	{
		tmp = all_quote_out(tmp);
		free(tmp_free);
	}
	if (tmp[0] == '"')
		tmp = expand_quote(tmp, tmp_free, lst_env);
	return (tmp);
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
					tmp->cmd[i] = expand_word(tmp->cmd[i], param->lst_env);
					free(tmp_free);
				}
			}
			i++;
		}
		tmp = tmp->next;
	}
}
