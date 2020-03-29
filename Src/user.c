/*
 * user.c
 *
 *  Created on: Sep 15, 2019
 *      Author: AJEESH
 */
/* Includes ------------------------------------------------------------------*/

#include "user.h"


/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;
uint8_t txData_motor[14]="Motor Cyclic\r\n";
uint8_t txData_sensor[16]="Sensor Cyclic\r\n";
uint8_t txData_gps[14]="SPI Cyclic\r\n";
uint8_t txData_pir_iot[19]="PIR_IOT Cyclic\r\n";
/*User functins updated here*****************************************/
bool start_init(void) /*For check the Inital sensor status*/
	{
		bool flag_utra_sensor,flag_rain_sensor;
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13)==GPIO_PIN_SET)
		{
			flag_utra_sensor=false;
			flag_rain_sensor=false;
		}
		else if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13)==GPIO_PIN_RESET)
		{
					flag_utra_sensor=true;
					flag_rain_sensor=true;
		}
		if((flag_utra_sensor==true)&&(flag_rain_sensor==true))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

void motor_cyclic_uart_check(void)  /*cyclic UART check for motor check must be delete*/
    {

        //HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,0);
	   	HAL_UART_Transmit(&huart2,txData_motor,14,1);
	    osDelay(2000);
    }
void joystick_cyclic_uart_check(void)  /*cyclic UART,update for Joystick input*/
	{
		//HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
		HAL_UART_Transmit(&huart2,txData_sensor,16,1);
		osDelay(2000);
		gps_valuereceive();
		revert_state();
	}
void spi_cyclic_check(void)  /*SPI Update*/
	{
		//HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,1);
		HAL_UART_Transmit(&huart2,txData_gps,14,1);
		osDelay(2000);
	}
void pir_iot_cyclic_check(void)  /*cyclic pir_iot check*/
	{
		//HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,1);
		HAL_UART_Transmit(&huart2,txData_pir_iot,19,1);
		osDelay(2000);
	}
