/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 11:34:44 by minsunki          #+#    #+#             */
/*   Updated: 2021/09/30 16:32:27 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pperror(char *str)
{
	printf("%s\n", str);
	return (1);
}

static int	prep(t_meta *m)
{
	int	i;

	i = m->nop;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(m->m_forks[i]), NULL))
			return (1);
		m->philosophers[i].pid = i;
	}
	if (pthread_mutex_init(&(m->m_print), NULL))
		return (1);
	if (pthread_mutex_init(&(m->m_meal), NULL))
		return (1);
	return (0);
}

int	main(int ac, char *av[])
{
	t_meta	*m;

	if (ac != 5 && ac != 6)
		return (pperror("Wrong number of arguments"));
	m = meta_get();
	if (!m)
		return (pperror("Malloc failed for meta"));
	m->nop = ft_atoi(av[1]);
	if (m->nop < 0)
		return (1);
	meta_init();
	m->ttd = ft_atoi(av[2]);
	m->tte = ft_atoi(av[3]);
	m->tts = ft_atoi(av[4]);
	if (ac == 6)
		m->npe = ft_atoi(av[5]);
	if (m->nop < 1 || m->ttd < 0 || m->tte < 0 || m->tts < 0 || m->npe < 0)
		return (1);
	if (prep(m))
		return (1);
	if (philo_run(m))
		return (pperror("Pthread failed"));
	meta_destroy();
	return (0);
}
