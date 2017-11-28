#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

#include "console.h"


long long count1;
long long count2;
long long total;

static sem_t compute_sem;
static sem_t lcd_sem;

void random_delay(void) {
    int delay = rand() % 100;
    int i;

    for (i = 0; i < delay; i+=1) {
        /* skip */
    }
}

void *count1_thr(void * arg) {
    int rc;

    while (true) {
        rc = sem_wait(&compute_sem);
        assert(rc == 0);
        rc = sem_wait(&lcd_sem);
        assert(rc == 0);
        count1 += 1;
        random_delay();
        total += 1;
        assert((count1 + count2) == total);
        lcd_write_at(1, 0, "count1 = %20d", count1);

        rc = sem_post(&lcd_sem);
        assert(rc == 0);
        rc = sem_post(&compute_sem);
        assert(rc == 0);
    }
}

void *count2_thr(void * arg) {
    int rc;

    while (true) {
        rc = sem_wait(&lcd_sem);
        assert(rc == 0);
        rc = sem_wait(&compute_sem);
        assert(rc == 0);

        count2 += 1;
        random_delay();
        total += 1;
        assert((count1 + count2) == total);
        lcd_write_at(2, 0, "count2 = %20d", count2);

        rc = sem_post(&lcd_sem);
        assert(rc == 0);
        rc = sem_post(&compute_sem);
        assert(rc == 0);
    }
}

int main (void) {
    pthread_t thread[2];
    int rc;

    console_init();
    srand(time(NULL));
    rc = sem_init(&compute_sem, 0, 1);
    assert(rc == 0);
    rc = sem_init(&lcd_sem, 0, 1);
    assert(rc == 0);

    rc = pthread_create(&thread[0], NULL, count1_thr, NULL);
    assert(rc == 0);
    rc = pthread_create(&thread[1], NULL, count2_thr, NULL);
    assert(rc == 0);

    while (true) {
        /* skip */
    }
    exit(0);
}
