/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:09:29 by agunczer          #+#    #+#             */
/*   Updated: 2022/01/28 16:33:20 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	increase_philo_id(t_shared *shared, int *philo_id)
{
	pthread_mutex_lock(&shared->mutex_philo_id);
	*philo_id = shared->philo_id;
	shared->philo_id++;
	pthread_mutex_unlock(&shared->mutex_philo_id);
}

static int	check_input(int argc, char **argv)
{
	int	num;

	num = 1;
	if (argc < 5 || argc > 6)
	{
		printf("\033[0;31m\tWrong number of Arguments\n\tPhilosophers quit.");
		return (1);
	}
	if (is_num(argv[1]) == 0)
		num = 0;
	if (is_num(argv[2]) == 0)
		num = 0;
	if (is_num(argv[3]) == 0)
		num = 0;
	if (is_num(argv[4]) == 0)
		num = 0;
	if (argc == 6)
	{
		if (is_num(argv[5]) == 0)
			num = 0;
	}
	if (num == 1)
	{
		printf("\033[0;33mBUCKLE UP FUCKERS, THE HUNGER GAMES ARE ABOUT TO BEGIN!\n\033[0m");
		sleep(4);
	}
	else
	{
		printf("\033[0;31m\tWrong argument type provided\n\tPhilosophers quit.");
		return (1);
	}
	return (0);
}

static int	init_input(t_input *input, char **argv)
{
	input->num_of_philo = ft_atoi(argv[1]);
	input->time_to_die = ft_atoi(argv[2]);
	input->time_to_eat = ft_atoi(argv[3]);
	input->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		input->number_of_meals = ft_atoi(argv[5]);
	else
		input->number_of_meals = -1;
	// shared_data->fork = malloc(shared_data->num_of_philo
	// 		* sizeof(int));
	// while (i < shared_data->num_of_philo)
	// {
	// 	shared_data->fork[i] = 1;
	// 	i++;
	// }
	return (0);
}

int	main(int argc, char **argv)
{
	int			i;
	t_input		input;

	i = 1;
	if (check_input(argc, argv) == 1)
		return (EXIT_FAILURE);
	if (init_input(&input, argv) == 1 && free_all())
		return (EXIT_FAILURE);
	if (create_philo(input) == NULL && free_all())
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
