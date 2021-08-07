/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dict.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 22:46:48 by laube             #+#    #+#             */
/*   Updated: 2021/08/06 22:57:04 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/header.h"

int	parse_dict(char *path, int key)
{
	int		tmp_fd;
	int		fd;
	int		line_bytes;
	int		ret_print_value;
	char	*buff;

	ret_print_value = 0;
	tmp_fd = open(path, O_RDONLY);
	fd = open(path, O_RDONLY);
	if (fd == -1 || tmp_fd == -1)
		return (-1);
	while (ret_print_value == 0)
	{
		line_bytes = get_line_bytes(tmp_fd);
		buff = malloc(sizeof(char) * (line_bytes));
		read(fd, buff, line_bytes);
		buff[line_bytes - 1] = 0;
		ret_print_value = print_value(buff, key);
		free(buff);
		buff = NULL;
	}
	return (0);
}

void	read_dict_helper(char *path, int *part_key, int *spc_state)
{
	if (*part_key > 99)
	{
		parse_dict(path, *part_key / 100);
		ft_putchar(' ');
		parse_dict(path, 100);
		*part_key = *part_key % 100;
		*spc_state = 1;
	}
	if (*part_key > 9)
	{
		if (*spc_state == 1)
			ft_putchar(' ');
		parse_dict(path, (*part_key / 10) * 10);
		*part_key = *part_key % 10;
		*spc_state = 1;
	}
}

void	read_dict(char *path, int part_key, int thousands)
{
	int	spc_state;

	spc_state = 0;
	read_dict_helper(path, &part_key, &spc_state);
	if (part_key != 0)
	{
		if (spc_state == 1)
			ft_putchar(' ');
		parse_dict(path, part_key);
		spc_state = 1;
	}
	if (thousands != 0)
	{
		if (spc_state == 1)
			ft_putchar(' ');
		parse_dict(path, thousands);
	}
}

void	dict_control(char *path, int *full_key, int thousands, int *spc_state)
{
	int	part_key;

	part_key = *full_key;
	if (*spc_state == 1)
		ft_putchar(' ');
	part_key = *full_key / thousands;
	read_dict(path, part_key, thousands);
	*full_key = *full_key % thousands;
	*spc_state = 1;
}
