/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:24:13 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/29 09:10:27 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_verif_nb(t_init *param)
{
	int	i;
	int	status;

	i = 0;
	while (param->tok->cmd[1][i] && is_white(param->tok->cmd[1][i]))
		i++;
	while (param->tok->cmd[1][i])
	{
		if (!((param->tok->cmd[1][i] >= 48 && param->tok->cmd[1][i] <= 57)
			|| ((param->tok->cmd[1][i] == '+' || param->tok->cmd[1][i] == '-')
			&& (param->tok->cmd[1][i + 1] >= 48
			&& param->tok->cmd[1][i + 1] <= 57))))
		{
			param->status = 2;
			write(2, "numeric argument required\n", 27);
			status = param->status;
			ft_lstclear_mal(&param->mal);
			exit(status);
		}
		i++;
	}
	param->status = ft_atoi(param->tok->cmd[1]);
}

int	ft_free_param(t_init *param, int nb_arg)
{
	ft_verif_nb(param);
	if (param->status == 2)
		write(2, "numeric argument required\n", 27);
	if (param->count_cmd == 1)
		ft_putstr_fd("exit\n", 2);
	nb_arg = param->status;
	ft_lstclear_mal(&param->mal);
	return (nb_arg);
}

void	check_exit_arg(t_init *param, int nb_arg)
{
	int	status;

	if (nb_arg == 1)
	{
		status = param->status;
		ft_lstclear_mal(&param->mal);
		exit(status);
	}
	if (nb_arg > 2)
	{
		ft_verif_nb(param);
		param->status = 1;
		write(2, "too many arguments\n", 20);
		status = param->status;
		ft_lstclear_mal(&param->mal);
		exit(status);
	}
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
	check_exit_arg(param, nb_arg);
	nb_arg = ft_free_param(param, nb_arg);
	exit(nb_arg);
}
