/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 11:33:47 by minsunki          #+#    #+#             */
/*   Updated: 2021/09/30 16:06:37 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

typedef struct s_philo
{
	int			pid;
	int			ate;
	long long	last_meal;
	pthread_t	tid;
}				t_philo;

// s_meta struct with metadata
// 	nop	number_of_philosophers
// 	ttd time_to_die
// 	tte time_to_eat
// 	tts time_to_sleep
// 	npe	number_of_times_each_philosopher_must_eat

typedef struct s_meta
{
	int				nop;
	int				ttd;
	int				tte;
	int				tts;
	int				npe;
	int				died;
	int				all_ate;
	long long		start_time;
	pthread_mutex_t	m_meal;
	pthread_mutex_t	m_print;
	pthread_mutex_t	*m_forks;
	t_philo			*philosophers;
}				t_meta;

// philo.c
int			philo_run(t_meta *m);

// main.c
int			pperror(char *str);

// meta.c
int			meta_init(void);
t_meta		*meta_get(void);
void		meta_destroy(void);

// utils.c
int			ft_atoi(char *str);
void		pprint(t_meta *m, int id, char *str);
void		pwait(t_meta *m, long long time);
long long	timestamp(void);

#endif