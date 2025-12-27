#include "str2int.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int str2int(const char* str)
{
	if (str == NULL || *str == '\0')
	{
		abort();
	}

	int sign = 1;
	long long result = 0;
	int i = 0;

	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
	{
		i++;
	}

	if (str[i] == '\0')
	{
		abort();
	}

	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
		{
			abort();
		}

		int digit = str[i] - '0';

		if (result > (LLONG_MAX - digit) / 10)
		{
			abort();
		}

		result = result * 10 + digit;

		if ((sign == 1 && result > INT_MAX) ||
			(sign == -1 && result > (long long)INT_MAX + 1))
		{
			abort();
		}

		i++;
	}

	result *= sign;

	if (result < INT_MIN || result > INT_MAX)
	{
		abort();
	}

	return (int)result;
}