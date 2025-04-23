/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_res.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:55:11 by mdegache          #+#    #+#             */
/*   Updated: 2025/04/23 14:21:16 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int final_len(char **inputs, int l)
{
    int i;
    int j;
    int len;

    i = 0;
    len = 0;
    while (i < l)
    {
        j = 0;
        while (j < (int)ft_strlen(inputs[i]))
        {
            j++;
            len++;
        }
        i++;
    }
    return (len);
}
