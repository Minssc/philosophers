/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 11:58:43 by minsunki          #+#    #+#             */
/*   Updated: 2021/09/30 16:05:24 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_meta	*meta_get(void)
{
	static t_meta	*meta;

	if (!meta)
	{
		meta = (t_meta *)malloc(sizeof(t_meta));
		memset(meta, 0, sizeof(t_meta));
	}
	if (!meta)
		return (0);
	return (meta);
}

int	meta_init(void)
{
	t_meta	*m;

	m = meta_get();
	m->philosophers = (t_philo *)malloc(sizeof(t_philo) * m->nop);
	if (!m->philosophers)
		return (pperror("malloc failed @meta_init for m->m_philosophers"));
	memset(m->philosophers, 0, sizeof(t_philo) * m->nop);
	m->m_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * m->nop);
	if (!m->m_forks)
		return (pperror("malloc failed @meta_init for m->m_forks"));
	return (0);
}

void	meta_destroy(void)
{
	t_meta	*m;

	m = meta_get();
	if (!m)
		return ;
	if (m->philosophers)
		free(m->philosophers);
	if (m->m_forks)
		free(m->m_forks);
	free(m);
}
