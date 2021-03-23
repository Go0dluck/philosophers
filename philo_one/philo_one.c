/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goodluck <goodluck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 10:09:45 by ksharee           #+#    #+#             */
/*   Updated: 2021/03/21 11:27:04 by goodluck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	clear_all(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->size)
	{
		pthread_mutex_destroy(&all->philo[i].philo_fork);
		pthread_mutex_destroy(&all->philo[i].philo_mut);
	}
	pthread_mutex_destroy(&all->mutex_must_eat);
	pthread_mutex_destroy(&all->mutex_mess);
}

void	*monitor(void *philo)
{
	t_philo *tmp;

	tmp = (t_philo *)philo;
	while (1)
	{
		pthread_mutex_lock(&tmp->philo_mut);
		if ((get_time() - tmp->last_eat) > tmp->all->t_die)
		{
			pthread_mutex_lock(&tmp->all->mutex_mess);
			send_mess(DIE, philo);
			pthread_mutex_unlock(&tmp->philo_mut);
			pthread_mutex_unlock(&tmp->all->mutex_must_eat);
		}
		else if (tmp->all->must_eat == 0)
		{
			pthread_mutex_lock(&tmp->all->mutex_mess);
			write(1, "All the philosophers have eaten\n", 33);
			pthread_mutex_unlock(&tmp->philo_mut);
			pthread_mutex_unlock(&tmp->all->mutex_must_eat);
		}
		pthread_mutex_unlock(&tmp->philo_mut);
		usleep(100);
	}
	return (NULL);
}

void	*processor(void *philo)
{
	t_philo		*tmp;
	pthread_t	pt_monitor;

	tmp = (t_philo *)philo;
	tmp->last_eat = get_time();
	pthread_create(&pt_monitor, NULL, monitor, philo);
	pthread_detach(pt_monitor);
	while (1)
	{
		philo_get_fork(tmp);
		philo_eat(tmp);
		philo_sleep(tmp);
		philo_think(tmp);
	}
	return (NULL);
}

void	start_pthread(t_all *all)
{
	pthread_t	tid;
	int			i;

	i = -1;
	while (++i < all->size)
	{
		pthread_create(&tid, NULL, processor, &all->philo[i]);
		pthread_detach(tid);
	}
}

int		main(int agrc, char **agrv)
{
	t_all		*all;

	check_arg(agrc, agrv);
	if (!(all = (t_all *)malloc(sizeof(t_all))))
		error_exit("\e[1;31mError malloc\e[0m");
	init_struct(all, agrc, agrv);
	all->start = get_time();
	start_pthread(all);
	pthread_mutex_lock(&all->mutex_must_eat);
	pthread_mutex_unlock(&all->mutex_must_eat);
	clear_all(all);
	return (0);
}
