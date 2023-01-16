#include "sigdet.h"
#include "settings.h"
#include <math.h>
#include <stdio.h>

#define TIMEOUT_CLK_HZ 9400
#define ONE_SECOND_MS 1000

uint8_t timeout = 0;

/*
 * Release state machine. Checks for alternating sequence of
 * F1 and F2. Returns 1 if device should release, 0 if not.
 *
 * Timeout is not currently implemented since the switch to STM32
 */
uint8_t check_state(uint8_t foundf1, uint8_t foundf2) {
    static state_t state = WAIT_F1;
    static uint8_t transitions = 0;
    static uint16_t f1_repeat_count = 0, f2_repeat_count = 0;
    uint8_t release = 0;
    if (!foundf1)
        f1_repeat_count = 0;
    else
        f1_repeat_count++;
    if (!foundf2)
        f2_repeat_count = 0;
    else
        f2_repeat_count++;
    /* Listening for the first frequency */
    if (state == WAIT_F1) {
        if (f1_repeat_count > REPEAT_THRESH) {
            state = WAIT_F2;
            transitions++;
            /* Reset timeout */
        }
    }
    /* Listening for the second frequency */
    else if (state == WAIT_F2) {
        if (f2_repeat_count > REPEAT_THRESH) {
            state = WAIT_F1;
            transitions++;
            /* Reset timeout */
        }
    }
    /* No transitions occurred after some time */
    if (timeout) {
        /* Back to initial state, clear all recorded transitions */
        state = WAIT_F1;
        transitions = 0;
        /* Reset timeout */
        timeout = 0;
    }
    /* Heard the correct number of transitions - release! */
    if (transitions == TRANSITION_AMOUNT) {
        release = 1;
        state = WAIT_F1;
        transitions = 0;
    }
    return release;
}

/*
 * Calculate the frequency magnitude given an array
 * of both real and imaginary parts. Place result in
 * "result" array. Arrays must be 1024 in size.
 * Start and end are indices between which the computation
 * will take place. Used to avoid unnecessary computation.
 */
void compute_freq_mag(int16_t *real, int16_t *imag, uint16_t *result, uint16_t start, uint16_t end) {
    uint16_t i = 0;
    uint32_t val;
    double freq;
//    uint32_t freq;
    for (i = start; i < end; i++) {
        freq = real[i] * real[i] + imag[i] * imag[i];
        freq = sqrt(freq);
        /* Made magnitude calculation faster. May have caused some issues.
         * Leaving here for now, needs more testing */
//        val = (real[i] << 16) | imag[i];
//        val = __SMUAD(val, val);
//        freq = val >> 1;
//        freq = (freq + val / freq) >> 1;
//        freq = (freq + val / freq) >> 1;
//        freq = (freq + val / freq) >> 1;
//        freq = (freq + val / freq) >> 1;
//        freq = (freq + val / freq) >> 1;
//        freq = (freq + val / freq) >> 1;
//        freq = (freq + val / freq) >> 1;
//        freq = (freq + val / freq) >> 1;
        result[i] = (uint16_t)freq;
    }
    result[0] = 0;
}

/*
 * Determine if the target frequency is found in the frequency content
 * freq - real component (array of 1024 elements)
 * imag - imaginary component (array of 1024 elements)
 * mag  - magnitude (result from compute_freq_mag)
 * target - frequency to check for
 */
uint8_t sigdet(int16_t *freq, int16_t *imag, uint16_t *mag, uint32_t target) {
    uint32_t total_energy = 0, signal_energy = 0;
    uint16_t i = 0;
    int16_t start;
    start = ((target * BUFSIZE) / SAMPLE_RATE_HZ) - NOISE_RADIUS;
    if (start <= 0)
        start = 1;
    compute_freq_mag(freq, imag, mag, start, start + (NOISE_RADIUS << 1));
    /* Determine total energy in wide region around target */
    for (i = start; i < start + (NOISE_RADIUS << 1); i++) {
        total_energy += mag[i];
    }
    /* Determine signal energy in narrow region around target */
    for (i = start + (NOISE_RADIUS - SIGNAL_RADIUS); i < start + (NOISE_RADIUS + SIGNAL_RADIUS); i++) {
        signal_energy += mag[i];
    }

    /* No signal */
    if (total_energy < (NOISE_RADIUS << 1)) {
        return 0;
    }

    /* Output - turn on LED for prototype */
    float snr = (float)signal_energy / (float)total_energy;
    if (snr > SIGNAL_NOISE_RATIO_MIN) {
        /* Signal is detected */
        return 1;
    }
    /* Signal not detected */
    return 0;
}

