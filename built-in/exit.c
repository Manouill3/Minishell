/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:24:13 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/15 15:15:40 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_verif_nb(t_init *param)
{
	int	i;

	i = 0;
	while (param->tok->cmd[1][i])
	{
		if (!((param->tok->cmd[1][i] >= 48 && param->tok->cmd[1][i] <= 57)
			|| param->tok->cmd[1][i] == '+' || param->tok->cmd[1][i] == '-'))
		{
			param->status = 2;
			write(2, " numeric argument required\n", 27);
			// ft_putstr_fd("exit", 2);
			exit(param->status);
		}
		i++;
	}
	param->status = ft_atoi(param->tok->cmd[1]);
}

int	ft_free_param(t_init *param, int nb_arg)
{
	ft_verif_nb(param);
	if (param->status == 2)
		write(2, " numeric argument required\n", 27);
	nb_arg = param->status;
	ft_free_all(param);
	free_struct(param);
	return (nb_arg);
}

void	ft_exit(t_init *param)
{
	int	nb_arg;
	int	i;

	i = 0;
	nb_arg = 0;
	while (param->tok->cmd[i])
	{
		nb_arg++;
		i++;
	}
	if (nb_arg == 1)
		exit(param->status);
	if (nb_arg > 2)
	{
		ft_verif_nb(param);
		param->status = 1;
		write(2, " too many arguments\n", 20);
		return ;
	}
	nb_arg = ft_free_param(param, nb_arg);
	ft_putstr_fd("exit\n", 2);
	exit(nb_arg);
}
