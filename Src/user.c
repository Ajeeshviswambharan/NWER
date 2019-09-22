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
uint8_t txData_gps[14]="GPS Cyclic\r\n";
uint8_t rxData_ledon[32]="ONE RECEIVED SO LED WILL ON\r\n";
uint8_t rxData_ledoz[33]="ZERO RECEIVED SO LED WILL OFF\r\n";
uint8_t rxData_ledou[17]="UNKNOWN ENTRY\r\n";
char rx_buffer_gps[25];
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

        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,0);
	    HAL_UART_Transmit(&huart2,txData_motor,14,1);
	    osDelay(2000);
    }
void sensor_cyclic_uart_check(void)  /*cyclic UART check for sensor check must be delete*/
	{
		HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
		HAL_UART_Transmit(&huart2,txData_sensor,16,1);
		osDelay(1000);
		gps_valuereceive();
	}
void gps_cyclic_uart_check(void)  /*cyclic UART check for gps check*/
	{
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,1);
		HAL_UART_Transmit(&huart2,txData_gps,14,1);
		osDelay(800);
	}
void gps_valuereceive(void)/* GPS value read */
	{
		HAL_UART_Receive_DMA(&huart2,(uint8_t *)rx_buffer_gps,3);
	}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_UART_RxCpltCallback can be implemented in the user file.
   */
  /* Check for the Received value */
  if((rx_buffer_gps[0]=='*') && (rx_buffer_gps[2]=='#') )//Valid vata
	{
		if(rx_buffer_gps[1]== 1)//LED ON
			{
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,1);	
				HAL_UART_Transmit(&huart2,rxData_ledon,32,1);
			}
		else if(rx_buffer_gps[1]== 0 )
			{
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,0);	
				HAL_UART_Transmit(&huart2,rxData_ledoz,33,1);	
			
			}
		else
			{
			/* Recevied data is unknown */
			HAL_UART_Transmit(&huart2,rxData_ledou,17,1);	
			}
		
	}
	else
	{
		{
			HAL_UART_Receive_DMA(&huart2,(uint8_t *)rx_buffer_gps,3);
		}
	}
	
}
