#ifndef _ECHO_LOCATOR_H
#define _ECHO_LOCATOR_H

#include <stdint.h>
#include "gpio.h"
#include <malloc.h>

// forward declared for encapsulation
typedef struct echo_locator_tag Echo_Locator;

// equivalent to "Echo_Locator.init(self, echo_port, echo_pin, trig_port, trig_pin)"
void Echo_Locator__init(Echo_Locator* self,
		uint32_t echo_port, uint32_t echo_pin, uint32_t trig_port, uint32_t trig_pin);

// Allocation + initialization (equivalent to "new Echo_Locator(...)")
Echo_Locator* Echo_Locator__create(uint32_t echo_port, uint32_t echo_pin,
		uint32_t trig_port, uint32_t trig_pin);

// Measure distance
uint32_t measure_distance(Echo_Locator* self);


// Callback for EXTI
void echo_locator_callback(Echo_Locator* self);

// Filtered Measurement with accuracy
uint32_t filtered_measurement(Echo_Locator* self, int accuracy);

#endif
