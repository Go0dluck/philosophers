/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goodluck <goodluck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 14:52:28 by ksharee           #+#    #+#             */
/*   Updated: 2021/03/21 11:07:56 by goodluck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	philo_get_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->philo[philo->r_fork].philo_fork);
	pthread_mutex_lock(&philo->all->philo[philo->l_fork].philo_fork);
	pthread_mutex_lock(&philo->all->mutex_mess);
	send_mess(FORK, philo);
	pthread_mutex_unlock(&philo->all->mutex_mess);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_mut);
	philo->last_eat = get_time();
	pthread_mutex_lock(&philo->all->mutex_mess);
	send_mess(EAT, philo);
	pthread_mutex_unlock(&philo->all->mutex_mess);
	if (philo->all->must_eat > 0)
		philo->all->must_eat--;
	usleep(philo->all->t_eat * 1000);
	pthread_mutex_unlock(&philo->philo_mut);
	pthread_mutex_unlock(&philo->all->philo[philo->r_fork].philo_fork);
	pthread_mutex_unlock(&philo->all->philo[philo->l_fork].philo_fork);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->mutex_mess);
	send_mess(SLEEP, philo);
	pthread_mutex_unlock(&philo->all->mutex_mess);
	usleep(philo->all->t_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->mutex_mess);
	send_mess(THINK, philo);
	pthread_mutex_unlock(&philo->all->mutex_mess);
}
