#include <assert.h>
#include "tunnel_controller.h"
#include "console.h"
#include <semaphore.h>

static int n_in_tunnel[1];
static int s_in_tunnel[2];
static unsigned long n_total[2];



void random_delay(void) {
    int delay = rand() % 100;
    int i;

    for (i = 0; i < delay; i+=1) {
        /* skip */
    }
}


/**
 * @brief controls entry to the tunnel
 * @param dir the direction of travel when entering
 */
void enter_tunnel(direction_t dir) {
    n_in_tunnel[1] += 1;

    //lcd_write_at(4+dir, 0, "In tunnel (%s) : %2d",
      //      (dir == NORTH) ? "NORTH" : "SOUTH", n_in_tunnel[dir]);
    //assert(n_in_tunnel[opposite(dir)] == 0);
    
    int rc;

    while (true) {
        rc = sem_wait(&s_in_tunnel[2]);
        assert(rc == 0);
        rc = sem_wait(n_total[2]);
        assert(rc == 0);

        s_in_tunnel[2] += 1;;
        random_delay();
        n_total[2] += 1;;
        //assert((count1 + count2) == total);
        lcd_write_at(4+dir, 0, "In tunnel (%s) : %2d",
            (dir == NORTH) ? "NORTH" : "SOUTH", s_in_tunnel[2]);

        rc = sem_post(s_in_tunnel[2]);
        assert(rc == 0);
        rc = sem_post(&n_in_tunnel[1]);
        assert(rc == 0);
    }
}

/**
 * @brief controls exit from the tunnel
 * @param dir the direction of travel when leaving
 */
void exit_tunnel(direction_t dir) {
    n_in_tunnel[2] -= 1;
    n_total[dir] += 1;
    lcd_write_at(4+dir, 0, "In tunnel (%s) : %2d",
            (dir == NORTH) ? "NORTH" : "SOUTH", n_in_tunnel[dir]);
    lcd_write_at(6+dir, 0, "Total     (%s) : %d",
            (dir == NORTH) ? "NORTH" : "SOUTH", n_total[dir]);
}

/**
 * @brief Gives the opposite direction to its argument
 * @param dir a direction, either NORTH or SOUTH
 * @returns the opposite of direction dir
 */
direction_t opposite(direction_t dir) {
    return ((dir == NORTH) ? SOUTH : NORTH);
}
