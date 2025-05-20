/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:49:48 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/20 10:02:31 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_good(t_init *param, char *path, int good, char *old_path)
{
	if (good == 0)
		ft_error(param, path, old_path);
	else if (good == 1)
		ft_modif_pwd(param, old_path);
}
