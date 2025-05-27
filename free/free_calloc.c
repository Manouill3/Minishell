/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_calloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:52:08 by marvin            #+#    #+#             */
/*   Updated: 2025/05/21 18:52:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	*add_calloc(t_mal *mal, size_t size, size_t sizeb)
{
	void	*tmp;
	t_mal	*new;

	tmp = ft_calloc(size, sizeb);
	if (!tmp)
	{
		ft_lstclear_mal(&mal);
		exit (1);
	}
	new = ft_lstnew_mal(tmp);
	if (!new)
	{
		ft_lstclear_mal(&mal);
		exit (1);
	}
	ft_lstadd_back_mal(&mal, new);
	return (tmp);
}
