/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:35:17 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/29 15:59:27 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_print_arg(int *n, int *i, t_list_char *tok)
{
	if ((*n) == 1 && tok->no_red[(*i)])
	{
		while (tok->no_red[(*i)] && tok->no_red[(*i) + 1])
		{
			printf("%s ", tok->no_red[(*i)]);
			(*i)++;
		}
		printf("%s", tok->no_red[(*i)]);
	}
	else if ((*n) != 1 && tok->no_red[(*i)])
	{
		while (tok->no_red[(*i)] && tok->no_red[(*i) + 1])
		{
			printf("%s ", tok->no_red[(*i)]);
			(*i)++;
		}
		printf("%s\n", tok->no_red[(*i)]);
	}
}

int	ft_echo_option(t_list_char *tok, int *i, int *n)
{
	int	j;

	while (tok->no_red[(*i)] && ((!ft_strcmp(tok->no_red[(*i)], "-n"))
			|| (tok->no_red[(*i)][0] == '-' && tok->no_red[(*i)][1] == 'n')))
	{
		j = 1;
		while (tok->no_red[(*i)][j])
		{
			if (tok->no_red[(*i)][j] != 'n')
			{
				ft_print_arg(n, i, tok);
				return (0);
			}
			j++;
		}
		(*i)++;
		(*n) = 1;
	}
	return (1);
}

void	ft_echo(t_init *param, t_list_char *tok)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (ft_strcmp("echo", tok->no_red[i]) && tok->no_red[i] != NULL)
		i++;
	if (tok->no_red[i + 1] == NULL)
	{
		printf("\n");
		return ;
	}
	while (ft_strlen(tok->no_red[i]) <= 0 || ft_strcmp(tok->no_red[i], "echo"))
		i++;
	i++;
	if (ft_echo_option(tok, &i, &n) == 0)
		return ;
	param->status = 0;
	ft_print_arg(&n, &i, tok);
}
