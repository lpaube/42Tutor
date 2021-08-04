/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 17:44:43 by laube             #+#    #+#             */
/*   Updated: 2021/08/04 13:04:53 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdlib.h>
# include <unistd.h>

int		ft_atoi(char *str);
int		ft_strlen(char *str);
void	ft_putstr(char *str);
void	ft_putchar(char c);
void	ft_putnbr(int num);
int		get_dim(char *str);
int		**init_rules(char *rules, int dim);
int		**init_board(int dim);
int		test_rules(int **board, int **rules_tab, int dim, int pos);
int		no_dup(int **board, int dim, int col, int row);
int		solve_it(int **board, int **rules_tab, int dim);

#endif
