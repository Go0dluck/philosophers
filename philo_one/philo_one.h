/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharee <ksharee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:46:19 by ksharee           #+#    #+#             */
/*   Updated: 2021/03/22 13:29:26 by ksharee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5

typedef struct		s_philo
{
	int				pos;
	int				l_fork;
	int				r_fork;
	int				p_die;
	long long		last_eat;
	struct s_all	*all;
	pthread_mutex_t	philo_mut;
	pthread_mutex_t	philo_fork;
}					t_philo;

typedef struct		s_all
{
	int				t_eat;
	int				t_sleep;
	int				t_die;
	int				must_eat;
	int				size;
	int				quantity_eat;
	pthread_mutex_t	mutex_mess;
	pthread_mutex_t	mutex_must_eat;
	long long		start;
	t_philo			*philo;
}					t_all;

int					ft_atoi(const char *str);
int					ft_strlen(char *str);
void				send_mess(int type, t_philo *philo);
void				error_exit(char *str);
int					is_num(char **agrv);

void				init_struct(t_all *all, int agrc, char **agrv);
long				get_time(void);
void				check_arg(int agrc, char **agrv);

void				philo_get_fork(t_philo *philo);
void				philo_eat(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_think(t_philo *philo);

#endif
