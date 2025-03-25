/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:05:45 by mdegache          #+#    #+#             */
/*   Updated: 2025/03/25 18:07:22 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	*all_quote_out(char *content)
{
	char	*data;
	char	*tmp_data;

	data = ft_strdup(content);
	tmp_data = data;
	data = quote_out(data, 39);
	free(tmp_data);
	tmp_data = NULL;
	tmp_data = data;
	data = quote_out(data, '"');
	free(tmp_data);
	tmp_data = NULL;
	return (data);
}

char	*quote_out(char *cont, char quote)
{
	int		i;
	int		j;
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

char	*expand_now(t_init *init, char *data, char *content, int i)
{
	t_list_char *tmp_env;
	char	*res;

	tmp_env = init->env;
	init->tmp_data = data;
	data = quote_out(data, '$');
	free(init->tmp_data);
	while (tmp_env && ft_strcmp(data, tmp_env->data))
		tmp_env = tmp_env->next;
	free(data);
	if (!tmp_env)
		return (ft_strdup(content));
	while (tmp_env && tmp_env->data[i] && tmp_env->data[i] != '=')
		i++;
	res = ft_substr(tmp_env->data, i + 1, ft_strlen(tmp_env->data) - i + 1);
	return (res);
}

char	*ft_expand_arg(t_init *init, char *data, char *content, int i)
{
	char	*res;
	
	if (init->i > 0 && ft_strcmp(init->tab[init->i - 1], "<<"))
		return(content);
	if (content[0] != content[ft_strlen(content) - 1])
	{
		data = all_quote_out(content);
		res = expand_now(init, data, content, i);
		return (res);
	}
	if(content[0] == 39)
		return(ft_strdup(content));
	if (content[0] == '"')
	{
		data = all_quote_out(content);
		res = expand_now(init, data, content, i);
		return (res);
	}
	res = expand_now(init, data, content, i);
	return (res);
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
	if (!ft_strchr(content, '$'))
		return (ft_strdup(content));
	return(ft_expand_arg(init, data, content, i));
}
