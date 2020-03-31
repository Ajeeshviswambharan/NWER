/*
 * motor.c
 *
 *  Created on: Sep 24, 2019
 *      Author: AJEESH
 */

/* Used  for updation of Sensor codes */
/* Private includes ----------------------------------------------------------*/
#include "motor.h"




/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN Includes */
void motor_control(waypoint_info nwer_info[WAY_DETAILS],uint8_t mode,uint8_t mode_sub)
{
    if((nwer_info[0].PIR_VALUE==false) &&(nwer_info[0].stm_mode==RUNNING))
    {
    	if(mode==INTIAL_MODE)
    	{
    		forward();
    	}
    }
    else
    {
    	stop();
    }
}

void forward()
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,1);
}
void backward()
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,1);
}
void leftturn()
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,1);
}
void rightturn()
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,1);
}
void turnaround()
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,1);
}
void stop()
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,0);
}
