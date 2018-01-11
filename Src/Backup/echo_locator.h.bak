#ifndef ECHO_LOCATOR_INCLUDE

#define ECHO_LOCATOR_INCLUDE
#include <stdint.h>
#include "gpio.h"
// struct echo_locator_tag;  // forward declared for encapsulation
//struct echo_locator_tag;
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
#endif

