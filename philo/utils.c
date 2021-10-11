/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 12:55:30 by minsunki          #+#    #+#             */
/*   Updated: 2021/10/11 12:03:50 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	unsigned long long	res;
	int					is_neg;

	while (*str == ' ' || *str == '\v' || *str == '\t' || *str == '\r'
		|| *str == '\n' || *str == '\f')
		str++;
	is_neg = (*str == '-');
	if (*str == '+' || *str == '-')
		str++;
	res = 0;
	while ('0' <= *str && *str <= '9')
	{
		res *= 10;
		res += *str - '0';
		str++;
	}
	if (res > 2147483647 && !is_neg)
		return (-1);
	if (res > 2147483648 && is_neg)
		return (0);
	if (is_neg)
		return (-res);
	return (res);
}

void	pprint(t_meta *m, int id, char *str, int ndc)
{
	pthread_mutex_lock(&(m->m_print));
	if (ndc || !m->died)
	{
		printf("%lli ", timestamp() - m->start_time);
		printf("%i ", id + 1);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(m->m_print));
}

void	pwait(t_meta *m, long long time)
{
	long long	st;

	st = timestamp();
	while (!m->died)
	{
		if (timestamp() - st >= time)
			break ;
		usleep(100);
	}
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, 0);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}
