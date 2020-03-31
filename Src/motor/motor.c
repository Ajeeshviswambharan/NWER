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


void motor_control(waypoint_info nwer_info[WAY_DETAILS],uint8_t mode,uint8_t mode_sub)
{
    uint8_t mode_select,sub_mode_select;
    mode_select=mode;
    switch (mode_select)
    {
    case INTIAL_MODE:/* constant-expression */
        /* Initial mode detected*/
        if((nwer_info[0].PIR_VALUE==false) &&(nwer_info[0].stm_mode==RUNNING))
        {
    		forward();
            osDelay(2000);
            stop();
            osDelay(2000);

        }
        else
        {
    	stop();
        }
        break;

    default:
        break;
    }



}
