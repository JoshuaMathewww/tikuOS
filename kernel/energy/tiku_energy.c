#include "tiku_energy.h"
#include <stddef.h>

// Current source is null until set
static tiku_energy_source_t energy_source;

void tiku_energy_set_source(tiku_energy_source_t source)
{
    energy_source = source;
}

uint16_t tiku_energy_mv(void)
{
    if (energy_source == NULL) {
        return TIKU_ENERGY_MV_UNKNOWN;
    }
    return energy_source();
}