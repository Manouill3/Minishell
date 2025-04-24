/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:14:17 by tcybak            #+#    #+#             */
/*   Updated: 2025/04/24 14:25:34 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_add_export_only(t_init *param, t_list_char *tok, t_env *tmp_exp)
{
	ft_lstadd_back_env(&param->lst_export, ft_lstnew_env(ft_strdup(tok->cmd[1])));
	while (tmp_exp->next != NULL)
		tmp_exp = tmp_exp->next;
	get_name_env(tmp_exp);
	get_final_cont(tmp_exp);
	tmp_exp->exp = 1;
	return ;
}

int		ft_add_value_var(t_init *param, int i, t_list_char *tok)
{
	int	len;
	char	*add;
	char	*name;
	char	*tmp;
	t_env 	*tmp_env;
	t_env	*tmp_exp;

	tmp_env = param->lst_env;
	tmp_exp = param->lst_export;
	tmp = NULL;
	len = ft_strlen(tok->cmd[1]) - i;
	add = ft_substr(tok->cmd[1], i, len);
	name = ft_substr(tok->cmd[1], 0, (i - 2));
	printf("len = %d\n add = %s\n name = %s\n", len, add, name);
	while (tmp_env)
	{
		if (!ft_strcmp(name, tmp_env->name))
		{
			tmp = ft_strjoin(tmp_env->cont, add);
			free(tmp_env->cont);
			tmp_env->cont = NULL;
			tmp_env->cont = tmp;
			while(ft_strcmp(name, tmp_exp->name))
				tmp_exp = tmp_exp->next;
			if (!ft_strcmp(name, tmp_exp->name))
			{
				tmp = ft_strjoin(tmp_exp->cont, add);
				free(tmp_exp->cont);
				tmp_exp->cont = NULL;
				tmp_exp->cont = tmp;
			}
			free(add);
			free(name);
			return (0);
		}
		tmp_env = tmp_env->next;
	}
	tmp_env = param->lst_env;
	while (tmp_exp)
	{
			if (!ft_strcmp(name, tmp_exp->name))
			{
				ft_lstadd_back_env(&param->lst_env, ft_lstnew_env(ft_strdup(tok->cmd[1])));
				while (tmp_env->next != NULL)
					tmp_env = tmp_env->next;
				get_name_env_more(tmp_env);
				get_final_cont_more(tmp_env);
				if (!add)
					tmp_exp->exp = 0;
				else
				{
					tmp = ft_strjoin(tmp_exp->cont, add);
					free(tmp_exp->cont);
					tmp_exp->cont = NULL;
					tmp_exp->cont = tmp;
				}
				free(add);
				free(name);
				return (0);
			}
		tmp_exp = tmp_exp->next;
	}
	printf("HERE\n");
	tmp_env = NULL;
	tmp_exp = NULL;
	tmp_env = param->lst_env;
	tmp_exp = param->lst_export;
	ft_lstadd_back_env(&param->lst_env, ft_lstnew_env(ft_strdup(tok->cmd[1])));
	ft_lstadd_back_env(&param->lst_export, ft_lstnew_env(ft_strdup(tok->cmd[1])));
	while (tmp_exp->next != NULL)
		tmp_exp = tmp_exp->next;
	while (tmp_env->next != NULL)
		tmp_env = tmp_env->next;
	get_name_env_more(tmp_env);
	get_final_cont_more(tmp_env);
	get_name_env_more(tmp_exp);
	get_final_cont_more(tmp_exp);
	free(add);
	free(name);
	return (0);
}

int		ft_continue_value(t_init *param, t_list_char *tok)
{
	int	i;

	i = 1;
	while((tok->cmd[1][i] != '=' && tok->cmd[1][i]))
	{
		if (tok->cmd[1][i] == '+' && tok->cmd[1][i + 1] == '=')
		{
			printf("NOTHERE");
			i = i + 2;
			ft_add_value_var(param, i, tok);
			return (0);
		}
		if (ft_isalnum(tok->cmd[1][i]) == 0)
		{
			perror("export identifier");
			return (0);
		}
		i++;
	}
	return (1);
	
}

void	ft_create_add_back(t_init *param, t_list_char *tok, t_env *tmp_exp, int exist)
{
	t_env	*tmp_env;

	tmp_env = param->lst_env;
	if (exist != 1)
	{
		ft_lstadd_back_env(&param->lst_export, ft_lstnew_env(ft_strdup(tok->cmd[1])));
		while (tmp_exp->next != NULL)
		tmp_exp = tmp_exp->next;
		get_name_env(tmp_exp);
		get_final_cont(tmp_exp);
	}
	ft_lstadd_back_env(&param->lst_env, ft_lstnew_env(ft_strdup(tok->cmd[1])));
	while (tmp_env->next != NULL)
		tmp_env = tmp_env->next;
	get_name_env(tmp_env);
	get_final_cont(tmp_env);
}

void	ft_create_var(t_init *param, t_list_char *tok, t_env *tmp_exp)
{
	int	i;
	int	j;
	int	len_const;
	int	exist;
	int	create;
	t_env	*tmp_env;
	char	*name;
	char	*new_const;

	i = 1;
	create = 0;
	len_const = 0;
	exist = 0;
	tmp_env = param->lst_env;
	printf("Create = %d\n", create);
	while(tok->cmd[1][i] != '=' && tok->cmd[1][i])
	{
		if (ft_isalnum(tok->cmd[1][i]) == 0)
		{
			perror("export identifier");
			return ;
		}
		i++;
	}
	name = ft_substr(tok->cmd[1], 0, (i));
	while (tmp_env)
	{
		// printf("tmp_env->name = %s, name = %s\n", tmp_env->name, name);
		if (!ft_strcmp(tmp_env->name, name))
		{
			create = 1;
			break;
		}
		tmp_env = tmp_env->next;
	}
	if (create == 0 && tok->cmd[1][i] == '=')
		create = 2;
	printf("Create = %d\n", create);
	while (tmp_exp)
	{
		if (!ft_strcmp(tmp_exp->name, name))
			exist = 1;
		if (!ft_strcmp(tmp_exp->name, name) && create == 1 && tok->cmd[1][i] != '=')
		{
			printf("HERE1\n");
			tmp_exp->exp = 0;
			if (create != 2)
			{
				free(name);
				return ;
			}
		}
		if (!ft_strcmp(tmp_exp->name, name) && tok->cmd[1][i] != '=')
		{
			printf("HERE2\n");
			tmp_exp->exp = 1;
			if (create != 2)
			{
				free(name);
				return ;
			}
		}
		if (!ft_strcmp(tmp_exp->name, name) && tok->cmd[1][i] == '=')
		{
			printf("HERE3\n");
			i++;
			j = i;
			while (tok->cmd[1][i])
			{
					len_const++;
					i++;
			}
			new_const = ft_calloc(len_const + 1,sizeof(char));
			if (!new_const)
			{
				new_const = NULL;
				tmp_exp->cont = NULL;
				if (create == 1)
					tmp_env->cont = NULL;
			}
			if (new_const)
			{
				i = 0;
				while (tok->cmd[1][j])
				{
					new_const[i] = tok->cmd[1][j];
					i++;
					j++;
				}
				free(tmp_exp->cont);
				tmp_exp->cont = NULL;
				tmp_exp->cont = ft_strdup(new_const);
				if (create == 1)
				{
					free(tmp_env->cont);
					tmp_env->cont = NULL;
					tmp_env->cont = ft_strdup(new_const);
				}
				tmp_exp->exp = 0;
				free(new_const);
			}
			if (create != 2)
			{
				free(name);
				return ;
			}
		}
		tmp_exp = tmp_exp->next;
	}
	tmp_env = param->lst_env;
	tmp_exp = param->lst_export;
	if (create == 2)
		ft_create_add_back(param, tok, tmp_exp, exist);
	else
		ft_add_export_only(param, tok, tmp_exp);
	free(name);
}

void    ft_export(t_init *param, t_list_char *tok)
{
	int	verif;
	t_env *tmp_exp;

	verif = 0;
	tmp_exp = param->lst_export;
	if (tok->cmd[1] == NULL)
	{
		while(tmp_exp)
		{
			printf("declare -x ");
			if (tmp_exp->cont[0] == '\0' && tmp_exp->exp == 1)
				printf("%s\n", tmp_exp->name);
			else
			{
				printf("%s=", tmp_exp->name);
				printf("\"%s\"\n",tmp_exp->cont);
			}
			tmp_exp = tmp_exp->next;
		}
		return ;
	}
	if (ft_isalpha(tok->cmd[1][0]) || tok->cmd[1][0] == '_')
	{
		verif = ft_continue_value(param, tok);
		if (verif == 1)
			ft_create_var(param, tok, tmp_exp);
		return ;
	}
	else
		perror("export identifier");
}

