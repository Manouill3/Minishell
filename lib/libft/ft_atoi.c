/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:51:03 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/13 11:39:02 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

uint8_t	ft_atoi(const char *nptr)
{
	int							i;
	unsigned long long			nb;
	int							sign;

	sign = 1;
	nb = 0;
	i = 0;
	while ((nptr[i] > 8 && nptr[i] < 14) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - '0');
		if ((sign == 1 && nb > 9223372036854775807ULL)
			|| (sign == -1 && nb > 9223372036854775808ULL))
			return (2);
		i++;
	}
	return ((uint8_t)nb * sign);
}
