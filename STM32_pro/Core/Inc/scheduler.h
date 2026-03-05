/*
 * scheduler.h
 *
 *  Created on: Sep 25, 2025
 *      Author: acer
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_
#include "stdint.h"
#include "main.h"
#define SCH_MAX_TASKS 10

#define ERROR_SCH_INVALID_INDEX								101
#define ERROR_SCH_TOO_MANY_TASKS 							102
#define ERROR_SCH_WAITING_FOR_SLAVE_TO_ACK 					103
#define ERROR_SCH_WAITING_FOR_START_COMMAND_FROM_MASTER 	104
#define ERROR_SCH_ONE_OR_MORE_SLAVES_DID_NOT_START 			105
#define ERROR_SCH_LOST_SLAVE 								106
#define ERROR_SCH_CAN_BUS_ERROR 							107
#define ERROR_I2C_WRITE_BYTE_AT24C64 						108

typedef struct {
	void (*pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
	uint32_t TaskID;
} sTask;
void SCH_Init(void);
uint32_t SCH_Add_Task(void (*task)(void), uint32_t delay, uint32_t period);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
uint8_t SCH_Delete_Task(uint32_t taskID);

void deleteAllTasks(void);

#endif /* INC_SCHEDULER_H_ */
