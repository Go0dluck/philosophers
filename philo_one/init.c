/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goodluck <goodluck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 10:09:39 by ksharee           #+#    #+#             */
/*   Updated: 2021/03/20 23:52:23 by goodluck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	check_arg(int agrc, char **agrv)
{
	if (agrc < 5 || agrc > 6)
		error_exit("\e[1;31mFew or many arguments\e[0m");
	if (is_num(agrv) == 1)
		error_exit("\e[1;31mInvalid arguments\e[0m");
}

void	init_philo(t_all *all, char **agrv)
{
	int	i;

	i = -1;
	all->t_die = ft_atoi(agrv[2]);
	all->t_eat = ft_atoi(agrv[3]);
	all->t_sleep = ft_atoi(agrv[4]);
	if (all->t_die < 60 || all->t_eat < 60 || all->t_sleep < 60)
		error_exit("\e[1;31mArgument under 60\e[0m");
	while (++i < all->size)
	{
		all->philo[i].all = all;
		all->philo[i].pos = i + 1;
		all->philo[i].p_die = 0;
		all->philo[i].l_fork = i + 1;
		all->philo[i].r_fork = ((i - 1 + all->size) % all->size) + 1;
		if (pthread_mutex_init(&all->philo[i].philo_fork, NULL) != 0)
			error_exit("\e[1;31mError mutex_init\e[0m");
		if (pthread_mutex_init(&all->philo[i].philo_mut, NULL) != 0)
			error_exit("\e[1;31mError mutex_init\e[0m");
	}
}

void	init_struct(t_all *all, int agrc, char **agrv)
{
	all->size = ft_atoi(agrv[1]);
	if (all->size < 2 || all->size > 200)
		error_exit("\e[1;31mError size philosophers\e[0m");
	if (agrc == 6)
	{
		all->must_eat = ft_atoi(agrv[5]) * all->size;
		if (all->must_eat == 0)
			all->must_eat = -1;
	}
	else
		all->must_eat = -1;
	if (!(all->philo = (t_philo *)malloc(sizeof(t_philo) * all->size)))
		error_exit("\e[1;31mError malloc\e[0m");
	init_philo(all, agrv);
	if (pthread_mutex_init(&all->mutex_mess, NULL) != 0)
		error_exit("\e[1;31mError mutex_init\e[0m");
	if (pthread_mutex_init(&all->mutex_must_eat, NULL) != 0)
		error_exit("\e[1;31mError mutex_init\e[0m");
	pthread_mutex_lock(&all->mutex_must_eat);
	all->start = get_time();
}
