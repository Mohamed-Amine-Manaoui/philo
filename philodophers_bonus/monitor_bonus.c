/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanaoui <mmanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:47:07 by mmanaoui          #+#    #+#             */
/*   Updated: 2024/08/18 19:30:04 by mmanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_msleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	*monitor_die(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->help->sem_write);
		if (get_current_time()
			- philo->last_time_eat > (size_t)philo->help->time_to_die)
		{
			sem_wait(philo->help->sem_monitor);
			if (philo->help->finish_meals)
			{
				sem_post(philo->help->sem_monitor);
				sem_post(philo->help->sem_dead);
				break ;
			}
			printf("%zu %d died\n", get_current_time() - philo->help->start,
				philo->id);
			sem_post(philo->help->sem_monitor);
			sem_post(philo->help->sem_dead);
			break ;
		}
		sem_post(philo->help->sem_write);
	}
	return (NULL);
}
