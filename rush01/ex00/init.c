/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 11:43:28 by laube             #+#    #+#             */
/*   Updated: 2021/08/04 13:17:36 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	get_dim(char *str)
{
	int	counter;

	counter = 0;
	while (*str)
	{
		while ((*str >= 9 && *str <= 13) || *str == 32)
			str++;
		if (!((*str >= 9 && *str <= 13) || *str == 32))
		{
			counter++;
			while (!((*str >= 9 && *str <= 13) || *str == 32) && *str)
				str++;
		}
	}
	if (counter % 4 != 0 || counter == 0)
		return (-1);
	return (counter / 4);
}

int	**destroy_rules(int ***rules_tab, int iter)
{
	int	i;

	i = 0;
	while (i <= iter)
	{
		free((*rules_tab)[i]);
		i++;
	}
	free(*rules_tab);
	return (0);
}

int	**init_rules(char *rules, int dim)
{
	int	**rules_tab;
	int	i;
	int	j;

	i = 0;
	rules_tab = malloc(sizeof(*rules_tab) * dim);
	while (i < dim)
	{
		rules_tab[i] = malloc(sizeof(**rules_tab) * dim);
		j = 0;
		while (j < dim)
		{
			if (!(ft_atoi(rules) >= 0 && ft_atoi(rules) <= dim))
				return (destroy_rules(&rules_tab, i));
			rules_tab[i][j] = ft_atoi(rules);
			while (!((*rules >= 9 && *rules <= 13) || *rules == 32) && *rules)
				rules++;
			while (((*rules >= 9 && *rules <= 13) || *rules == 32) && *rules)
				rules++;
			j++;
		}
		i++;
	}
	return (rules_tab);
}

int	**init_board(int dim)
{
	int		**board;
	int		i;
	int		j;

	i = 0;
	board = malloc(sizeof(*board) * dim);
	while (i < dim)
	{
		board[i] = malloc(sizeof(**board) * dim);
		j = 0;
		while (j < dim)
		{
			board[i][j] = 0;
			j++;
		}
		i++;
	}
	return (board);
}
