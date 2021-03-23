/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharee <ksharee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 11:32:35 by goodluck          #+#    #+#             */
/*   Updated: 2021/03/22 11:16:53 by ksharee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5

typedef struct		s_philo
{
	int				pos;
	pid_t			pid;
	long long		last_eat;
	long long		limit;
	sem_t			*protect;
	sem_t			*sem_must_eat;
	struct s_all	*all;
}					t_philo;

typedef struct		s_all
{
	int				t_eat;
	int				t_sleep;
	int				t_die;
	int				must_eat;
	int				size_must_eat;
	int				size;
	int				stop;
	long			start;
	sem_t			*death;
	sem_t			*fork;
	sem_t			*mess;
	t_philo			*philo;
}					t_all;

void				init_struct(t_all *all, int agrc, char **agrv);
void				error_exit(char *str);
int					is_num(char **agrv);
int					ft_atoi(const char *str);
int					ft_strlen(char *str);
long				get_time(void);
void				check_arg(int agrc, char **agrv);
void				*monitor(void *philo);
void				*monitor_eat(void *all);

void				philo_get_fork(t_philo *philo);
void				send_mess(int type, t_philo *philo);
void				philo_eat(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_think(t_philo *philo);

#endif
