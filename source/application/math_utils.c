#include "fm_radio.h"


int32_t fast_atan2(int32_t y, int32_t x) {
    int32_t yabs, angle;
    int32_t pi4 = (1 << 12), pi34 = 3 * (1 << 12); // note pi = 1<<14

    if (x == 0 && y == 0) {
        return 0;
    }

    yabs = y;

    if (yabs < 0) {
        yabs = -yabs;
    }

    if (x >= 0) {
        angle = pi4  - pi4 * (x - yabs) / (x + yabs);

    } else {
        angle = pi34 - pi4 * (x + yabs) / (yabs - x);
    }

    if (y < 0) {
        return -angle;
    }

    return angle;
}

void multiply(int32_t ar, int32_t aj, int32_t br, int32_t bj, int32_t* cr, int32_t* cj) {
    *cr = ar * br - aj * bj;
    *cj = aj * br + ar * bj;
}

int32_t polar_disc_fast(int32_t ar, int32_t aj, int32_t br, int32_t bj) {
    int32_t cr, cj;
    multiply(ar, aj, br, -bj, &cr, &cj);
    return fast_atan2(cj, cr);
}
