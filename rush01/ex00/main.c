/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 17:45:23 by laube             #+#    #+#             */
/*   Updated: 2021/08/03 00:10:54 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

#include <stdio.h>

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
	int	**board;
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
	return (ft_sqroot(counter));
}

// Returns 0 if does not pass rules; 1 if pass rules; 2 if pass rules and board full
int	pass_rules(int **board, int **rules_tab, int dim, int pos)
{
	int	col;
	int	row;
	int	i;

	row = pos / dim;
	col = pos - row * dim;

}

int	solve_it(int **board, int **rules_tab, int dim)
{
	int	col;
	int	row;

	col = 0;
	row = 0;
	while (pass_rules(board, rules_tab, dim, row * dim + col) != 2)
	{
		if (pass_rules(board, rules_tab, dim, row * dim + col) == 0)
			board[curr_row][curr_col]++;
		if (board[curr_row][curr_col] > dim)
		{
			board[curr_row][curr_col] = 0;
			if (curr_col == 3)
			{
				curr_row--;
				curr_col = 0;
			}
		}
	}
}

int	main(int argc, char **argv)
{
	int	dim;
	int **board;
	int **rules_tab;

	if (argc != 2)
	{
		ft_putstr("Error");
		ft_putchar('\n');
	}
	dim = get_dim(argv[1]);
	printf("argc: %d | dim: %d\n", argc, dim);
	board = init_board(dim);
	rules_tab = init_rules(argv[1], dim);
	solve_it(board, rules_tab, dim);
}
