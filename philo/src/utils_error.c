#include "philo.h"

int error(const char *msg)
{
    printf("Error: %s\n", msg);
    return (0);
}

int error2(const char *msg, const char *name)
{
    printf("Error: %s %s\n", msg, name);
    return (0);
}