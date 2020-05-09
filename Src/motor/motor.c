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
uint8_t way_numer;
uint8_t way_numer_backup;
/* USER CODE BEGIN Includes */


    


void forward()
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,ON);
}
void backward()
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,ON);
}
void leftturn()
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,ON);
}
void rightturn()
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,ON);
}
void turnaround()
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,OFF);
}
void stop()
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,0);
}


void motor_control(waypoint_info nwer_info[WAY_DETAILS],uint8_t mode,uint8_t mode_sub,uint8_t fs_status)
{
    uint8_t mode_select,sub_mode_select;
    mode_select=mode;
    switch (mode_select)
    {
    case INTIAL_MODE:/* constant-expression */
        /* Initial mode detected*/
    	{
                for(int w_points=INIT_START;w_points<INIT_END;w_points++)
                {        
                    if((fs_status==false) && (nwer_info[w_points].my_wheel_heading == FORWARD) && (nwer_info[w_points].heading_angle == 0)) 
                    { 
    		        forward();
                    osDelay(2000);
                    }
                    else if((fs_status==false) && (nwer_info[w_points].my_wheel_heading == ROTATE_RIGHT) && (nwer_info[w_points].heading_angle == 90)) 
                    { 
    		        rightturn();
                    osDelay(2000);
                    }
                    else if((fs_status==false) && (nwer_info[w_points].my_wheel_heading == ROTATE_LEFT) && (nwer_info[w_points].heading_angle == 90)) 
                    { 
    		        leftturn();
                    osDelay(2000);
                    }
                    else
                    {
                    stop();                        
                    }
                    
                }

        }

        break;

    default:
        break;
    }



}
