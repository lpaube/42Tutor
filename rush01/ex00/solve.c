/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 11:48:42 by laube             #+#    #+#             */
/*   Updated: 2021/08/04 12:56:40 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	no_dup(int **board, int dim, int col, int row)
{
	int	i;

	i = 0;
	while (i < dim)
	{
		if (board[i][col] == board[row][col] && i != row)
			return (0);
		i++;
	}
	i = 0;
	while (i < dim)
	{
		if (board[row][i] == board[row][col] && i != col)
			return (0);
		i++;
	}
	return (1);
}

int	backtrace(int **board, int *row, int *col, int dim)
{
	if (row == 0 && col == 0)
		return (-1);
	board[*row][*col] = 0;
	if (*col == 0)
	{
		(*row)--;
		*col = dim - 1;
	}
	else
		(*col)--;
	board[*row][*col]++;
	return (0);
}

int	solve_it(int **board, int **rules_tab, int dim)
{
	int	col;
	int	row;

	col = 0;
	row = 0;
	while (test_rules(board, rules_tab, dim, row * dim + col) != 2)
	{
		if (board[row][col] > dim)
		{
			if (backtrace(board, &row, &col, dim) == -1)
				return (-1);
		}
		else if (test_rules(board, rules_tab, dim, row * dim + col) == 0)
			board[row][col]++;
		else
		{
			if (++col >= dim)
			{
				row++;
				col = 0;
			}
		}
	}
	return (0);
}
