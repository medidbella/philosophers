#include <sys/time.h>
#include <stdio.h>

int main()
{
	struct timeval start;
	gettimeofday(&start, NULL);

	
	printf("tv_sec = %ld\n tv_usec = %ld\n", start.tv_sec, start.tv_usec);
}