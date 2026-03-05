/*
 * scheduler.c
 *
 *  Created on: Sep 25, 2025
 *      Author: acer
 */
#include "scheduler.h"

uint8_t Index = 0;
//uint32_t ERROR_CODE_G = 0;
unsigned char Error_code_G;
sTask SCH_tasks_G[SCH_MAX_TASKS];

void SCH_Init(void){
	unsigned char i ;
	for( i = 0; i < SCH_MAX_TASKS; i ++) {
			SCH_Delete_Task(i);
	}
	Index = 0;
	Error_code_G = 0;
//	HAL_GPIO_WritePin(led0_GPIO_Port, led0_Pin, 1);
//	HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, 1);
//	HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, 1);
//	HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, 1);
//	HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, 1);

}
void SCH_Update(void){
	for (int i = 0; i < SCH_MAX_TASKS; i++){
		if(SCH_tasks_G[i].pTask){
			if(SCH_tasks_G[i].Delay > 0 ) {
				SCH_tasks_G[i].Delay--;
			}
			else{
				SCH_tasks_G [i].RunMe += 1;
				if(SCH_tasks_G[i].Period){
					SCH_tasks_G[i].Delay = SCH_tasks_G [i].Period;
				}
			}
		}
	}
}
uint32_t SCH_Add_Task(void (*task)(void), uint32_t delay, uint32_t period){
	HAL_GPIO_TogglePin(led_test_GPIO_Port,led_test_Pin);
	while ((Index < SCH_MAX_TASKS) && (SCH_tasks_G[Index].pTask != 0 ) ){
		Index++;
	}
	if( Index == SCH_MAX_TASKS){
		Error_code_G = ERROR_SCH_TOO_MANY_TASKS;
		HAL_GPIO_TogglePin(led_test_GPIO_Port,led_test_Pin);
		return SCH_MAX_TASKS;
	}
	SCH_tasks_G[Index].pTask = task;
	SCH_tasks_G[Index].Delay = delay;
	SCH_tasks_G[Index].Period = period;
	SCH_tasks_G[Index].RunMe = 0;
	SCH_tasks_G[Index].TaskID = Index;
	return Index;
}
void SCH_Dispatch_Tasks(void){
	for (int i = 0; i < SCH_MAX_TASKS; i++){
		if(SCH_tasks_G[i].RunMe > 0 ) {
//			HAL_GPIO_TogglePin(led_test_GPIO_Port,led_test_Pin);
			(*SCH_tasks_G[i].pTask)();
			SCH_tasks_G[i].RunMe--;
			if(SCH_tasks_G[i].Period == 0){
				SCH_Delete_Task(SCH_tasks_G[i].TaskID);
			}
		}
	}
}
uint8_t SCH_Delete_Task(uint32_t taskID){
	if(taskID >= SCH_MAX_TASKS || SCH_tasks_G[taskID].pTask == 0){
		Error_code_G = ERROR_SCH_INVALID_INDEX;
		return Error_code_G;
	}
	if (taskID == SCH_MAX_TASKS - 1){
		SCH_tasks_G[taskID].pTask = 0x0000;
		SCH_tasks_G[taskID].Delay = 0;
		SCH_tasks_G[taskID].Period = 0;
		SCH_tasks_G[taskID].RunMe = 0;
		SCH_tasks_G[taskID].TaskID = 0;
		Index--;
	}
	else{
		for (int i = taskID; i < SCH_MAX_TASKS - 1; i++){
			SCH_tasks_G[i] = SCH_tasks_G[i + 1];
		}
		SCH_tasks_G[SCH_MAX_TASKS-1].pTask = 0x0000;
		SCH_tasks_G[SCH_MAX_TASKS-1].Delay = 0;
		SCH_tasks_G[SCH_MAX_TASKS-1].Period = 0;
		SCH_tasks_G[SCH_MAX_TASKS-1].RunMe = 0;
		SCH_tasks_G[SCH_MAX_TASKS-1].TaskID = 0;
		Index--;
	}
	return taskID;
}

