#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define ERR_EXIT(m)         \
	do                      \
	{                       \
		perror(m);          \
		exit(EXIT_FAILURE); \
	} while (0)

typedef struct tsd
{
	pthread_t tid;
	char *str;
} tsd_t;

pthread_once_t once_control = PTHREAD_ONCE_INIT;
pthread_key_t key_tsd;

void destory_routine(void *value)
{
	printf("destory.\n");
	free(value);
}

void once_routine(void)
{
	pthread_key_create(&key_tsd, destory_routine);
	printf("key init ..\n");

}
void *thread_routine(void *arg)
{

	pthread_once(&once_control, once_routine);

	tsd_t *value = (tsd_t *)malloc(sizeof(tsd_t));
	value->tid = pthread_self();
	value->str = (char *)arg;

	pthread_setspecific(key_tsd, value);
	printf("%s setspecific %p\n", (char *)arg, value);

	value = pthread_getspecific(key_tsd);
	printf("id=%d,str = %s\n", value->tid, value->str);
	sleep(2);

	value = pthread_getspecific(key_tsd);
	printf("id=%d,str = %s\n", value->tid, value->str);

	return NULL;
}

int main(void)
{

	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, thread_routine, "thread1");
	pthread_create(&tid2, NULL, thread_routine, "thread2");

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	pthread_key_delete(key_tsd);

	return 0;
}
