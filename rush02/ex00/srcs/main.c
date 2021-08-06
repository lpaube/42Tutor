/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 12:04:51 by laube             #+#    #+#             */
/*   Updated: 2021/08/06 13:15:54 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../incls/header.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

int	ft_atoi(const char *str)
{
	int	curr_num;
	int	sign;

	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	sign = 1;
	curr_num = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!(*str >= '0' && *str <= '9'))
		return (-1);
	while (*str >= '0' && *str <= '9')
		curr_num = (curr_num * 10) + (*(str++) - '0');
	if (curr_num * sign < 0)
		return (-1);
	return (curr_num * sign);
}

int	get_line_bytes(int tmp_fd)
{
	int	line_bytes;
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

int	parse_dict(char *path, int key)
{
	int	tmp_fd;
	int	fd;
	int	line_bytes;
	int	ret_print_value;
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

void	parse_key(char *path, int full_key)
{
	int	part_key;
	
	part_key = full_key;
	if (part_key < 1000)
	{
		if (part_key > 99)
		{
			parse_dict(path, part_key / 100);
			ft_putchar(' ');
			parse_dict(path, 100);
			ft_putchar(' ');
			part_key = part_key % 100;
		}
		if (part_key > 9)
		{
			parse_dict(path, (part_key / 10) * 10);
			ft_putchar(' ');
			part_key = part_key % 10;
		}
		if (part_key != 0)
			parse_dict(path, part_key);
	}
}

int	ft_error(char *str)
{
	ft_putstr(str);
	return (-1);
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
		parse_key("../dict.txt", key);
	}
	else if (argc == 3)
	{
		key = ft_atoi(argv[2]);
		if (key == -1)
			return (ft_error("Error\n"));
		parse_key(argv[1], key);
	}
}
