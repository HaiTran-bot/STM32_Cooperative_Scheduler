/*
 * task.c
 *
 *  Created on: Sep 27, 2025
 *      Author: acer
 */
#include "tasks.h"
void task1 (void){
    HAL_GPIO_TogglePin(led0_GPIO_Port, led0_Pin);
}

void task2 (void){
	HAL_GPIO_TogglePin(led1_GPIO_Port, led1_Pin);
}

void task3(void){
	HAL_GPIO_TogglePin(led2_GPIO_Port, led2_Pin);
}

void task4(void){
	HAL_GPIO_TogglePin(led3_GPIO_Port, led3_Pin);
}
void task5(void){
	HAL_GPIO_TogglePin(led4_GPIO_Port, led4_Pin);
}

void BlinkTaskTest(void){
	HAL_GPIO_TogglePin(led_test_GPIO_Port, led_test_Pin);
}
