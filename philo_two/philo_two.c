/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharee <ksharee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:30:05 by goodluck          #+#    #+#             */
/*   Updated: 2021/03/22 12:48:14 by ksharee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	clear_all(void)
{
	sem_unlink("death");
	sem_unlink("fork");
	sem_unlink("mess");
	sem_unlink("protect");
}

void	*monitor(void *philo)
{
	t_philo	*tmp;

	tmp = (t_philo *)philo;
	while (1)
	{
		sem_wait(tmp->protect);
		if ((get_time() - tmp->last_eat) > tmp->all->t_die)
			send_mess(DIE, philo);
		else if (tmp->all->must_eat == 0)
		{
			sem_wait(tmp->all->mess);
			write(1, "All the philosophers have eaten\n", 33);
			sem_post(tmp->all->death);
		}
		sem_post(tmp->protect);
		usleep(100);
	}
	return (NULL);
}

void	*processor(void *philo)
{
	pthread_t	tid;
	t_philo		*tmp;

	tmp = (t_philo *)philo;
	tmp->last_eat = get_time();
	pthread_create(&tid, NULL, monitor, philo);
	pthread_detach(tid);
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
	t_all	*all;

	check_arg(agrc, agrv);
	if (!(all = (t_all *)malloc(sizeof(t_all))))
		error_exit("\e[1;31mError malloc\e[0m");
	init_struct(all, agrc, agrv);
	all->start = get_time();
	start_pthread(all);
	sem_wait(all->death);
	clear_all();
	return (0);
}
