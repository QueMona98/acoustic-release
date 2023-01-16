#ifndef SIGDET_H_
#define SIGDET_H_

#include "main.h"

/*#define SIGNAL_RADIUS 5
#define NOISE_RADIUS 50
#define SIGNAL_NOISE_RATIO_MIN 0.15*/

#define SIGNAL_RADIUS 2
#define NOISE_RADIUS 10
#define REPEAT_THRESH 10
#define SIGNAL_NOISE_RATIO_MIN 0.3

typedef enum {WAIT_F1, WAIT_F2} state_t;

void compute_freq_mag(int16_t *samples, int16_t *imag, uint16_t *result, uint16_t start, uint16_t end);
uint8_t sigdet(int16_t *freq, int16_t *imag, uint16_t *mag, uint32_t target);
uint8_t check_state(uint8_t foundf1, uint8_t foundf2);

#endif /* SIGDET_H_ */
