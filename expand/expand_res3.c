/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_res3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:33:56 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/09 15:21:09 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	*get_final_input(char *res, char **inputs, int len)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (i < len)
	{
		j = 0;
		while (j < (int)ft_strlen(inputs[i]))
			res[k++] = inputs[i][j++];
		i++;
	}
	return (res);
}

