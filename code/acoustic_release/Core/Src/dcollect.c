#include "dcollect.h"
#include "uart.h"

#define BAUD_RATE 115200


// send a single buffer sample to UART (for testing)
inline void send_sample(uint16_t sample) {
    write_char(sample & 0xFF);
    write_char((sample >> 8) & 0xFF);
}

// send1 1024 buffer samples over UART
void send_samples(uint16_t *samples) {
    uint16_t i = 0;
    while (i < 1024) {
    	write_char(samples[i] & 0xFF);
    	write_char((samples[i] >> 8) & 0xFF);
        i++;
    }
}

// write 8 bytes, all 1's to UART
// this is the startup confirmation
void send_ss_seq(void) {
    uint8_t i;
    for (i = 0; i < 8; i++)
        write_char(0xFF);
}
