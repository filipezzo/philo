#include "philo.h"

long get_time_ms(void)
{
    struct timeval time;
    long ms;

    if (gettimeofday(&time, NULL) != 0)
        return (-1);
    ms = time.tv_sec * 1000L + time.tv_usec / 1000L;
    return (ms);
}