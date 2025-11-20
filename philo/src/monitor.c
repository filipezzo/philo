#include "philo.h"

void *monitor_routine(void *arg)
{
    t_data *data;
    int finished;
    long now;
    long diff;
    size_t i;

    data = (t_data *)arg;

    while (1)
    {
        finished = 0;
        i = 0;
        while (i < (size_t)data->n_philos)
        {
            pthread_mutex_lock(&data->lock_mtx);
            if (data->stop_simulation)
            {
                pthread_mutex_unlock(&data->lock_mtx);
                return (NULL);
            }
            now = get_time_ms();
            diff = now - data->philos[i].last_meal;
            if (diff > data->t_die && !data->stop_simulation)
            {
                data->stop_simulation = 1;
                pthread_mutex_unlock(&data->lock_mtx);
                safe_print(data, data->philos[i].id, "died");
                return (NULL);
            }
            if (data->must_eat > 0 && data->philos[i].meals >= data->must_eat)
                finished++;
            pthread_mutex_unlock(&data->lock_mtx);
            i++;
        }

        if (data->must_eat > 0 && finished == data->n_philos)
        {
            pthread_mutex_lock(&data->lock_mtx);
            data->stop_simulation = 1;
            pthread_mutex_unlock(&data->lock_mtx);
            return (NULL);
        }
        usleep(1000);
    }
    return (NULL);
}