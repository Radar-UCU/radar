/**
 * |----------------------------------------------------------------------
 * | Copyright (C) Victoria Yuzkiv, 2017
 * |----------------------------------------------------------------------
 */

#include "MicroServo.h"


void Set_Position(uint8_t pos) {
	HAL_Delay(1500);
	uint32_t tmp=(SERVO_MICROS_MAX - SERVO_MICROS_MIN) / 180 ;
	TIM3->CCR2 = SERVO_MICROS_MIN + tmp * pos;
}

void Set_Min_Position() {
	HAL_Delay(1500);
	TIM3->CCR2 = SERVO_MICROS_MIN;
}

void Set_Max_Position() {
	HAL_Delay(1500);
	TIM3->CCR2 = SERVO_MICROS_MAX;
}
