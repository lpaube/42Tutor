/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 12:04:51 by laube             #+#    #+#             */
/*   Updated: 2021/08/06 00:05:15 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../incls/header.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

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

char	*get_value(char *buff, int key)
{
	printf("key: %d | buff: %s\n", key, buff);
	return ("hello");
}

int	parse_dict(char *path, int key)
{
	int	tmp_fd;
	int	fd;
	int	line_bytes;
	char	*buff;
	char	*value;

	value = NULL;
	tmp_fd = open(path, O_RDONLY);
	fd = open(path, O_RDONLY);
	if (fd == -1 || tmp_fd == -1)
		return (-1);
	while (value == NULL)
	{
		line_bytes = get_line_bytes(tmp_fd);
		buff = malloc(sizeof(char) * (line_bytes));
		read(fd, buff, line_bytes);
		buff[line_bytes - 1] = 0;
		value = get_value(buff, key);
		free(buff);
	}
	return (0);
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
		parse_dict("../dict.txt", key);
	}
	else if (argc == 3)
	{
		key = ft_atoi(argv[2]);
		if (key == -1)
			return (ft_error("Error\n"));
		parse_dict(argv[1], key);
	}
}
