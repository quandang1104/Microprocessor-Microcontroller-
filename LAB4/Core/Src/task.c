/*
 * task.c
 *
 *  Created on: Oct 26, 2025
 *      Author: ADMIN
 */

#include "task.h"
#include "string.h"
extern UART_HandleTypeDef huart1;
void task1(void){
	HAL_GPIO_TogglePin(GPIOA, LED_1_Pin);
}
void task2(void){
	HAL_GPIO_TogglePin(GPIOA, LED_2_Pin);
}
void task3(void){
	HAL_GPIO_TogglePin(GPIOA, LED_3_Pin);
}
void task4(void){
	HAL_GPIO_TogglePin(GPIOA, LED_4_Pin);
}
//void task5(void){
//	HAL_GPIO_TogglePin(GPIOA, debug_Pin);
//}

//	char msg[] = "Task3 executed\r\n";
//	HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 100);
