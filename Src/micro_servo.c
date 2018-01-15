/**
 * |----------------------------------------------------------------------
 * | Copyright (C) Victoria Yuzkiv, 2017
 * |----------------------------------------------------------------------
 */

#include "micro_servo.h"


void Set_Position(uint8_t pos) {
	//HAL_Delay(1500);
	udelay_TIM6(100000);
	double tmp=((double)(SERVO_MICROS_MAX - SERVO_MICROS_MIN)) / 180.0 ;
	TIM3->CCR2 = SERVO_MICROS_MIN + (double)tmp * pos;
}

void Set_Min_Position(void) {
	//HAL_Delay(1500);
	udelay_TIM6(100000);
	TIM3->CCR2 = SERVO_MICROS_MIN;
}

void Set_Max_Position(void) {
	//HAL_Delay(1500);
	udelay_TIM6(100000);
	TIM3->CCR2 = SERVO_MICROS_MAX;
}
