/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 09:27:48 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/19 09:48:25 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void    min_env(t_init *param)
{
    t_env   *env;
    t_env   *env_ex;
    
    ft_lstadd_back_env(&param->lst_env, ft_lstnew_env(getcwd(NULL, 0)));
		ft_lstadd_back_env(&param->lst_export,
				ft_lstnew_env(getcwd(NULL, 0)));
    env = param->lst_env;
    env_ex = param->lst_export;
    env->name = ft_calloc(4, sizeof(char));
    if (!env->name)
            return ;
    env_ex->name = ft_calloc(4, sizeof(char));
    if (!env_ex->name)
            return ;
    env->name[0] = 'P';
    env->name[1] = 'W';
    env->name[2] = 'D';
    env_ex->name[0] = 'P';
    env_ex->name[1] = 'W';
    env_ex->name[2] = 'D';
}
