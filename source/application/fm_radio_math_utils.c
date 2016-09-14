#include "fm_radio.h"

// atan2 approximation taken from librtlsdr
int32_t fmradio_atan2(int32_t y, int32_t x) {
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

// fm demodulation math taken from librtlsdr
int32_t fmradio_polar_disc(int32_t ar, int32_t aj, int32_t br, int32_t bj) {

    // complex multiply first sample with
    // second sample flipped over the real axis
    // (ar+aj) * (br-bj)
    int32_t cr = ar * br - aj * -bj;
    int32_t cj = aj * br + ar * -bj;

    // find angle of resultant
    return fmradio_atan2(cj, cr);
    
}
