/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 08:17:50 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/23 10:53:01 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	count_quote(char *input)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (input[i])
	{
		if (input[i] == 39 || input[i] == '"')
			len++;
		i++;
	}
	return (len);
}

char	*change_to_var(char *input, t_env *env)
{
	int		i;
	int		j;
	int		len;
	char	*res;

	i = 0;
	j = 0;
	len = ft_strlen(env->cont) + count_quote(input);
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (input[i] == 39 || input[i] == '"')
		res[j++] = input[i++];
	i = 0;
	while (env->cont[i])
		res[j++] = env->cont[i++];
	i = 0;
	while (input[i] == 39 || input[i] == '"')
		res[j++] = input[i++];
	return (res);
}

char	*exp_heredoc(char *input, t_env *env, t_mal *mal)
{
	char	*res;
	char	*word;
	char	*no_quote;
	t_env	*tmp_env;

	tmp_env = env;
	word = char_out(input, '$', mal);
	no_quote = all_quote_out(word, mal);
	while (tmp_env && ft_strcmp(tmp_env->name, no_quote))
		tmp_env = tmp_env->next;
	if (!tmp_env)
		return (NULL);
	res = change_to_var(word, tmp_env);
	// free(word);
	// free(no_quote);
	return (res);
}
