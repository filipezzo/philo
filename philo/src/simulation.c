#include "philo.h"

int start_simulation(t_data *data)
{
    size_t i;
    pthread_t monitor_thread;

    data->start_time = get_time_ms();
    i = 0;
    while (i < (size_t)data->n_philos)
    {
        if (pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]) != 0)
            return error("while creating philo thread");
        i++;
    }
    if (pthread_create(&monitor_thread, NULL, monitor_routine, data) != 0)
        return error("while creating monitor thread");
    i = 0;
    while (i < (size_t)data->n_philos)
    {
        if (pthread_join(data->philos[i].thread, NULL) != 0)
            return error("waiting for philo thread");
        i++;
    }
    if (pthread_join(monitor_thread, NULL) != 0)
        return error("waiting for monitor thread");

    return (1);
}