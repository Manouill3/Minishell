/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exp_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:24:26 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/19 16:53:38 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	white_or_not(char *s)
{
	if (ft_strchr(s, 9))
		return (1);
	if (ft_strchr(s, 10))
		return (1);
	if (ft_strchr(s, 11))
		return (1);
	if (ft_strchr(s, 12))
		return (1);
	if (ft_strchr(s, 13))
		return (1);
	if (ft_strchr(s, 32))
		return (1);
	return (0);
}
