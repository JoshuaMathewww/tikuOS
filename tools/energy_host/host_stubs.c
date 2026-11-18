#include "tiku.h"
#include <hal/tiku_cpu.h>
#include <kernel/cpu/tiku_hang.h>
#include <kernel/memory/tiku_mem.h>
#include <kernel/process/tiku_process.h>
#include <kernel/timers/tiku_clock.h>
#include <kernel/timers/tiku_htimer.h>
#include <kernel/timers/tiku_timer.h>
#include <kernel/vfs/tiku_vfs.h>

// CPU: no interrupts or sleep on a laptop
void tiku_atomic_enter(void) {}
void tiku_atomic_exit(void) {}
void tiku_cpu_irq_enable(void) {}
tiku_cpu_idle_enter_t tiku_cpu_idle_hook(tiku_cpu_idle_mode_t mode) { (void)mode; return 0; }
int tiku_cpu_idle_mode_wakes_on_tick(tiku_cpu_idle_mode_t mode) { (void)mode; return 1; }

// Clock: always 0
tiku_clock_time_t tiku_clock_time(void) { return 0; }
int tiku_clock_tickless_begin(tiku_clock_time_t ticks) { (void)ticks; return 0; }
void tiku_clock_tickless_end(void) {}

// Hang watchdog
void tiku_hang_arm(void) {}
void tiku_hang_checkin(void) {}
uint8_t tiku_hang_is_culprit(const struct tiku_process *p) { (void)p; return 0; }

// Timers: none; tests poke processes directly
void tiku_htimer_init(void) {}
void tiku_timer_init(void) {}
void tiku_timer_request_poll(void) {}
void tiku_timer_cancel_process(const struct tiku_process *p) { (void)p; }
int tiku_timer_any_pending(void) { return 0; }
int tiku_timer_work_pending(void) { return 0; }
tiku_clock_time_t tiku_timer_next_expiration(void) { return 0; }
int tiku_timer_owner_armed(const struct tiku_process *p) { (void)p; return 0; }

// Memory and VFS
tiku_mem_err_t tiku_arena_stats(const tiku_arena_t *a, tiku_mem_stats_t *s)
{ (void)a; (void)s; return TIKU_MEM_ERR_INVALID; }
void tiku_vfs_unwatch_all(struct tiku_process *p) { (void)p; }
