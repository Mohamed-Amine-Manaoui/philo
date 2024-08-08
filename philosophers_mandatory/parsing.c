/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanaoui <mmanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 21:45:26 by mmanaoui          #+#    #+#             */
/*   Updated: 2024/08/08 17:27:50 by mmanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		signe;
	long	res;

	i = 0;
	signe = 1;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		signe = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		if (res * signe > INT_MAX || res * signe < INT_MIN)
			return (0);
		i++;
	}
	return (res * signe);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_alpha(char *av)
{
	int	i;

	i = 0;
	if (av[i] == '-' || av[i] == '+')
		i++;
	if (!av[i])
		return (1);
	while (av[i])
	{
		if (ft_isdigit(av[i]))
			i++;
		else
			return (1);
	}
	return (0);
}

int	handle_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] == 32)
			i++;
		if (((str[i] == '-' || str[i] == '+') && !(str[i + 1] >= 48 && str[i
					+ 1] <= 57)) || check_alpha(str))
		{
			return (-1);
		}
		i++;
	}
	return (1);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len && s[start] != '\0')
	{
		ptr[i] = s[start];
		i++;
		start++;
	}
	ptr[i] = '\0';
	return (ptr);
}

void	ss(int ac, char **av)
{
	int	i;
	int	j;
	int	k;

	i = 1;
	k = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j] == 32 || av[i][j] == 9)
			j++;
		if (!av[i][j])
			break ;
		k = j + 1;
		while (av[i][k] && av[i][k] != 32 && av[i][k] != 9)
			k++;
		av[i] = ft_substr(av[i], j, k - j);
		if (ac - 1 == i)
			break ;
		i++;
	}
}

int	valid_args(char **av, int ac, t_help *help)
{
	int	i;

	i = 1;
	ss(ac, av);
	while (av[i])
	{
		if (handle_error(av[i]) == -1)
			return (1);
		i++;
	}
	help->nbr_philo = ft_atoi(av[1]);
	help->time_to_die = ft_atoi(av[2]);
	help->time_to_eat = ft_atoi(av[3]);
	help->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		help->nbr_meals = ft_atoi(av[5]);
	return (0);
}
