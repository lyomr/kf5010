#include <unistd.h>
#include <assert.h>
#include <pthread.h>

#include "console.h"

enum {
    BASE_PRIORITY = 1,
    N_THREADS = 2,
};

static pthread_attr_t attr;
static pthread_t thread[N_THREADS];
static pthread_barrier_t barrier;

static void *count_thr(void *arg);

int main(void) {
    struct sched_param fifo_param;
    int rc;
    unsigned long i;

    console_init();
    rc = pthread_barrier_init(&barrier, NULL, N_THREADS);
    assert(rc == 0);
    rc = pthread_attr_init(&attr);
    assert(rc == 0);
    rc = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    assert(rc == 0);
    rc = pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
    assert(rc == 0);
    rc = pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
    assert(rc == 0);

    for (i = 0; i < N_THREADS; i += 1) {
        fifo_param.sched_priority = BASE_PRIORITY + i;
        rc = pthread_attr_setschedparam(&attr, &fifo_param);
        assert(rc == 0);
        rc = pthread_create(&thread[i], &attr, count_thr, (void *)i);
        assert(rc == 0);
    }

    while (true) {
        /* skip */
    }
    return 0;
}

static void *count_thr(void *arg) {
    unsigned long id = (unsigned long)arg;
    unsigned long counter = 0;
    int rc;
    
    rc = pthread_barrier_wait(&barrier);
    assert(rc == 0 || rc == PTHREAD_BARRIER_SERIAL_THREAD);
    while (true) {
        lcd_write_at(id, 0, "Thread %ld : %010ld", id, counter);
        counter += 1;
        /*usleep(100000);*/
    }
    pthread_exit(0);
}

