/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:05:45 by mdegache          #+#    #+#             */
/*   Updated: 2025/03/13 17:44:30 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	*quote_out(char *cont, char quote)
{
	int	i;
	int	j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_calloc(ft_strlen(cont) + 1, sizeof(char));
	while (cont[i])
	{
		if (cont[i] != quote)
		{
			tmp[j] = cont[i];
			j++;
		}
		i++;
	}
	return (tmp);
}

char	*get_quote_back(char *data, char quote)
{
	int	i;
	int	j;
	char *res;

	i = 0;
	j = 1;
	res = ft_calloc(ft_strlen(data) + 3, sizeof(char));
	res[0] = quote;
	while(data[i])
	{
		res[j] = data[i];
		i++;
		j++;
	}
	res[j] = quote;
	return (res);
}

char	*ft_expand_rest(t_init *init, char *data, char *content, int i)
{
	t_list_char	*tmp_env;

	tmp_env  = init->env;
	if (data[0] == 39)
		return (expand_quote(tmp_env, data));
	if (data[0] != '$')
	{
		free(data);
		return (ft_strdup(content));
	}
	init->tmp_data = data;
	data = quote_out(data, '$');
	free(init->tmp_data);
	while (tmp_env && ft_strcmp(data, tmp_env->data))
		tmp_env = tmp_env->next;
	free(data);
	if (!tmp_env)
		return(ft_strdup(content));
	while (tmp_env && tmp_env->data[i] && tmp_env->data[i] != '=')
		i++;
	return (ft_substr(tmp_env->data, i + 1, ft_strlen(tmp_env->data) - i + 1));
}

char	*ft_expand(t_init *init)
{
	int		i;
	char	*content;
	char	*data;

	i = 0;
	data = NULL;
	init->tmp_data = NULL;
	content = init->tab[init->i];
	if (ft_strchr(content, '$'))
	{
		if ((content && content[0] == content[ft_strlen(content) - 1]
			&& content[0] == '"') ||
				content[0] != 39)
		{
			init->tmp_data = data;
			data = quote_out(content, '"');
			free(init->tmp_data);
			init->tmp_data = NULL;
			return (ft_expand_rest(init, data, content, i));
		}
	}
	return (ft_strdup(content));	
}
