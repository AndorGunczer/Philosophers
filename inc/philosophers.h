/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:09:50 by agunczer          #+#    #+#             */
/*   Updated: 2022/02/16 13:37:48 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# include <stdlib.h>

# define TAKEN 0
# define AVAILABLE 1

// typedef struct s_shared {
// 	int				*fork;
// 	int				death;
// 	int				philo_id;
// 	pthread_mutex_t	mutex_forks;
// 	pthread_mutex_t	mutex_waiter;
// 	pthread_mutex_t	mutex_death;
// 	pthread_mutex_t	mutex_print;
// 	struct timeval	timestamp;
// 	double			start;
// }	t_shared;

typedef enum e_state {
	eating = 1,
	sleeping = 2,
	thinking = 3,
	dead = 4
}	t_state;

typedef struct s_input {
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	struct timeval	timestamp;
	double			start;
}	t_input;

typedef struct s_philo {
	int				id;
	int				amount_meal;
	volatile int	*death;
	long			last_meal;
	pthread_mutex_t	*mutex_lfork;
	pthread_mutex_t *mutex_rfork;
	pthread_mutex_t	*mutex_end;
	pthread_mutex_t	*mutex_death;
	pthread_mutex_t	*mutex_print;
	t_input			*input;
	pthread_t		philosopher;
	t_state			state;
}	t_philo;

/*	death.c */
int		is_dead(t_philo *philo);

/*  utlis.c */
int		ft_atoi(const char *str);
int		ft_log(t_philo *philo, char *event, int exception);
int		is_num(char *str);

/*  philo.c */
int		fill_philosophers(t_input *input, t_philo *philo, int i);
t_philo	*create_philosopher(t_input *input);
void	*routine(void *arg);

/*  main.c */

/*	time.c */
long		get_time();
int			ft_sleep(long duration, t_philo *philo);

/*	string.c */
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_buff(char *s, char **ptr);
void	ft_putnbr_buff(long n, char **ptr);

#endif