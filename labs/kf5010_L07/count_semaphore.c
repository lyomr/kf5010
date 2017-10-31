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

bool flashing = false;

long long count1;
long long count2;
long long total;

static sem_t sem;

void random_delay(void) {
    int delay = rand() % 100;
    int i;

    for (i = 0; i < delay; i+=1) {
        /* skip */
    }
}

void *led_toggle_thr(void * arg) {
    while (true) {
        if (flashing) {
            led_toggle((leds_t)arg);
            sleep(1);
        }
    }
}

void *count1_thr(void * arg) {
    int rc;

    while (!flashing) {
        rc = sem_wait(&sem);
        assert(rc == 0);

        count1 += 1;
        random_delay();
        total += 1;
        if ((count1 + count2) != total) {
            flashing = true;
        }
        /*lcd_set_pos(1, 0);*/
        /*lcd_write("count1 = %20d", count1);*/
        lcd_write_at(1, 0, "count1 = %20d", count1);

        rc = sem_post(&sem);
        assert(rc == 0);
    }
    while (true) {
        /* skip */
    }
}

void *count2_thr(void * arg) {
    int rc;

    while (!flashing) {
        rc = sem_wait(&sem);
        assert(rc == 0);

        count2 += 1;
        random_delay();
        total += 1;
        if ((count1 + count2) != total) {
            flashing = true;
        }
        /*lcd_set_pos(2, 0);*/
        /*lcd_write("count2 = %20d", count2);*/
        lcd_write_at(2, 0, "count2 = %20d", count2);

        rc = sem_post(&sem);
        assert(rc == 0);
    }
    while (true) {
        /* skip */
    }
}

int main (void) {
    pthread_t thread[3];
    int rc;

    console_init();
    srand(time(NULL));
    rc = sem_init(&sem, 0, 1);
    assert(rc == 0);

    rc = pthread_create(&thread[0], NULL, led_toggle_thr, (void *)LED_RED);
    assert(rc == 0);
    rc = pthread_create(&thread[1], NULL, count1_thr, NULL);
    assert(rc == 0);
    rc = pthread_create(&thread[2], NULL, count2_thr, NULL);
    assert(rc == 0);

    while (true) {
        /* skip */
    }
    exit(0);
}
