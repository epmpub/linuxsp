#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <sys/timerfd.h>

#define handle_error(msg) \
    do{perror(msg);exit(EXIT_FAILURE);}while(0)

void print_time ()
{
    struct timeval tv;
    gettimeofday (&tv, NULL);
    printf ("current time: %ld.%ld\n", tv.tv_sec, tv.tv_usec);
}

int main (int argc, char *argv[])
{
    struct timespec now;
    if (clock_gettime (CLOCK_REALTIME, &now) == -1)
        handle_error ("clock_gettime");

    struct itimerspec new_value;
    new_value.it_value.tv_sec = now.tv_sec + 10; // 10s later,timer will timeout
    new_value.it_value.tv_nsec = now.tv_nsec;
    new_value.it_interval.tv_sec = 3;  //timer intelval
    new_value.it_interval.tv_nsec = 0;

    int fd = timerfd_create (CLOCK_REALTIME, 0);
    if (fd == -1)
        handle_error ("timerfd_creat");
    if (timerfd_settime(fd, TFD_TIMER_ABSTIME, &new_value, NULL) == -1)
        handle_error ("timerfd_settime");

    print_time ();
    printf ("timer started\n");

    for (uint64_t tot_exp = 0; tot_exp < 20;) //timer run times: 20
    {
        uint64_t exp;
        ssize_t s = read (fd, &exp, sizeof(uint64_t));
        if (s != sizeof(uint64_t))
            handle_error ("read");
        tot_exp += exp;
        print_time ();
        printf ("read: %llu, total: %llu\n", exp, tot_exp);
    }

    return 0;
    
}

