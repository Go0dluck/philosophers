/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharee <ksharee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:30:27 by goodluck          #+#    #+#             */
/*   Updated: 2021/03/22 12:28:12 by ksharee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5

typedef struct		s_philo
{
	int				pos;
	long long		last_eat;
	sem_t			*protect;
	struct s_all	*all;
}					t_philo;

typedef struct		s_all
{
	int				t_eat;
	int				t_sleep;
	int				t_die;
	int				must_eat;
	int				size;
	int				stop;
	long			start;
	sem_t			*death;
	sem_t			*fork;
	sem_t			*mess;
	t_philo			*philo;
}					t_all;

void				check_arg(int agrc, char **agrv);
int					is_num(char **agrv);
void				error_exit(char *str);
void				send_mess(int type, t_philo *philo);
void				ft_putnbr_fd(long n, int fd);
long				get_time(void);
int					ft_atoi(const char *str);
int					ft_strlen(char *str);
void				init_struct(t_all *all, int agrc, char **agrv);

void				philo_get_fork(t_philo *philo);
void				philo_eat(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_think(t_philo *philo);

#endif
