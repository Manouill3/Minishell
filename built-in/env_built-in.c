/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_built-in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:32:09 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/09 13:33:18 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		printf("%s=", tmp->name);
		printf("%s\n", tmp->cont);
		tmp = tmp->next;
	}
}
