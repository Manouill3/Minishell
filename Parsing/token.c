/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:53:40 by tcybak            #+#    #+#             */
/*   Updated: 2025/03/12 14:50:26 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	print_lst(t_list_char *lst)
{
	t_list_char	*curr;

	curr = lst;
	while (curr)
	{
		printf("name : %s\n", curr->name);
		printf("data : %s\n", curr->data);
		curr = curr->next;
	}
}

void get_env(t_init *init, char **env)
{
	int	i;

	i = 0;;
	init->env = NULL;
	while (env[i])
	{
		ft_lstadd_back_char(&init->env, ft_lstnew_char(ft_strdup(env[i])));
		i++;
	}
}

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

char	*expand_quote(t_list_char *tmp, char *data)
{
	int	i;
	char *res;
	char *tmp_data;
	
	i = 0;
	tmp_data = data;
	data = quote_out(data, 39);
	free(tmp_data);
	tmp_data = NULL;
	if (data[0] != '$')
	{
		tmp_data = data;
		data = get_quote_back(data, 39);
		free(tmp_data);
		tmp_data = NULL;
		return (data);
	}
	tmp_data = data;
	data = quote_out(data, '$');
	free(tmp_data);
	tmp_data = NULL;
	while (tmp && ft_strcmp(data, tmp->data))
		tmp = tmp->next;
	if (!tmp)
	{
		tmp_data = data;
		data = get_quote_back(data, 39);
		free(tmp_data);
		tmp_data = NULL;
		return(data);
	}
	free(data);
	while (tmp && tmp->data[i] && tmp->data[i] != '=')
		i++;
	res = ft_substr(tmp->data, i + 1, ft_strlen(tmp->data) - i + 1);
	tmp_data = res;
	res = get_quote_back(res, 39);
	free(tmp_data);
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
				return (content);
			tmp_data = data;
			data = quote_out(data, '$');
			free(tmp_data);
			tmp_data = NULL;
			while (tmp_env && ft_strcmp(data, tmp_env->data))
				tmp_env = tmp_env->next;
			if (!tmp_env)
				return(content);
			while (tmp_env && tmp_env->data[i] && tmp_env->data[i] != '=')
				i++;
			res = ft_substr(tmp_env->data, i + 1, ft_strlen(tmp_env->data) - i + 1);
			return (res);
		}
	}
	return (content);	
}

void	ft_check_name(t_init *init)
{
	t_list_char *new_node;
	
	new_node = ft_lstnew_char(ft_expand(init));
	if (init->tab[init->i][0] == '<' || init->tab[init->i][0] == '>' || init->tab[init->i][0] == '|')
		new_node->name = "Operator";
	else if (init->tab[init->i][0] == '-')
		new_node->name = "flag";
	else if (init->i == 0 || init->tab[init->i - 1][0] == '|')
		new_node->name = "cmd";
	else
		new_node->name = "arg";
	ft_lstadd_back_char(&init->tok, new_node);
}

void    token(t_init *init)
{	
	init->tok = NULL;
	init->tab = ft_split(init->line);
	init->i = 0;
	while (init->tab[init->i])
	{
		ft_check_name(init);
		init->i++;
	}	
}

