#include "include/time.h"
#include "include/stdint.h"

#define SLEEP_COUNT 250000

void sleep(size_t ms) {
    unsigned int i = 0; 
    unsigned int j = 0;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < SLEEP_COUNT; j++) {
            // Do nothing
        }
    }
}
