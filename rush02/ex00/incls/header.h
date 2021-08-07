/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 22:50:30 by laube             #+#    #+#             */
/*   Updated: 2021/08/06 22:57:54 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

void	ft_putchar(char c);
int		ft_strlen(char *str);
void	ft_putstr(char *str);
int		ft_atoi(const char *str);
int		ft_error(char *str);
void	dict_control(char *path, int *full_key, int thousands, int *spc_state);
void	read_dict(char *path, int part_key, int thousands);
int		print_value(char *buff, int key);
int		get_line_bytes(int tmp_fd);

#endif
