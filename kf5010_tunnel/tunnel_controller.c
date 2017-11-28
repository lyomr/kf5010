#include <assert.h>
#include "tunnel_controller.h"
#include "console.h"

static int n_in_tunnel[2];
static unsigned long n_total[2];

/**
 * @brief controls entry to the tunnel
 * @param dir the direction of travel when entering
 */
void enter_tunnel(direction_t dir) {
    n_in_tunnel[dir] += 1;

    lcd_write_at(4+dir, 0, "In tunnel (%s) : %2d",
            (dir == NORTH) ? "NORTH" : "SOUTH", n_in_tunnel[dir]);
    /*assert(n_in_tunnel[opposite(dir)] == 0);*/
}

/**
 * @brief controls exit from the tunnel
 * @param dir the direction of travel when leaving
 */
void exit_tunnel(direction_t dir) {
    n_in_tunnel[dir] -= 1;
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
