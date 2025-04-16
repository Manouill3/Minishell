/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:27:05 by mdegache          #+#    #+#             */
/*   Updated: 2025/04/16 16:02:09 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	*get_actual_word(char *word, int i, int len, t_env *env)
{
	char	*sub_word;
	
	sub_word = ft_substr(word, len, i - len);
	if (!sub_word)
		return(NULL);
	
}

char	*expand_word(char *word, t_env *lst_env)
{
	int	i;
	int	len;
	char	*actual_word;
	char	*res;

	i = 0;
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
			while (word[i] && ft_isalnum(word[i]))
				i++; 
		}
		actual_word = get_actual_word(word, i, len, env);
		res = ft_strjoin(res, actual_word);
		free(get_actual_word);
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
					tmp->cmd[i] = expand_word(tmp->cmd[i], param->lst_env);
					free(tmp_free);
				}
			}
			i++;
		}
		tmp = tmp->next;
	}
}
