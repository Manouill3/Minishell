/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:46:56 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/12 15:48:31 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_free_env(char *add, char *name)
{
	free(add);
	free(name);
}

void	env_content(t_env *env, char *add)
{
	char	*tmp;

	tmp = ft_strjoin(env->cont, add);
	free(env->cont);
	env->cont = tmp;
}

void	export_content(t_env *exp, char *add)
{
	char	*tmp;

	tmp = ft_strjoin(exp->cont, add);
	free(exp->cont);
	exp->cont = tmp;
}
