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
void motor_control(waypoint_info nwer_info[WAY_DETAILS])
{
    if((nwer_info[0].PIR_VALUE==false) &&(nwer_info[0].stm_mode==RUNNING))
    {
    	if(nwer_info[0].mode==INTIAL_MODE)
    	{
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,1);
    	}
    }
}
