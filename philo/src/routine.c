#include "philo.h"

static int sim_stopped(t_data *data)
{
    int stopped;

    pthread_mutex_lock(&data->lock_mtx);
    stopped = data->stop_simulation;
    pthread_mutex_unlock(&data->lock_mtx);
    return (stopped);
}

static void smart_sleep(t_data *data, long ms)
{
    long start;
    long now;

    start = get_time_ms();
    if (start == -1)
        return;
    while (1)
    {
        if (sim_stopped(data))
            return;
        now = get_time_ms();
        if (now == -1)
            return;
        if (now - start >= ms)
            break;
        usleep(1000);
    }
}

static void take_forks(t_philo *philo)
{
    t_data *data;

    data = philo->data;
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->right_fork);
        safe_print(data, philo->id, "has taken a fork");
        pthread_mutex_lock(philo->left_fork);
        safe_print(data, philo->id, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        safe_print(data, philo->id, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        safe_print(data, philo->id, "has taken a fork");
    }
}

static void *one_philo_routine(t_philo *philo)
{
    t_data *data;

    data = philo->data;
    pthread_mutex_lock(&data->lock_mtx);
    philo->last_meal = get_time_ms();
    pthread_mutex_unlock(&data->lock_mtx);
    pthread_mutex_lock(philo->left_fork);
    safe_print(data, philo->id, "has taken a fork");
    smart_sleep(data, data->t_die);
    pthread_mutex_unlock(philo->left_fork);
    return (NULL);
}

void *philo_routine(void *arg)
{
    t_philo *philo;
    t_data *data;

    philo = (t_philo *)arg;
    data = philo->data;

    if (data->n_philos == 1)
        return (one_philo_routine(philo));
    pthread_mutex_lock(&data->lock_mtx);
    philo->last_meal = get_time_ms();
    pthread_mutex_unlock(&data->lock_mtx);
    if (philo->id % 2 == 0)
        usleep(data->t_eat * 1000 / 2);
    while (!sim_stopped(data))
    {
        safe_print(data, philo->id, "is thinking");
        take_forks(philo);
        pthread_mutex_lock(&data->lock_mtx);
        philo->last_meal = get_time_ms();
        philo->meals++;
        pthread_mutex_unlock(&data->lock_mtx);
        safe_print(data, philo->id, "is eating");
        smart_sleep(data, data->t_eat);

        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        safe_print(data, philo->id, "is sleeping");
        smart_sleep(data, data->t_sleep);
    }
    return (NULL);
}