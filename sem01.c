
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
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

int main(int argc, char const *argv[])
{
    int semid;
    semid = sem_create(1234);

    sem_setval(semid, 2);

    int ret = sem_getval(semid);
    assert(ret == 2);

    sem_p(semid);
    ret = sem_getval(semid);
    assert(ret == 1);

    sem_p(semid);
    ret = sem_getval(semid);
    assert(ret == 2);

    sem_v(semid);
    ret = sem_getval(semid);
    assert(ret == 2);

    sem_d(semid);

    return 0;
}
