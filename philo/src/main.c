#include "philo.h"

int main(int argc, char **argv)
{
    t_data data;

    if (!parse_args(argc, argv, &data))
        return (1);
    if (!init_data(&data))
        return (1);
    if (!init_philos(&data))
    {
        cleanup(&data);
        return (1);
    }
    if (!start_simulation(&data))
    {
        cleanup(&data);
        return (1);
    }
    cleanup(&data);
    return (0);
}