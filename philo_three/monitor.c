/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharee <ksharee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:02:26 by ksharee           #+#    #+#             */
/*   Updated: 2021/03/22 11:02:42 by ksharee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*monitor(void *philo)
{
	t_philo	*tmp;

	tmp = (t_philo *)philo;
	while (1)
	{
		sem_wait(tmp->protect);
		if (get_time() > tmp->limit)
			send_mess(DIE, tmp);
		sem_post(tmp->protect);
		usleep(100);
	}
	return (NULL);
}

void	*monitor_eat(void *all)
{
	t_all	*tmp;
	int		finish;
	int		i;

	finish = -1;
	tmp = (t_all *)all;
	while (finish < tmp->size_must_eat)
	{
		i = -1;
		while (++i < tmp->size)
			sem_wait(tmp->philo[i].sem_must_eat);
		finish++;
	}
	sem_wait(tmp->mess);
	write(1, "All the philosophers have eaten\n", 33);
	sem_post(tmp->death);
	return (NULL);
}
