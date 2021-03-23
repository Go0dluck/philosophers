/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharee <ksharee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 11:37:27 by goodluck          #+#    #+#             */
/*   Updated: 2021/03/22 10:52:49 by ksharee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	philo_get_fork(t_philo *philo)
{
	sem_wait(philo->all->fork);
	sem_wait(philo->all->fork);
	send_mess(FORK, philo);
}

void	philo_eat(t_philo *philo)
{
	sem_wait(philo->protect);
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->all->t_die;
	send_mess(EAT, philo);
	usleep(philo->all->t_eat * 1000);
	sem_post(philo->protect);
	sem_post(philo->sem_must_eat);
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
