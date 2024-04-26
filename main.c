#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int counter;
pthread_mutex_t mutex;
void thread_fn1()
{
	int i = 0;
	while (i++ < 100000)
	{
		pthread_mutex_lock(&mutex);
		counter++;
		pthread_mutex_unlock(&mutex);
	}
}


int main(void)
{
	pthread_t thread1;
	pthread_t thread2;
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&thread1, NULL, (void *(*)(void *))thread_fn1, NULL);
	pthread_create(&thread2, NULL, (void *(*)(void *))thread_fn1, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_mutex_destroy(&mutex);
	printf("counter = %d\n", counter);
	return (0);
}