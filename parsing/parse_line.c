/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:08:09 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/06 17:46:01 by tcybak           ###   ########.fr       */
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

// int	ft_verif_redirect(t_init *param, t_list_char *lst)
// {
// 	int	j;
// 	int	len;
// 	t_list_char	*tmp;
	
// 	tmp = lst;
// 	while (tmp->next != NULL)
// 	{
// 		tmp = tmp->next;
// 	}
// 		j = 0;
// 		len = ft_strlen(tmp->cmd[0]);
// 		while (tmp->cmd[0][j] == '<' || tmp->cmd[0][j] == '>')
// 			j++;
// 		// printf("HERE = %c j = %d\n", tmp->cmd[0][j - 1],j);
// 		if (j - 1 >= 0 && ((tmp->cmd[0][j - 1] == '<' && j <= 3) || (tmp->cmd[0][j - 1] == '>' && j < 2)))
// 		{
// 			write(2, "syntax error near unexpected token `newline'\n", 45);
// 			param->status = 2;
// 			return (1);
// 		}
// 		else if (j - 1 >= 0 && ((tmp->cmd[0][j - 1] == '<' && j == 4) || (tmp->cmd[0][j - 1] == '>' && j == 3)))
// 		{
// 			write(2, "syntax error near unexpected token `", 37);
// 			write(2, &(tmp->cmd[0][j - 1]), 1);
// 			write(2, "'\n", 2);
// 			param->status = 2;
// 			return (1);
// 		}
// 		else if (j - 1 >= 0 && j > 3 && (tmp->cmd[0][j - 1] == '>'))
// 		{
// 			write(2, "syntax error near unexpected token `>>'\n", 40);
// 			param->status = 2;
// 			return (1);
// 		}
// 		else if (j - 1 >= 0 && j > 4 && (tmp->cmd[0][j - 1] == '<'))
// 		{
// 			write(2, "syntax error near unexpected token `<<'\n", 40);
// 			param->status = 2;
// 			return (1);
// 		}
// 	return (0);
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
	// if (ft_verif_redirect(param, param->tok))
	// 	return ;
	get_funct(param, param->tok);
	get_no_red(param->tok);
	tmp = param->tok;
	while(tmp)
	{
		ft_supp_quote(tmp->cmd);
		ft_supp_quote(tmp->no_red);
		tmp = tmp->next;
	}
	get_in_out(param->tok);
	get_nb_eof(param->tok);
	tmp = param->tok;
	// print_lst_char(param->tok);
	while (tmp)
	{
		exec_heredoc(tmp, tmp->heredoc, param->lst_env);
		tmp = tmp->next;
	}
	if (!param->tok)
		return ;
	exec(param);
}
