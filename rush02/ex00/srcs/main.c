/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 12:04:51 by laube             #+#    #+#             */
/*   Updated: 2021/08/06 22:57:15 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/header.h"

int	get_line_bytes(int tmp_fd)
{
	int		line_bytes;
	char	buff;

	line_bytes = 0;
	buff = 1;
	while (buff != '\n' && buff != 0)
	{
		read(tmp_fd, &buff, 1);
		line_bytes++;
	}
	return (line_bytes);
}

int	print_value(char *buff, int key)
{
	int	dict_key;

	dict_key = ft_atoi(buff);
	if (dict_key == key)
	{
		while (*buff)
		{
			if (*buff == ':')
			{
				buff++;
				while ((*buff >= 9 && *buff <= 13) || *buff == 32)
					buff++;
				ft_putstr(buff);
				return (1);
			}
			buff++;
		}
	}
	return (0);
}

void	parse_key(char *path, int full_key)
{
	int	part_key;
	int	spc_state;

	spc_state = 0;
	part_key = full_key;
	if (full_key >= 1000000000)
		dict_control(path, &full_key, 1000000000, &spc_state);
	if (full_key < 1000000000 && full_key >= 1000000)
		dict_control(path, &full_key, 1000000, &spc_state);
	if (full_key < 1000000 && full_key >= 1000)
		dict_control(path, &full_key, 1000, &spc_state);
	if (full_key < 1000)
	{
		if (spc_state == 1)
			ft_putchar(' ');
		read_dict(path, full_key, 0);
	}
	ft_putchar('\n');
}

int	main(int argc, char **argv)
{
	int	key;

	if (argc != 2 && argc != 3)
		return (ft_error("Error\n"));
	if (argc == 2)
	{
		key = ft_atoi(argv[1]);
		if (key == -1)
			return (ft_error("Error\n"));
		parse_key("dict.txt", key);
	}
	else if (argc == 3)
	{
		key = ft_atoi(argv[2]);
		if (key == -1)
			return (ft_error("Error\n"));
		parse_key(argv[1], key);
	}
}
