#include "dcollect.h"
#include "uart.h"

#define BAUD_RATE 115200

inline void send_sample(uint16_t sample) {
    write_char(sample & 0xFF);
    write_char((sample >> 8) & 0xFF);
}

void send_samples(uint16_t *samples) {
    uint16_t i = 0;
    while (i < 1024) {
    	write_char(samples[i] & 0xFF);
    	write_char((samples[i] >> 8) & 0xFF);
        i++;
    }
}

void send_ss_seq(void) {
    uint8_t i;
    for (i = 0; i < 8; i++)
        write_char(0xFF);
}

