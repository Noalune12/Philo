#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// int mails = 0;
// pthread_mutex_t mutex;

// void*	routine()
// {
// 	// printf("test from threads\n");
// 	// sleep(3);
// 	// printf("ending threads\n\n");
// 	for (int i = 0; i < 1000000; i++) //memory race problem
// 	{
// 		pthread_mutex_lock(&mutex); //handle race problem - one thread will access to the section, the other one wait for its turn
// 		mails++;
// 		pthread_mutex_unlock(&mutex);
// 		// read mails
// 		// increment
// 		// write mails
// 	}
// 	return (NULL);
// }

// int main(int ac, char **av)
// {
// 	// pthread_t	t1, t2;
// 	pthread_t	t1[4];
// 	int i;
// 	pthread_mutex_init(&mutex, NULL);
// 	for (i = 0; i < 4; i++)
// 	{
// 		if (pthread_create(t1 + i, NULL, &routine, NULL) != 0) //return an int
// 			return (1);
// 		printf("Thread %d has started\n", i);
// 	}
// 	for (i = 0; i < 4; i++)
// 	{
// 		if (pthread_join(t1[i], NULL))
// 			return (2);
// 		printf("Thread %d has finished execution\n", i);
// 	}
// 	// if (pthread_create(&t1, NULL, &routine, NULL) != 0) //return an int
// 	// 	return (1);
// 	// if (pthread_create(&t2, NULL, &routine, NULL) != 0)
// 	// 	return (2);
// 	// if (pthread_join(t1, NULL) != 0)
// 	// 	return (3);
// 	// if (pthread_join(t2, NULL) != 0)
// 	// 	return (4);
// 	pthread_mutex_destroy(&mutex);
// 	printf("%d\n", mails);
// 	return (0);
// }

// #include <time.h>

// void*	roll_dice()
// {
// 	int value = (rand() % 6) + 1;
// 	int *result = malloc(sizeof(int));
// 	*result = value;
// 	printf("%d\n", value);
// 	printf("%p\n", result);
// 	return ((void*) result);
// }

// int main(int ac, char **av)
// {
// 	int *res;
// 	srand(time(NULL));
// 	pthread_t	th;
// 	if (pthread_create(&th, NULL, &roll_dice, NULL) != 0)
// 			return (1);
// 	if (pthread_join(th, (void **) &res) != 0)
// 		return (2);
// 	printf("result: %d, %p\n", *res, res);
// 	free(res);
// 	return (0);
// }

// int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

// void* routine(void *ptr)
// {
// 	int index = *(int *)ptr;
// 	printf("%d ", primes[index]);
// 	free(ptr);
// }

// int main(int ac, char **av)
// {
// 	pthread_t th[10];
// 	int i;
// 	for (i = 0; i < 10; i++)
// 	{
// 		int* a = malloc(sizeof(int));
// 		*a = i;
// 		if (pthread_create(&th[i], NULL, &routine, a) != 0)
// 			return (1);
// 	}
// 	for (i = 0; i < 10; i++)
// 	{
// 		if (pthread_join(th[i], NULL) != 0)
// 			return (1);
// 	}
// }


// int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

// void* routine(void *ptr)
// {
// 	int index = *(int *)ptr;
// 	int sum = 0;
// 	for (int j = 0; j < 5; j++)
// 		sum += primes[index + j];
// 	printf("Local sum = %d\n", sum);
// 	*(int*)ptr = sum;
// 	return ptr;
// }

// int main(int ac, char **av)
// {
// 	pthread_t th[2];
// 	int i;
// 	for (i = 0; i < 2; i++)
// 	{
// 		int* a = malloc(sizeof(int));
// 		*a = i * 5;
// 		if (pthread_create(&th[i], NULL, &routine, a) != 0)
// 			return (1);
// 	}
// 	int globalsum = 0;
// 	for (i = 0; i < 2; i++)
// 	{
// 		int* res;
// 		if (pthread_join(th[i], (void **) &res) != 0)
// 			return (1);
// 		globalsum += *res;
// 		free(res);
// 	}
// 	printf("sum = %d\n", globalsum);
// }

#define THREAD_NUM 2

void* routine()
{
	// pthread_t th = pthread_self();
	// printf("%lu\n", th);
	sleep(1);
	printf("finish execution\n");
}

int main(int ac, char **av)
{
	pthread_t th[THREAD_NUM];
	pthread_attr_t detachedthread;
	pthread_attr_init(&detachedthread);
	pthread_attr_setdetachstate(&detachedthread, PTHREAD_CREATE_DETACHED);
	int i;
	for (i = 0; i < THREAD_NUM; i++)
	{
		if (pthread_create(&th[i], &detachedthread, &routine, NULL) != 0)
			perror("failed to create");
		// printf("%lu\n", th[i]);
		pthread_detach(th[i]);
	}
	// for (i = 0; i < THREAD_NUM; i++)
	// {
	// 	if (pthread_join(th[i], NULL) != 0)
	// 		perror("failed to join");
	// }
	pthread_attr_destroy(&detachedthread);
	pthread_exit(0);
}
