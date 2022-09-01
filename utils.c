#include "philosophers.h"
#include <sys/time.h>

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	// als het mis gaat. Protecten
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
