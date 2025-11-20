#include "philo.h"

int init_data(t_data *data)
{
    size_t i;
    data->start_time = 0;
    data->stop_simulation = 0;
    data->philos = NULL;
    data->forks = NULL;
    data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
    if (!data->forks)
        return error("Malloc failed for forks");
    i = 0;
    while (i < (size_t)data->n_philos)
    {
        if (pthread_mutex_init(&data->forks[i], NULL) != 0)
        {
            size_t j;

            j = 0;
            while (j < i)
            {
                pthread_mutex_destroy(&data->forks[j]);
                j++;
            }
            free(data->forks);
            data->forks = NULL;
            return (error("fail to init fork mutex"));
        }
        i++;
    }
    if (pthread_mutex_init(&data->lock_mtx, NULL) != 0)
    {
        i = 0;
        while (i < (size_t)data->n_philos)
        {
            pthread_mutex_destroy(&data->forks[i]);
            i++;
        }
        free(data->forks);
        data->forks = NULL;
        return error("failed to init global mutex");
    }
    return (1);
}