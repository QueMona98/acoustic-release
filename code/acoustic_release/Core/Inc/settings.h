#ifndef INC_SETTINGS_H_
#define INC_SETTINGS_H_

#define FFT_SIZE 10
#define BUFSIZE 1024
#define SAMPLE_RATE_HZ 500000
#define ADC_MID 8192

/* The two frequencies we are looking for (Hz) */
#define FREQL 185000
#define FREQH 200000

#define RELEASE_TIMEOUT_MS 500
/* Number of transitions required for a release */
#define TRANSITION_AMOUNT 4

/* Compilation modes */
#define DEBUG

#endif /* INC_SETTINGS_H_ */
