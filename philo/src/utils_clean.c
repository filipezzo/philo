#include "philo.h"

void cleanup(t_data *data)
{
    size_t i;

    if (data->forks)
    {
        i = 0;
        while (i < (size_t)data->n_philos)
        {
            pthread_mutex_destroy(&data->forks[i]);
            i++;
        }
        free(data->forks);
        data->forks = NULL;
    }
    pthread_mutex_destroy(&data->lock_mtx);
    if (data->philos)
    {
        free(data->philos);
        data->philos = NULL;
    }
}