

#include <time/cron.h>
#include <iomap.h>

typedef enum {
    BLINK_OFF,
    BLINK_PERIODIC,
    // BLINK_MORSE // Not Implemented
} BLINK_MODE_t;

typedef struct BLINK_STATE_t { 
    BLINK_MODE_t mode;
    cron_job_t   job;
    tm_sdelta_t  period;
} blink_state_t;

extern blink_state_t blink_state;

void start_blink_task(void);
void set_blink_period(uint16_t period);
