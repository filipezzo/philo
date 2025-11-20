#include "philo.h"

long ph_atol(const char *str)
{
    size_t i;
    long result;

    i = 0;
    result = 0;
    while (is_space(str[i]))
        i++;
    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            return error("The value must be a positive number");
        i++;
    }
    if (!is_digit(str[i]))
        return error("The value must be a number");
    while (is_digit(str[i]))
    {
        result = (result * 10) + (str[i] - '0');
        i++;
    }
    while (is_space(str[i]))
        i++;
    if (str[i] != '\0')
        return error("The value must be a number");
    if (result > INT_MAX)
        return error("The value cannot be higher than 2147483647");
    return (result);
}