/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 11:34:07 by minsunki          #+#    #+#             */
/*   Updated: 2021/09/30 16:32:47 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	p_eat(t_meta *m, t_philo *p)
{
	pthread_mutex_lock(&(m->m_forks[p->pid]));
	pprint(m, p->pid, "has taken a fork");
	if (m->nop == 1)
		return ;
	pthread_mutex_lock(&(m->m_forks[(p->pid + 1) % m->nop]));
	pprint(m, p->pid, "has taken a fork");
	pthread_mutex_lock(&(m->m_meal));
	pprint(m, p->pid, "is eating");
	p->ate++;
	p->last_meal = timestamp();
	pthread_mutex_unlock(&(m->m_meal));
	pwait(m, m->tte);
	pthread_mutex_unlock(&(m->m_forks[p->pid]));
	pthread_mutex_unlock(&(m->m_forks[(p->pid + 1) % m->nop]));
}

static void	*p_thread(void *pp)
{
	t_philo	*p;
	t_meta	*m;

	m = meta_get();
	p = (t_philo *)pp;
	if (p->pid % 2)
		usleep(5000);
	while (!m->died)
	{
		p_eat(m, p);
		if (m->nop == 1 || m->all_ate)
			break ;
		pprint(m, p->pid, "is sleeping");
		pwait(m, m->tts);
		pprint(m, p->pid, "is thinking");
	}
	return (0);
}

static void	deathwatch(t_meta *m, t_philo *p)
{
	int		i;

	while (!m->all_ate)
	{
		i = -1;
		while (++i < m->nop && !m->died)
		{
			pthread_mutex_lock(&(m->m_meal));
			if (timestamp() - p[i].last_meal > m->ttd)
			{
				pprint(m, i, "died");
				m->died = 1;
			}
			pthread_mutex_unlock(&(m->m_meal));
			usleep(50);
		}
		if (m->died)
			break ;
		i = 0;
		while (m->npe && i < m->nop && p[i].ate >= m->npe)
			i++;
		if (i == m->nop)
			m->all_ate = 1;
	}
}

static void	thread_cleanup(t_meta *m, t_philo *p)
{
	int		i;

	i = -1;
	while (++i < m->nop)
		pthread_join(p[i].tid, NULL);
	i = -1;
	while (++i < m->nop)
		pthread_mutex_destroy(&(m->m_forks[i]));
	pthread_mutex_destroy(&(m->m_print));
	pthread_mutex_destroy(&(m->m_meal));
}

int	philo_run(t_meta *m)
{
	int		i;

	i = -1;
	m->start_time = timestamp();
	while (++i < m->nop)
	{
		if (pthread_create(&(m->philosophers[i].tid), NULL, p_thread,
				&(m->philosophers[i])))
			return (1);
		m->philosophers[i].last_meal = m->start_time;
	}
	deathwatch(m, m->philosophers);
	thread_cleanup(m, m->philosophers);
	return (0);
}
