#include "philo.h"

int	init_master(t_master *master, int ac, char **av);
int	validate_args(int ac, char **av, int i, int j);
int	init_values(int ac, char **av, t_master *master, int i);
int	create_philo_thread(t_master *master, int *i);
void	lock_fork(t_philo *info);
void	unlock_fork(t_philo *info);
void	print_msg(t_philo *info, char *str);

int	main(int ac, char **av)
{
	static t_master	master;
	int				i;

	if (init_master(&master, ac, av) == -1)
		return (1);
	i = 0;
	while (i < master.philos)
	{
		pthread_mutex_destroy(&master.forks[i++]);
	}
	free(master.forks);
	i = 0;
	usleep(20000);
	while (i < master.philos)
	{
		if (master.arr_philos[i])
			free(master.arr_philos[i]);
		i++;
	}
	free(master.arr_philos);
	return (0);
}

void	*philo_routine(void *data)
{
	t_philo *info;

	info = (t_philo *)data;

	while(get_time() < info->master->start)
		usleep(200);
	while (info->master->meals == -1 || info->courses <= info->master->meals)
	{
		lock_fork(info);
		print_msg(info, "is eating");
		usleep(info->master->eat_time);
		unlock_fork(info);
		info->last_meal = get_time();
		if (info->master->meals != -1)
			info->courses++;
		print_msg(info, "is sleeping");
		usleep(info->master->sleep_time);
		print_msg(info, "is thinking");
		usleep(info->master->think_time);
	}
	return NULL;
}

void	lock_fork(t_philo *info)
{
	if (info->id % 2 == 0)
	{
		if (pthread_mutex_lock(info->right_fork) == 0)
			print_msg(info, "has taken right_fork");
		if (pthread_mutex_lock(info->left_fork) == 0)
			print_msg(info, "has taken left_fork");
	}
	else
	{
		if (pthread_mutex_lock(info->left_fork) == 0)
			print_msg(info, "has taken left_fork");
		if (pthread_mutex_lock(info->right_fork) == 0)
			print_msg(info, "has taken right_fork");
	}
}

void	unlock_fork(t_philo *info)
{
	if (info->id % 2 == 0)
	{
		pthread_mutex_unlock(info->right_fork);
		pthread_mutex_unlock(info->left_fork);
	}
	else
	{
		pthread_mutex_unlock(info->left_fork);
		pthread_mutex_unlock(info->right_fork);
	}
}

void	print_msg(t_philo *info, char *str)
{
	long	time_atm;

	time_atm = get_time();
	printf("%li %i %s\n", time_atm-info->master->start, info->id, str);
}

int	init_master(t_master *master, int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf("Four (max five) arguments are required!\n");
		return (-1);
	}
	if (validate_args(ac, av, 1, 0) == -1)
		return (-1);
	if (init_values(ac, av, master, 0))
		return (-1);

	printf("Todays crew:\n\tStart time: %li\n\tPhilos: %li\n\tTime_to die: %li\n\tTime_to eat: %li\n\tTime_to sleep: %li\n\tMeals amount: %li\n", master->start, master->philos, master->think_time, master->eat_time, master->sleep_time, master->meals);
	return (0);
}

int	validate_args(int ac, char **av, int i, int j)
{
	while (i < ac)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if (av[i][0] == '0' || !(av[i][j] >= '0' && av[i][j] <= '9'))
			{
				printf("Only positive integers allowed as arguments!\n");
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	init_values(int ac, char **av, t_master *master, int i)
{
	master->philos = p_atol(av[1]);
	master->start = get_time() + (62 * master->philos);
	master->think_time = p_atol(av[2]);
	master->eat_time = p_atol(av[3]);
	master->sleep_time = p_atol(av[4]);
	if (ac == 6)
		master->meals = p_atol(av[5]);
	else
		master->meals = -1;
	if (master->think_time < 60 || master->eat_time < 60 || master->sleep_time < 60)
		return (printf("Time values must be creater than 60\n"));
	master->arr_philos = malloc(sizeof(t_philo*) * master->philos);
	if (!master->arr_philos)
		return (printf("Philos array allocation failed\n"));
	memset(master->arr_philos, '\0', sizeof(t_philo*) * master->philos);
	master->forks = malloc(sizeof(pthread_mutex_t) * master->philos);
	if (!master->forks)
		return (printf("Forks allocation failed\n"));
	memset(master->forks, '\0', sizeof(pthread_mutex_t) * master->philos);
	while (i < master->philos)
	{
		if (pthread_mutex_init(&master->forks[i], NULL) != 0)
		{
			while (--i >= 0)
			{
				pthread_mutex_destroy(&master->forks[i--]);
			}
			free(master->forks);
			return (printf("Mutex init failed\n"));
		}
		i++;
	}
	i = 0;
	while (i < master->philos)
	{
		if (create_philo_thread(master, &i))
			return (-1);
	}
	i = 0;
	while (i < master->philos)
		pthread_join(master->arr_philos[i++]->phil, NULL);
	return (0);
}

int	create_philo_thread(t_master *master, int *i)
{
	t_philo		*phil_data;

	phil_data = malloc(sizeof(t_philo));
	if (!phil_data)
	{
		while (*i >= 0)
		{
			if (master->arr_philos[*i])
				free(master->arr_philos[*i]);
			(*i)--;
		}
		free(master->arr_philos);
		return (printf("Philo_data allocation failed\n"));
	}
	phil_data->id = *i + 1;
	phil_data->left_fork = &master->forks[*i];
	phil_data->right_fork = &master->forks[(*i + 1) % master->philos];
	phil_data->last_meal = get_time();
	phil_data->courses = 0;
	phil_data->master = master;
	master->arr_philos[*i] = phil_data;
	pthread_create(&master->arr_philos[*i]->phil, NULL, philo_routine, master->arr_philos[*i]);
	printf("Yes\n");
	printf("Created philo nr %i\nTime: %li\n", *i, get_time());
	(*i)++;
	return (0);
}
