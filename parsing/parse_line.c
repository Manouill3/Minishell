/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:08:09 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/06 15:16:20 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_supp_quote(char **cmd)
{
	int	i;
	int	j;
	int	nb;
	char	*tmp;

	i = 0;
	nb = 0;
	while (cmd[nb])
		nb++;	
	while (i < nb)
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == 39 || cmd[i][j] == '"')
			{
				tmp = cmd[i];
				cmd[i] = char_out(cmd[i], cmd[i][j]);
				free(tmp);
				break ;
			}
			j++;
		}
		i++;
	}
}

// void	ft_verif_redirect(t_init *param, t_list_char *lst)
// {
// 	int	i;
// 	int	j;
// 	int	len;
// 	t_list_char	*tmp;
	
// 	tmp = lst;
// 	while (tmp)
// 	{
// 		i = 0;
// 		while (i < tmp->len_cmd)
// 		{
// 			j = 0;
// 			len = ft_strlen(tmp->cmd[i]);
// 			while (tmp->cmd[i][j] == '<' || tmp->cmd[i][j] == '>')
// 				j++;
// 			if (j - 1 >= 0 && j < 2 && !tmp->cmd[i + 1] && !tmp->cmd[i][j + 1] && (tmp->cmd[i][j - 1] == '<' || tmp->cmd[i][j - 1] == '>'))
// 			{
// 				write(2, "syntax error near unexpected token `newline'", 44);
// 				param->status = 2;
// 				return ;
// 			}
// 			else if (j - 1 >= 0 && j > 2 && !tmp->cmd[i + 1] && !tmp->cmd[i][j + 1] && (tmp->cmd[i][j - 1] == '<' || tmp->cmd[i][j - 1] == '>'))
// 			{
// 				write(2, "syntax error near unexpected token `>>'", 39);
// 				param->status = 2;
// 				return ;
// 			}
// 			i++;
// 		}
// 		tmp = tmp->next;
// 	}
// }

void	get_funct(t_init *param, t_list_char *lst)
{
	(void)param;
	int		i;
	t_list_char	*tmp;

	tmp = lst;
	while (tmp)
	{
		i = 0;
		while (i < tmp->len_cmd)
		{
			if (i > 0)
			{
				if (ft_strlen(tmp->cmd[i]) > 0 && is_red(tmp->cmd[i]) && is_red(tmp->cmd[i - 1]))
				{
					tmp->funct = ft_strdup(tmp->cmd[i]);
					break ;
				}
			}
			else
				if (ft_strlen(tmp->cmd[i]) > 0 && is_red(tmp->cmd[i]))
				{
					tmp->funct = ft_strdup(tmp->cmd[i]);
					break ;
				}
			i++;
		}
		tmp = tmp->next;
	}
}

void	parsing_line(t_init *param)
{
	t_list_char	*tmp;
	
	get_token(param);
	expand_arg(param);
	// ft_verif_redirect(param, param->tok);
	get_funct(param, param->tok);
	get_no_red(param->tok);
	tmp = param->tok;
	while(tmp)
	{
		ft_supp_quote(tmp->cmd);
		ft_supp_quote(tmp->no_red);
		tmp = tmp->next;
	}
	// print_lst_char(param->tok);
	get_in_out(param->tok);
	get_nb_eof(param->tok);
	tmp = param->tok;
	while (tmp)
	{
		exec_heredoc(tmp, tmp->heredoc, param->lst_env);
		tmp = tmp->next;
	}
	if (!param->tok)
		return ;
	exec(param);
}
