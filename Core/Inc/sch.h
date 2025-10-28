/*
 * sch.h
 *
 *  Created on: Oct 26, 2025
 *      Author: ADMIN
 */

#ifndef INC_SCH_H_
#define INC_SCH_H_

#include "main.h"
#include "stdint.h"
#include "stdbool.h"
#define SCH_MAX_TASKS 10

#define ERROR_SCH_INVALID_INDEX 								1
#define ERROR_SCH_TOO_MANY_TASKS 								2
#define ERROR_SCH_WAITING_FOR_SLAVE_TO_ACK 						3
#define ERROR_SCH_WAITING_FOR_START_COMMAND_FROM_MASTER 		4
#define ERROR_SCH_ONE_OR_MORE_SLAVES_DID_NOT_START 				5
#define ERROR_SCH_LOST_SLAVE 									6
#define ERROR_SCH_CAN_BUS_ERROR 								7
#define ERROR_I2C_WRITE_BYTE_AT24C64 							8
#define ERROR_SCH_INVALID_PERIOD     							9
#define ERROR_SCH_INVALID_DELAY      							10


typedef struct Tasks {
	void (*functionPointer)(void);
	uint32_t delay;
	uint32_t period;
	uint32_t runme;
	uint32_t taskID;
	bool isEmpty;
	bool isOneshot;
} Tasks;

void SCH_init(void);
uint32_t SCH_addTask(void (*task)(void), uint32_t delay, uint32_t period);
void SCH_update(void);
void SCH_dispatch(void);
uint32_t SCH_deleteTask(uint32_t taskID);
void deleteAll(void);

#endif /* INC_SCH_H_ */










