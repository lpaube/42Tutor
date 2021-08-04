/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 17:45:23 by laube             #+#    #+#             */
/*   Updated: 2021/08/04 11:31:16 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


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
				return (0);
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
	if (counter % 4 != 0 || counter == 0)
		return (-1);
	return (counter / 4);
}

void	ft_putnbr(int num)
{
	if (num == -2147483648)
	{
		ft_putstr("-2147483648");
		return ;
	}
	if (num < 0)
	{
		ft_putchar('-');
		ft_putnbr(-num);
		return ;
	}
	else if (num >= 10)
	{
		ft_putnbr(num / 10);
	}
	ft_putchar((num % 10) + '0');
}

void	print_board(int **board, int dim)
{
	int	i;
	int	j;

	i = 0;
	while (i < dim)
	{
		j = 0;
		while (j < dim)
		{
			ft_putnbr(board[i][j]);
			if (j == dim - 1)
				ft_putchar('\n');
			else
				ft_putchar(' ');
			j++;
		}
		i++;
	}
}

int	no_dup(int **board, int dim, int col, int row)
{
	int	i;

	// Check col
	i = 0;
	while (i < dim)
	{
		if (i == row)
		{
			i++;
			continue ;
		}
		if (board[i][col] == board[row][col])
			return (0);
		i++;
	}
	// Check row
	i = 0;
	while (i < dim)
	{
		if (i == col)
		{
			i++;
			continue ;
		}
		if (board[row][i] == board[row][col])
			return (0);
		i++;
	}
	return (1);
}

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

// Returns 0 if does not pass rules; 1 if pass rules; 2 if pass rules and board full
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

int	solve_it(int **board, int **rules_tab, int dim)
{
	int	col;
	int	row;

	col = 0;
	row = 0;
	// NEED FIXING HERE!!!
	while (test_rules(board, rules_tab, dim, row * dim + col) != 2)
	{
		if (board[row][col] > dim)
		{
			if (row == 0 && col == 0)
				return (-1);
			board[row][col] = 0;
			if (col == 0)
			{
				row--;
				col = dim - 1;
			}
			else
			{
				col--;
			}
			board[row][col]++;
		}
		else if (test_rules(board, rules_tab, dim, row * dim + col) == 0)
		{
			board[row][col]++;
		}
		else
		{
			col++;
			if (col >= dim)
			{
				row++;
				col = 0;
			}
		}
	}
	return (0);
}

int	ft_error(void)
{
	ft_putstr("Error");
	ft_putchar('\n');
	return (-1);
}

int	main(int argc, char **argv)
{
	int	dim;
	int **board;
	int **rules_tab;

	if (argc != 2)
		return ft_error();
	dim = get_dim(argv[1]);
	if (dim == -1)
		return (ft_error());
	board = init_board(dim);
	rules_tab = init_rules(argv[1], dim);
	if (rules_tab == 0)
		return (ft_error());
	if (solve_it(board, rules_tab, dim) == -1)
		return (ft_error());
	print_board(board, dim);
}
