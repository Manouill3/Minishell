/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:46:56 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/24 22:25:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

// void	ft_free_env(char *add, char *name)
// {
// 	free(add);
// 	free(name);
// }

void	env_content(t_env *env, char *add, t_mal *mal)
{
	char	*tmp;

	tmp = ft_strjoin(env->cont, add, mal);
	// free(env->cont);
	env->cont = tmp;
}

void	export_content(t_env *exp, char *add, t_mal *mal)
{
	char	*tmp;

	tmp = ft_strjoin(exp->cont, add, mal);
	// free(exp->cont);
	exp->cont = tmp;
}
