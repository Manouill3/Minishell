/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:46:33 by tcybak            #+#    #+#             */
/*   Updated: 2025/03/13 18:02:40 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	*verif_simple_quote(char *tmp_data, char *data)
{
	tmp_data = data;
	data = get_quote_back(data, 39);
	free(tmp_data);
	tmp_data = NULL;
	return (data);
}

char	*ft_value_var(char *tmp_data, t_list_char *tmp, int i)
{
	char	*res;

	res = ft_substr(tmp->data, i + 1, ft_strlen(tmp->data) - i + 1);
	tmp_data = res;
	res = get_quote_back(res, 39);
	free(tmp_data);
	return (res);
}

char	*expand_quote(t_list_char *tmp, char *data)
{
	int		i;
	char	*tmp_data;

	i = 0;
	tmp_data = data;
	data = quote_out(data, 39);
	free(tmp_data);
	tmp_data = NULL;
	if (data[0] != '$')
		return (verif_simple_quote(tmp_data, data));
	tmp_data = data;
	data = quote_out(data, '$');
	free(tmp_data);
	tmp_data = NULL;
	while (tmp && ft_strcmp(data, tmp->data))
		tmp = tmp->next;
	if (!tmp)
		return (verif_simple_quote(tmp_data, data));
	free(data);
	while (tmp && tmp->data[i] && tmp->data[i] != '=')
		i++;
	return (ft_value_var(tmp_data, tmp, i));
}
