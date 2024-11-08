

#include "blink.h"
#include <hal/uc.h>


blink_state_t blink_state = {0};


void blink_off(void) {
    #if BLINK_POLARITY
    gpio_set_output_low(BLINK_GPIO);  
    #else
    gpio_set_output_high(BLINK_GPIO);  
    #endif
}

void blink_on(void) {
    #if BLINK_POLARITY
    gpio_set_output_high(BLINK_GPIO);  
    #else
    gpio_set_output_low(BLINK_GPIO);
    #endif
}

void blink_toggle(void) {
    gpio_set_output_toggle(BLINK_GPIO);  
}

void _blink_stop() {
    blink_state.period = 0;
    if (blink_state.mode){
        blink_state.mode = BLINK_OFF;
    }
    if (blink_state.job.active) {
        tm_cron_cancel_job(&blink_state.job);
    }
    blink_off();
}

void _blink_make_periodic() {
    blink_state.mode = BLINK_PERIODIC;
    if (blink_state.job.active) {
        tm_cron_cancel_job(&blink_state.job);
    }
    tm_system_t start;
    tm_current_time(&start);
    tm_cron_create_job_abs(&blink_state.job, &blink_toggle, &start, &blink_state.period);
}

void set_blink_period(uint16_t period){    
    if (!period){
        _blink_stop();
        return;
    }
    blink_state.period = period;
    if (blink_state.mode != BLINK_PERIODIC){
        _blink_make_periodic();
    }
}

void start_blink_task(void) {
    set_blink_period(500);
}
