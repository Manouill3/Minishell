/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:05:45 by mdegache          #+#    #+#             */
/*   Updated: 2025/03/13 15:46:57 by tcybak           ###   ########.fr       */
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


char	*ft_expand(t_init *init)
{
	int	i;
	char	*content;
	char	*res;
	char	*data;
	t_list_char	*tmp_env;
	char	*tmp_data;

	i = 0;
	data = NULL;
	content = init->tab[init->i];
	tmp_env  = init->env;
	if (ft_strchr(content, '$'))
	{
		if ((content && content[0] == content[ft_strlen(content) - 1]
			&& content[0] == '"') ||
				content[0] != 39)
		{
			tmp_data = data;
			data = quote_out(content, '"');
			free(tmp_data);
			tmp_data = NULL;
			if (data[0] == 39)
			{
				res = expand_quote(tmp_env, data);
				return (res);
			}
			if (data[0] != '$')
			{
				free(data);
				return (ft_strdup(content));
			}
			tmp_data = data;
			data = quote_out(data, '$');
			free(tmp_data);
			tmp_data = NULL;
			while (tmp_env && ft_strcmp(data, tmp_env->data))
				tmp_env = tmp_env->next;
			free(data);
			if (!tmp_env)
				return(ft_strdup(content));
			while (tmp_env && tmp_env->data[i] && tmp_env->data[i] != '=')
				i++;
			res = ft_substr(tmp_env->data, i + 1, ft_strlen(tmp_env->data) - i + 1);
			return (res);
		}
	}
	
	return (ft_strdup(content));	
}
