/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 17:45:23 by laube             #+#    #+#             */
/*   Updated: 2021/08/04 13:17:17 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

int	ft_error(void)
{
	ft_putstr("Error");
	ft_putchar('\n');
	return (-1);
}

void	free_table(int ***table, int dim)
{
	int	i;

	i = 0;
	while (i < dim)
	{
		free((*table)[i]);
		i++;
	}
	free(*table);
}

int	main(int argc, char **argv)
{
	int	dim;
	int	**board;
	int	**rules_tab;

	if (argc != 2)
		return (ft_error());
	dim = get_dim(argv[1]);
	if (dim == -1)
		return (ft_error());
	board = init_board(dim);
	rules_tab = init_rules(argv[1], dim);
	if (rules_tab == 0 || solve_it(board, rules_tab, dim) == -1)
	{
		free_table(&board, dim);
		return (ft_error());
	}
	print_board(board, dim);
	free_table(&rules_tab, dim);
	free_table(&board, dim);
	return (0);
}
