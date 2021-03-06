#include "echo_locator.h"


typedef enum state_t {
 IDLE_S,
// TRIGGERING_S,
 WAITING_FOR_ECHO_START_S,
 WAITING_FOR_ECHO_STOP_S,
// TRIG_NOT_WENT_LOW_S,
// ECHO_TIMEOUT_S,
// ECHO_NOT_WENT_LOW_S,
 READING_DATA_S,
 ERROR_S
} state_t;

struct echo_locator_tag {
	uint32_t echo_port;
	uint32_t echo_pin;
	uint32_t trig_pin;
	uint32_t trig_port;
	volatile state_t state;
	volatile uint32_t echo_start;
	volatile uint32_t echo_finish;
	volatile uint32_t measured_time;
};

// Constructor (without allocation)
void Echo_Locator__init(Echo_Locator* self, uint32_t echo_port, uint32_t echo_pin,
		uint32_t trig_port, uint32_t trig_pin) {
  self->echo_port = echo_port;
  self->echo_pin = echo_pin;
  self->trig_port = trig_port;
  self->trig_pin = trig_pin;
  self->state = IDLE_S;
  self->echo_start = 0;
  self->echo_finish = 0;
  self->measured_time = 0;
}

// Allocation + initialization (equivalent to "new Echo_Locator(...)")
Echo_Locator* Echo_Locator__create(uint32_t echo_port, uint32_t echo_pin,
		uint32_t trig_port, uint32_t trig_pin) {
	Echo_Locator* instance = (Echo_Locator*) malloc(sizeof(Echo_Locator));
	Echo_Locator__init(instance, echo_port, echo_pin, trig_port, trig_pin);
	return instance;
}

uint32_t measure_distance(Echo_Locator* self){
	HAL_GPIO_WritePin(self->trig_port, self->trig_pin, GPIO_PIN_SET);
	udelay_TIM6(16);
	HAL_GPIO_WritePin(self->trig_port, self->trig_pin, GPIO_PIN_RESET);

	self->state = WAITING_FOR_ECHO_START_S;
	//__enable_irq();
	while( self->state == WAITING_FOR_ECHO_START_S && self->state != ERROR_S ){}
	if ( self->state == ERROR_S ) {
		printf("Unexpected error while waiting for ECHO to start.\n");
		return -1;
	}
	while( self->state == WAITING_FOR_ECHO_STOP_S && self->state != ERROR_S ){}
	//__disable_irq();
	if ( self->state == ERROR_S ) {
		printf("Unexpected error while waiting for ECHO to finish.\n");
		return -1;
	}

	uint32_t distance = self->measured_time / 58;
	return distance;
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// A function to implement bubble sort
void bubbleSort(int arr[], int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)

       // Last i elements are already in place
       for (j = 0; j < n-i-1; j++)
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);
}

uint32_t filtered_measurement(Echo_Locator* self, int n){
	if(!(n%2)){
		n--;
	}
	if(n < 5){
		n = 5;
	}
	uint32_t results[n];
	for(int i=0; i<n; i++){
		results[i] = measure_distance(self);
	}
	bubbleSort(results, n);
	return results[n/2];
}

void echo_locator_callback(Echo_Locator* self){
	switch (self->state) {
	  case WAITING_FOR_ECHO_START_S: {
	   self->echo_start =  get_tim6_us();
	   self->measured_time = 0;
	   self->state = WAITING_FOR_ECHO_STOP_S;
	   break;
	  }
	  case WAITING_FOR_ECHO_STOP_S: {
	   self->echo_finish = get_tim6_us();
	   self->measured_time = self->echo_finish - self->echo_start;
	   self->state = READING_DATA_S;
	   break;
	  }
	  default:
	   self->state = ERROR_S;
	}
}
