/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharee <ksharee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 22:11:50 by goodluck          #+#    #+#             */
/*   Updated: 2021/03/22 12:32:24 by ksharee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	philo_get_fork(t_philo *philo)
{
	sem_wait(philo->all->fork);
	sem_wait(philo->all->fork);
	send_mess(FORK, philo);
}

void	philo_eat(t_philo *philo)
{
	sem_wait(philo->protect);
	if (philo->all->must_eat == 0)
		sem_wait(philo->protect);
	philo->last_eat = get_time();
	send_mess(EAT, philo);
	if (philo->all->must_eat > 0)
		philo->all->must_eat--;
	usleep(philo->all->t_eat * 1000);
	sem_post(philo->protect);
	sem_post(philo->all->fork);
	sem_post(philo->all->fork);
}

void	philo_sleep(t_philo *philo)
{
	send_mess(SLEEP, philo);
	usleep(philo->all->t_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	send_mess(THINK, philo);
}
