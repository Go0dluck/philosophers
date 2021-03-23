/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goodluck <goodluck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 11:37:23 by goodluck          #+#    #+#             */
/*   Updated: 2021/03/21 11:39:19 by goodluck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	if (str == NULL)
		return (i);
	while (str[i])
		i++;
	return (i);
}

int		ft_atoi(const char *str)
{
	long int	i;
	long int	rez;
	int			minus;

	i = 0;
	rez = 0;
	minus = 1;
	while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || \
			str[i] == '\v' || str[i] == '\f' || str[i] == '\r'))
		i++;
	if (str[i] == '-')
	{
		minus = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
		rez = rez * 10 + str[i++] - '0';
	if (i > 25 && minus < 0)
		return (0);
	if (i > 25 && minus > 0)
		return (-1);
	return (rez * minus);
}
