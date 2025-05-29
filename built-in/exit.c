/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:24:13 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/29 11:45:36 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_verif_nb(t_init *param, t_list_char *tok)
{
	int	i;
	int	status;

	i = 0;
	while (tok->cmd[1][i] && is_white(tok->cmd[1][i]))
		i++;
	while (tok->cmd[1][i])
	{
		if (!((tok->cmd[1][i] >= 48 && tok->cmd[1][i] <= 57)
			|| ((tok->cmd[1][i] == '+' || tok->cmd[1][i] == '-')
			&& (tok->cmd[1][i + 1] >= 48
			&& tok->cmd[1][i + 1] <= 57))))
		{
			param->status = 2;
			write(2, "numeric argument required\n", 27);
			status = param->status;
			ft_lstclear_mal(&param->mal);
			exit(status);
		}
		i++;
	}
	param->status = ft_atoi(tok->cmd[1]);
}

int	ft_free_param(t_init *param, int nb_arg, t_list_char *tok)
{
	ft_verif_nb(param, tok);
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
}

void	ft_exit(t_init *param, t_list_char *tok)
{
	int			nb_arg;
	int			i;
	t_list_char	*tmp;

	i = 0;
	nb_arg = 0;
	tmp = tok;
	while (tmp->cmd[i])
	{
		nb_arg++;
		i++;
	}
	check_exit_arg(param, nb_arg);
	if (nb_arg > 2)
	{
		ft_verif_nb(param, tmp);
		param->status = 1;
		write(2, "too many arguments\n", 20);
		return ;
	}
	nb_arg = ft_free_param(param, nb_arg, tok);
	exit(nb_arg);
}
