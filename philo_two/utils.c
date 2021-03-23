/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goodluck <goodluck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:39:27 by goodluck          #+#    #+#             */
/*   Updated: 2021/03/21 11:19:35 by goodluck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

long	get_time(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_putnbr_fd(long n, int fd)
{
	char	str[13];
	int		len;

	if (n == 0)
		str[0] = '0';
	len = 0;
	while (n != 0)
	{
		str[len++] = '0' + (n % 10);
		n = (n / 10);
	}
	if (len > 0)
		len--;
	while (len >= 0)
		write(fd, &str[len--], 1);
}

void	send_mess(int type, t_philo *philo)
{
	sem_wait(philo->all->mess);
	ft_putnbr_fd(get_time() - philo->all->start, 1);
	write(1, "\t", 1);
	ft_putnbr_fd(philo->pos, 1);
	if (type == 1)
		write(1, " has taken a fork\n", ft_strlen(" has taken a fork\n"));
	else if (type == 2)
		write(1, " is eating\n", ft_strlen(" is eating\n"));
	else if (type == 3)
		write(1, " is sleeping\n", ft_strlen(" is sleeping\n"));
	else if (type == 4)
		write(1, " is thinking\n", ft_strlen(" is thinking\n"));
	else if (type == 5)
	{
		write(1, " died\n", ft_strlen(" died\n"));
		sem_post(philo->all->death);
		return ;
	}
	sem_post(philo->all->mess);
}

void	error_exit(char *str)
{
	printf("%s\n", str);
	exit(1);
}

int		is_num(char **agrv)
{
	int	i;
	int	k;

	i = 0;
	while (agrv[++i])
	{
		k = -1;
		while (agrv[i][++k])
		{
			if (!(agrv[i][k] >= '0' && agrv[i][k] <= '9'))
				return (1);
		}
	}
	return (0);
}
