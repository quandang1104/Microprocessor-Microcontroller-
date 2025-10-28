/*
 * sch.c
 *
 *  Created on: Oct 26, 2025
 *      Author: ADMIN
 */
#include "sch.h"
uint8_t currentTask =0;
uint32_t ERROR_CODE_G =0;
Tasks taskList[SCH_MAX_TASKS];

void SCH_init(void){
	deleteAll();
	currentTask=0;
	ERROR_CODE_G =0;
	HAL_GPIO_WritePin(GPIOA, LED_1_Pin | LED_2_Pin | LED_3_Pin | LED_4_Pin, SET);
	HAL_GPIO_WritePin(GPIOA, debug_Pin, RESET);
}

uint32_t SCH_addTask(void (*task)(void), uint32_t delay, uint32_t period){
	if(currentTask == SCH_MAX_TASKS){
		ERROR_CODE_G = ERROR_SCH_TOO_MANY_TASKS;
		HAL_GPIO_TogglePin(GPIOA, debug_Pin);
		return ERROR_CODE_G;
	}
	if ((int)period < 0) {
	    ERROR_CODE_G = ERROR_SCH_INVALID_PERIOD;
	    HAL_GPIO_TogglePin(GPIOA, debug_Pin);
	    return ERROR_CODE_G;
	}
	if ((int)delay < 0) {
	    ERROR_CODE_G = ERROR_SCH_INVALID_DELAY;
	    HAL_GPIO_TogglePin(GPIOA, debug_Pin);
	    return ERROR_CODE_G;
	}
	taskList[currentTask].functionPointer= task;
	taskList[currentTask].period = period;
	taskList[currentTask].delay = delay;
	taskList[currentTask].runme = 0;
	taskList[currentTask].taskID = currentTask;
	taskList[currentTask].isEmpty = 0;
	taskList[currentTask].isOneshot = (period ==0);

	return currentTask++;
}
void SCH_update(void)
{
    for (int i = 0; i < currentTask; i++)
    {
        if (taskList[i].isEmpty)
            continue;
        if (taskList[i].delay == 0)
        {
            taskList[i].runme++;
            if (taskList[i].period > 0)
                taskList[i].delay = taskList[i].period;
        }
        else //(delay>0)
        {
            taskList[i].delay--;
            if (taskList[i].delay == 0)
            {
                taskList[i].runme++;
                if (taskList[i].period > 0)
                    taskList[i].delay = taskList[i].period;
            }
        }
    }
}

void SCH_dispatch(void){
	for(int i=0; i< SCH_MAX_TASKS; i++){
		if(taskList[i].runme>0 && taskList[i].isEmpty == false){
			taskList[i].runme--;
			(*taskList[i].functionPointer)();
			if(taskList[i].isOneshot == true){
				SCH_deleteTask(taskList[i].taskID);
			}
		}
	}
}
uint32_t SCH_deleteTask(uint32_t taskID){
	if(taskID >= SCH_MAX_TASKS){ // index lớn hơn size
		ERROR_CODE_G = ERROR_SCH_INVALID_INDEX;
		return ERROR_CODE_G;
	}
	if(taskList[taskID].functionPointer == NULL){ // task trống
		ERROR_CODE_G = ERROR_SCH_INVALID_INDEX;
		return ERROR_CODE_G;
	}
	if(taskID == SCH_MAX_TASKS -1){
		taskList[taskID].functionPointer = NULL;
		taskList[taskID].runme =0;
		taskList[taskID].period =0;
		taskList[taskID].delay =0;
		taskList[taskID].taskID=0;
		taskList[taskID].isEmpty= true;
		taskList[taskID].isOneshot = false;
		currentTask--;
	} else{
		for(int i = taskID; i < currentTask - 1; i++){
			taskList[i]= taskList[i+1];
		}
		taskList[currentTask-1].functionPointer = NULL;
		taskList[currentTask-1].runme =0;
		taskList[currentTask-1].period =0;
		taskList[currentTask-1].delay =0;
		taskList[currentTask-1].taskID=0;
		taskList[currentTask-1].isEmpty= true;
		taskList[currentTask-1].isOneshot = false;
		currentTask--;
	}
	return taskID;
}
void deleteAll(void){
    while (currentTask > 0){
        SCH_deleteTask(currentTask - 1);
    }
}
