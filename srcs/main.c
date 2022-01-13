# include "../inc/philosophers.h"

// int     waiter()

void    increase_philo_id(t_shared *shared, int *philo_id)
{
    pthread_mutex_lock(&shared->mutex_philo_id);
    *philo_id = shared->philo_id;
    shared->philo_id++;
    pthread_mutex_unlock(&shared->mutex_philo_id);
}

int     init_shared_data(t_shared *shared_data, char **argv)
{
    int i;

    i = 0;
    shared_data->death = 0;
    shared_data->philo_id = 1;
    pthread_mutex_init(&shared_data->mutex_philo_id, NULL);
    pthread_mutex_init(&shared_data->mutex_forks, NULL);
    pthread_mutex_init(&shared_data->mutex_waiter, NULL);
    shared_data->fork = malloc(5 * sizeof(int));
    while (i < 5)
    {
        shared_data->fork[i] = 1;
        i++;
    }
    shared_data->number_of_philosophers = ft_atoi(argv[1]);
    // shared_data->time_to_die = ft_atoi(argv[2]);
    // shared_data->time_to_eat = ft_atoi(argv[3]);
    // shared_data->time_to_sleep = ft_atoi(argv[4]);
    // if (argv[5])
    //     shared_data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
    return (0);
}

int     main(int argc, char **argv)
{
    pthread_t   threads[5];
    t_shared    shared_data;
    int         i;

    i = 1;
    init_shared_data(&shared_data, argv);
    while (i <= 5)
    {
        pthread_create(&threads[i - 1], NULL, live_life, &shared_data);
        i++;
    }
    i = 1;
    while (i <= 5)
    {
        pthread_join(threads[i - 1], NULL);
        i++;
    }
}