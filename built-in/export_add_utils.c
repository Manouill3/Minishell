/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:46:56 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/27 15:08:34 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	env_content(t_env *env, char *add, t_mal *mal)
{
	char	*tmp;

	tmp = ft_strjoin(env->cont, add, mal);
	env->cont = tmp;
}

void	export_content(t_env *exp, char *add, t_mal *mal)
{
	char	*tmp;

	tmp = ft_strjoin(exp->cont, add, mal);
	exp->cont = tmp;
}
