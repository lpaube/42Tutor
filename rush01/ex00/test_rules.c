/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_rules.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 11:44:54 by laube             #+#    #+#             */
/*   Updated: 2021/08/04 12:54:46 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	test_left(int **board, int **rules_tab, int dim, int row)
{
	int	i;
	int	max_height;
	int	seen_left;

	seen_left = 0;
	max_height = 0;
	i = 0;
	while (i < dim)
	{
		if (board[row][i] > max_height)
		{
			seen_left++;
			max_height = board[row][i];
		}
		i++;
	}
	if (seen_left > rules_tab[2][row])
		return (0);
	if (board[row][dim - 1] != 0 && seen_left != rules_tab[2][row])
		return (0);
	return (1);
}

int	test_right(int **board, int **rules_tab, int dim, int row)
{
	int	i;
	int	max_height;
	int	seen_right;

	if (board[row][dim - 1] == 0)
		return (1);
	seen_right = 0;
	max_height = 0;
	i = dim - 1;
	while (i >= 0)
	{
		if (board[row][i] > max_height)
		{
			seen_right++;
			max_height = board[row][i];
		}
		i--;
	}
	if (seen_right != rules_tab[3][row])
		return (0);
	return (1);
}

int	test_top(int **board, int **rules_tab, int dim, int col)
{
	int	i;
	int	max_height;
	int	seen_top;

	seen_top = 0;
	max_height = 0;
	i = 0;
	while (i < dim)
	{
		if (board[i][col] > max_height)
		{
			seen_top++;
			max_height = board[i][col];
		}
		i++;
	}
	if (seen_top > rules_tab[0][col])
		return (0);
	if (board[dim - 1][col] != 0 && seen_top != rules_tab[0][col])
		return (0);
	return (1);
}

int	test_bottom(int **board, int **rules_tab, int dim, int col)
{
	int	i;
	int	max_height;
	int	seen_bottom;

	if (board[dim - 1][col] == 0)
		return (1);
	seen_bottom = 0;
	max_height = 0;
	i = dim - 1;
	while (i >= 0)
	{
		if (board[i][col] > max_height)
		{
			seen_bottom++;
			max_height = board[i][col];
		}
		i--;
	}
	if (seen_bottom != rules_tab[1][col])
		return (0);
	return (1);
}

/*
	Returns 0 if does not pass rules; 1 if pass rules; 
	2 if pass rules and board full
*/
int	test_rules(int **board, int **rules_tab, int dim, int pos)
{
	int	col;
	int	row;
	int	i;

	(void)rules_tab;
	row = pos / dim;
	col = pos - row * dim;
	i = 0;
	if (board[row][col] == 0)
		return (0);
	if (no_dup(board, dim, col, row) == 0)
		return (0);
	if (test_left(board, rules_tab, dim, row) == 0)
		return (0);
	if (test_right(board, rules_tab, dim, row) == 0)
		return (0);
	if (test_top(board, rules_tab, dim, col) == 0)
		return (0);
	if (test_bottom(board, rules_tab, dim, col) == 0)
		return (0);
	if (col == dim - 1 && row == dim - 1 && board[row][col] != 0)
		return (2);
	return (1);
}
