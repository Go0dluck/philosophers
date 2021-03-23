/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharee <ksharee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 11:32:38 by goodluck          #+#    #+#             */
/*   Updated: 2021/03/22 11:58:45 by ksharee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	kill_process(t_all *all)
{
	int		i;

	i = -1;
	while (++i < all->size)
		kill(all->philo[i].pid, SIGKILL);
}

void	processor(t_philo *philo)
{
	pthread_t	pt_monitor;

	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->all->t_die;
	pthread_create(&pt_monitor, NULL, monitor, philo);
	pthread_detach(pt_monitor);
	while (1)
	{
		philo_get_fork(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
}

void	start_fork(t_all *all)
{
	int			i;
	pthread_t	pt_monitor_eat;

	i = -1;
	while (++i < all->size)
	{
		all->philo[i].pid = fork();
		if (all->philo[i].pid < 0)
			error_exit("\e[1;31mError fork\e[0m");
		else if (all->philo[i].pid == 0)
		{
			processor(&all->philo[i]);
			exit(0);
		}
		usleep(100);
	}
	if (all->must_eat == 1)
	{
		pthread_create(&pt_monitor_eat, NULL, monitor_eat, all);
		pthread_detach(pt_monitor_eat);
	}
}

int		main(int agrc, char **agrv)
{
	t_all	*all;

	check_arg(agrc, agrv);
	if (!(all = (t_all *)malloc(sizeof(t_all))))
		error_exit("\e[1;31mError malloc\e[0m");
	init_struct(all, agrc, agrv);
	all->start = get_time();
	start_fork(all);
	sem_wait(all->death);
	kill_process(all);
	return (0);
}
