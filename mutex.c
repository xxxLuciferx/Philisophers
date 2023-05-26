#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>

pthread_mutex_t lock2;

void *work(void *arg)
{
	pthread_mutex_t *lock = (pthread_mutex_t *)arg;

	while (1)
	{
		pthread_mutex_lock(&lock2);
		pthread_mutex_lock(lock);
		printf(" hello ");
		printf(" hello ");
		printf(" hello ");
		usleep(100000);
		printf(" hello ");
		printf(" hello ");
		printf(" hello\n");
		pthread_mutex_unlock(lock);
		usleep(100000);
		pthread_mutex_unlock(&lock2);
	}
	return (NULL);
}

int main()
{
	pthread_t khalil[5];
	// pthread_mutex_t lock[5];
	pthread_mutex_t *lock;

	lock = malloc(sizeof(pthread_mutex_t));

	pthread_mutex_init(lock, NULL);
	pthread_mutex_init(&lock2, NULL);
	int i = 0;
	while (i < 5)
	{
		pthread_create(&khalil[i], NULL, &work, lock);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		pthread_join(khalil[i], NULL);
		i++;
	}
}