// Tests for kernel/energy
#include <assert.h>
#include <stdio.h>

#include "tiku.h"
#include <kernel/process/tiku_process.h>
#include <kernel/energy/tiku_energy.h>

// Fake source: set fake_mv to choose the voltage
static uint16_t fake_mv;
static uint16_t fake_source(void) { return fake_mv; }

// On each poll: wait for 2800 mV, then count a send
static int sends;

TIKU_PROCESS(radio, "radio");

TIKU_PROCESS_THREAD(radio, ev, data)
{
    (void)data;
    TIKU_PROCESS_BEGIN();
    while (1) {
        TIKU_PROCESS_WAIT_EVENT_UNTIL(ev == TIKU_EVENT_POLL);
        TIKU_PROCESS_WAIT_ENERGY(2800);
        sends++;
    }
    TIKU_PROCESS_END();
}

// Set the voltage, then run the radio once
static void poke_radio_at(uint16_t mv)
{
    fake_mv = mv;
    tiku_process_poll(&radio);
    while (tiku_process_run()) {
    }
}

static void test_source(void)
{
    // No source
    assert(tiku_energy_mv() == TIKU_ENERGY_MV_UNKNOWN);

    tiku_energy_set_source(fake_source);
    // Reads the fake
    fake_mv = 2500;
    assert(tiku_energy_mv() == 2500);

    // Source removed
    tiku_energy_set_source(NULL);
    assert(tiku_energy_mv() == TIKU_ENERGY_MV_UNKNOWN);
    printf("source: OK\n");
}

static void test_wait_energy(void)
{
    tiku_energy_set_source(fake_source);
    tiku_process_init();
    tiku_process_start(&radio, NULL);
    while (tiku_process_run()) {
    }

    // Enough energy - no pause
    poke_radio_at(2900);
    assert(sends == 1);

    // Not enough energy - pause
    poke_radio_at(2100);
    assert(sends == 1);

    // Still low
    poke_radio_at(2500);
    assert(sends == 1);

    // Enough energy - resumes
    poke_radio_at(2900);
    assert(sends == 2);
    printf("wait_energy: OK\n");
}

int main(void)
{
    test_source();
    test_wait_energy();
    printf("all energy tests passed\n");
    return 0;
}
