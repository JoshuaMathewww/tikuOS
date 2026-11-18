#ifndef TIKU_ENERGY_H_
#define TIKU_ENERGY_H_

#include <stdint.h>

// Returned when no source is set; 
#define TIKU_ENERGY_MV_UNKNOWN  0xFFFFu

/* Use inside a process, continue if voltage >= mv, else pause until it is. 
Paused processes only re check when it gets an event */
#define TIKU_PROCESS_WAIT_ENERGY(mv)                                \
    if (tiku_energy_mv() < (mv)) {                                  \
        TIKU_PROCESS_WAIT_EVENT_UNTIL(tiku_energy_mv() >= (mv));    \
    }                                                               \

// Function returning the supply voltage in mV.
typedef uint16_t (*tiku_energy_source_t)(void);

// Set the voltage source (ADC, fake, ...)
void tiku_energy_set_source(tiku_energy_source_t source);

// Current voltage in mV
uint16_t tiku_energy_mv(void);

#endif
