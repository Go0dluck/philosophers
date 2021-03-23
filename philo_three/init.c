/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharee <ksharee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 11:37:21 by goodluck          #+#    #+#             */
/*   Updated: 2021/03/22 11:15:47 by ksharee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	check_arg(int agrc, char **agrv)
{
	if (agrc < 5 || agrc > 6)
		error_exit("\e[1;31mFew or many arguments\e[0m");
	if (is_num(agrv) == 1)
		error_exit("\e[1;31mInvalid arguments\e[0m");
}

void	semofor_init2(t_all *all, char *sem_name, char c, int i)
{
	memset(sem_name, c, i + 1);
	sem_unlink(sem_name);
	if ((all->philo[i].protect = sem_open(sem_name, O_CREAT, 0666, 1))
		== SEM_FAILED)
		error_exit("\e[1;31mError sem_open\e[0m");
}

void	init_philo(t_all *all, char **agrv)
{
	int		i;
	char	sem_name[all->size];
	char	eat_name[all->size];

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
		semofor_init2(all, sem_name, 'P', i);
		if (all->must_eat == 1)
		{
			memset(eat_name, 'E', i + 1);
			sem_unlink(eat_name);
			if ((all->philo[i].sem_must_eat =
				sem_open(eat_name, O_CREAT, 0666, 1)) == SEM_FAILED)
				error_exit("\e[1;31mError sem_open\e[0m");
		}
	}
}

void	semofor_init(t_all *all)
{
	sem_unlink("death");
	sem_unlink("fork");
	sem_unlink("mess");
	if ((all->death = sem_open("death", O_CREAT, 0666, 0)) == SEM_FAILED)
		error_exit("\e[1;31mError sem_open\e[0m");
	if ((all->fork = sem_open("fork", O_CREAT, 0666, all->size)) == SEM_FAILED)
		error_exit("\e[1;31mError sem_open\e[0m");
	if ((all->mess = sem_open("mess", O_CREAT, 0666, 1)) == SEM_FAILED)
		error_exit("\e[1;31mError sem_open\e[0m");
}

void	init_struct(t_all *all, int agrc, char **agrv)
{
	all->size = ft_atoi(agrv[1]);
	semofor_init(all);
	if (all->size < 2 || all->size > 200)
		error_exit("\e[1;31mError size philosophers\e[0m");
	if (agrc == 6)
	{
		all->must_eat = 1;
		if ((all->size_must_eat = ft_atoi(agrv[5])) == 0)
			all->must_eat = 0;
	}
	else
		all->must_eat = 0;
	if (!(all->philo = (t_philo *)malloc(sizeof(t_philo) * all->size)))
		error_exit("\e[1;31mError malloc\e[0m");
	init_philo(all, agrv);
	all->start = get_time();
}
