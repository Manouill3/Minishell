/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:27:05 by mdegache          #+#    #+#             */
/*   Updated: 2025/04/22 16:36:27 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	**expand_arg(t_init *param, char *word, t_env *env, char **inputs)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while(word[i])
	{
		j = i;
		if (word[i] == '"' || word[i] == 39)
			i = get_len_w_q(word, word[i], i)
		else if (word[i] == '$')
			i = get_len_w_d(word, i);
		else
		{
			while (word[i] && word[i] != '$')
				i++;
		}
		inputs[k] = get_actual_word()
	}
}

int	inputs_len(char *word)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (word[i])
	{
		if (word[i] == '"' || word[i] == 39)
		{
			i = get_len_w_q(word, word[i], i)
			len++;
		}
		else if (word[i] == '$')
		{
			i = get_len_w_d(word, i);
			len++
		}
		else
		{
			while (word[i] && word[i] != '$')
				i++;
			len++;
		}
	}
	return (len);
}

char	*expand_word(t_init *param, char *word, t_env *env)
{
	int	len;
	char	**inputs;

	len = input_len(word);
	inputs = ft_calloc(len + 1, sizeof(char *));
	if (!inputs)
		return (NULL);
	inputs = expand_to_tab(param, word, env);
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
