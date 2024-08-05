
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

#include <assert.h>

#define ERR_EXIT(m)         \
    do                      \
    {                       \
        perror(m);          \
        exit(EXIT_FAILURE); \
    } while (0)

union semun
{
    int val;               /* Value for SETVAL */
    struct semid_ds *buf;  /* Buffer for IPC_STAT, IPC_SET */
    unsigned short *array; /* Array for GETALL, SETALL */
    struct seminfo *__buf; /* Buffer for IPC_INFO
                              (Linux-specific) */
};

int sem_create(key_t key)
{
    int semid;
    semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1)
    {
        ERR_EXIT("semget");
    }
    return semid;
}

int sem_open(key_t key)
{
    int semid;
    semid = semget(key, 0, 0);
    if (semid == -1)
    {
        ERR_EXIT("semget");
    }
    return semid;
}

int sem_setval(int semid, int val)
{
    union semun su;
    su.val = val;
    int ret;
    ret = semctl(semid, 0, SETVAL, su);
    if (ret == -1)
    {
        ERR_EXIT("sem setval");
    }
    return 0;
}

int sem_getval(int semid)
{
    int ret;
    ret = semctl(semid, 0, GETVAL, 0);
    if (ret == -1)
    {
        ERR_EXIT("sem getval");
    }
    return ret;
}

int sem_d(int semid)
{
    int ret;
    ret = semctl(semid, 0, IPC_RMID, 0);
    if (ret == -1)
    {
        ERR_EXIT("semctl");
    }
    return 0;
}

int sem_p(int semid)
{
    struct sembuf sb = {0, -1, 0};
    int ret;
    ret = semop(semid, &sb, 1);
    if (ret == -1)
    {
        ERR_EXIT("semop");
    }
    return ret;
}

int sem_v(int semid)
{
    struct sembuf sb = {0, 1, 0};
    int ret;
    ret = semop(semid, &sb, 1);
    if (ret == -1)
    {
        ERR_EXIT("semop");
    }
    return ret;
}

int semid;

void print(char op_char)
{
    int pause_time;
    srand(getpid());
    for (int i = 0; i < 10; i++)
    {
        sem_p(semid);

        printf("%c", op_char);
        fflush(stdout);
        pause_time = rand() % 3;
        sleep(pause_time);
        
        printf("%c", op_char);
        fflush(stdout);

        sem_v(semid);
        pause_time = rand() % 2;
        sleep(pause_time);
    }
}
int main(int argc, char const *argv[])
{
    semid = sem_create(IPC_PRIVATE);
    sem_setval(semid, 0);
    pid_t pid;
    pid = fork();
    if (pid == -1)
    {
        ERR_EXIT("fork");
    }
    if (pid > 0)
    {
        sem_setval(semid,1);
        print('o');
        wait(NULL);
        sem_d(semid);
    }
    else
    {
        print('x');
    }

    return 0;
}
