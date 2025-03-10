/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:00:13 by mdegache          #+#    #+#             */
/*   Updated: 2024/12/05 21:25:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int i)
{
	if (!((i > 64 && i < 91) || (i > 96 && i < 123)))
		return (0);
	return (1024);
}
