#ifndef DCOLLECT_H
#define DCOLLECT_H

#include "main.h"

inline void send_sample(uint16_t sample);
void send_samples(uint16_t *samples);
void send_ss_seq(void);

#endif /* DCOLLECT_H */
