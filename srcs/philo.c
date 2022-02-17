#include "../inc/philosophers.h"

// static void status_philo(t_philo philo)
// {
// 	printf("DATA CHECK PHILO %d\n", philo.id);
// 	printf("\tphilo[i].waiter = %p\n", philo.mutex_waiter);
// 	printf("\tphilo[i].death = %p\n", philo.mutex_death);
// 	printf("\tphilo[i].print = %p\n", philo.mutex_print);
// 	printf("\tphilo[i].lfork (borrow) = %p\n", philo.mutex_lfork);
// 	printf("\tphilo[i].rfork (own) = %p\n", philo.mutex_rfork);
// }

static	int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	else if ((c == '\n' || c == '\t' || c == '\v' || c == '\t' || c == '\r'
			|| c == '\f'))
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		j;
	int		num;

	i = 0;
	j = 0;
	num = 0;
	while (ft_isspace(*(str + i)) == 1 && str[i] != '\0')
	{
		i++;
		j++;
	}
	if (str[i] == '\0')
		return (0);
	if (*(str + j) == '-' || *(str + j) == '+')
		i++;
	while (*(str + i) && *(str + i) >= '0' && *(str + i) <= '9')
	{
		num = num * 10 + (*(str + i) - '0');
		i++;
	}
	if (*(str + j) == '-')
		num *= -1;
	return (num);
}

int	is_num(char *str)
{
	if (str == NULL)
		return (0);
	while (*str != '\0')
	{
		if (*str > 57 || *str < 48)
			return (0);
		str++;
	}
	return (1);
}

int		destroy_mutexes(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(philo[0].mutex_end);
	free(philo[0].mutex_end);
	pthread_mutex_destroy(philo[0].mutex_print);
	free(philo[0].mutex_print);
	pthread_mutex_destroy(philo[0].mutex_death);
	free(philo[0].mutex_death);
	if (philo[0].death != NULL)
		free((void *)philo[0].death);
	while (i < philo[0].input->num_of_philo)
	{
		pthread_mutex_destroy(philo[i].mutex_rfork);
		free(philo[i].mutex_rfork);
		i++;
	}
	return (0);
}

int		launch_philo(t_philo *philo, t_input *input)
{
	int	i;

	i = 0;
	while (i < input->num_of_philo)
	{
		pthread_create(&philo[i].philosopher, NULL, &routine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < input->num_of_philo)
	{
		pthread_join(philo[i].philosopher, NULL);
		i++;
	}
	return (0);
}

int		fill_philosophers(t_input *input, t_philo *philo, int i)
{
	while (i < input->num_of_philo)
	{
		philo[i].mutex_rfork = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
		if (pthread_mutex_init(philo[i].mutex_rfork, NULL))
			return (1);
		i++;
	}
	i = 0;
	while (i < input->num_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].death = philo[0].death;
		philo[i].mutex_end = philo[0].mutex_end;
		philo[i].mutex_death = philo[0].mutex_death;
		philo[i].mutex_print = philo[0].mutex_print;
		philo[i].mutex_lfork = philo[(i + 1) % input->num_of_philo].mutex_rfork;
		philo[i].input = input;
		philo[i].amount_meal = 0;
		philo[i].last_meal = get_time();
		i++;
	}
	launch_philo(philo, input);
	return (0);
}

t_philo	*create_philosopher(t_input *input)
{
	t_philo *philo;
	int		i;

	philo = (t_philo *) malloc(input->num_of_philo * sizeof(t_philo));
	philo->death = (int *) malloc(sizeof(int));
	philo->mutex_end = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	philo->mutex_death = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	philo->mutex_print = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	if (philo->death == NULL || philo->mutex_end == NULL
		|| philo->mutex_death == NULL || philo->mutex_print == NULL)
		return (NULL);
	if (pthread_mutex_init(philo->mutex_end, NULL))
		return (NULL);
	if (pthread_mutex_init(philo->mutex_death, NULL))
		return (NULL);
	if (pthread_mutex_init(philo->mutex_print, NULL))
		return (NULL);
	*philo->death = 0;
	i = 0;
	if (fill_philosophers(input, philo, i))
		return (NULL);
	return (philo);
}