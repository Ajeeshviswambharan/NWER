/*
 * sensor.c
 *
 *  Created on: Sep 24, 2019
 *      Author: AJEESH
 */

/* Used  for updation of Sensor codes */
/* Private includes ----------------------------------------------------------*/
#include "sensor.h"




/* Private variables ---------------------------------------------------------*/
static Uart_Statemachine my_uart_se=UART_CHECK;
char rx_buffer_gps[25];
uint32_t w_points;
uint8_t rxData_ledon[32]="ONE RECEIVED SO LED WILL ON\r\n";
uint8_t rxData_ledoz[33]="ZERO RECEIVED SO LED WILL OFF\r\n";
uint8_t rxData_ledou[17]="UNKNOWN ENTRY\r\n";
uint8_t rxData_wrong[24]="WRONG DATA...........\r\n";
waypoint_info my_way_poits[TOTAL_POINTS];
waypoint_info my_way_poits_r[TOTAL_POINTS];

/* USER CODE BEGIN Includes */
void gps_valuereceive(void)/* GPS value read */
	{
	/* Three byte Intiator and size taking command*/
		HAL_UART_Receive_DMA(&huart2,(uint8_t *)rx_buffer_gps,3);
        store_waypoit_D(&my_way_poits);
	}


    /* UART call back functions start */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_UART_RxCpltCallback can be implemented in the user file.
   */

//  MY_FLASH_ReadN(0,my_way_poits_r,TOTAL_POINTS,DATA_TYPE_32);//Read the Flahs values for GPS
    switch (my_uart_se)
    {
    case UART_CHECK:        /* constant-expression */
    /* code */
            if((rx_buffer_gps[0]=='*') && (rx_buffer_gps[2]=='#') )//Valid data
                {
                    if(rx_buffer_gps[1] <= sizeof(rx_buffer_gps))
                        {
                    		//DMA function call and size will be first given
                           HAL_UART_Receive_DMA(&huart2,(uint8_t *)rx_buffer_gps,rx_buffer_gps[1]);
                    	 //HAL_UART_Receive_DMA(&huart2,(uint8_t *)rx_buffer_gps,24);
                            my_uart_se=UART_DATA;
                            memset(rx_buffer_gps,0,sizeof(rx_buffer_gps));//clearing buffer
                        }
                    else
                        {
                        /* buffer size exceeds  */
                            my_uart_se=UART_UNK;
                        }
                }
            else
                {
                    /* verification failed */
                    my_uart_se=UART_UNK;
                }

        break;
        case UART_DATA:
            message_handle(rx_buffer_gps);
            //memset(rx_buffer_gps,0,sizeof(rx_buffer_gps));//clearing buffer
        break;

//        case UART_UNK:
//        	HAL_UART_Transmit(&huart2,rxData_wrong,24,1);//Wrong data receive
//        	memset(rx_buffer_gps,sizeof(rx_buffer_gps),0);//clearing buffer
//        	my_uart_se=UART_CHECK;
//        break;

        default:
        break;
    }

}


void message_handle(char *msg)
{
        if(strstr(msg,"LED ON")!=NULL)
            {
                HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,1);
                HAL_UART_Transmit(&huart2,rxData_ledon,32,1);
                my_uart_se=UART_CHECK;
                  /* Check for the Received value */
                MY_FLASH_SetSectorAddrs(15,0x0800F000);
                MY_FLASH_WriteN(0,my_way_poits,TOTAL_POINTS,DATA_TYPE_32);
            }
            else if(strstr(msg,"LED OFF")!=NULL)
                {
                    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,0);
                    HAL_UART_Transmit(&huart2,rxData_ledoz,33,1);
                    my_uart_se=UART_CHECK;

                }

        else
        {
            /* Update the state machine */
            my_uart_se=UART_UNK;
           // memset(rx_buffer_gps,0,sizeof(rx_buffer_gps));//clearing buffer

        }
      
}
void revert_state()//used to clear buffer and revert the state if UART_UNK state...bcz message_handle invoke only trigger comes
{
	if(my_uart_se==UART_UNK)
    	{
    	           HAL_UART_Transmit(&huart2,rxData_wrong,24,1);//Wrong data receive
    	           memset(rx_buffer_gps,0,sizeof(rx_buffer_gps));//clearing bufferr
    	        	my_uart_se=UART_CHECK;

    	}
}


void store_waypoit_D(waypoint_info wpoints[WAY_DETAILS])
    {
    // init_update(&wpoints[WAY_DETAILS]);
    //kitchen_update(&wpoints[WAY_DETAILS]);
        for(w_points=INIT_START;w_points<INIT_END;w_points++)
        {        
		 wpoints[w_points].index =w_points;
	     wpoints[w_points].delay_value =2000;
	     wpoints[w_points].previous_index =w_points-1;

            if(w_points==(INIT_START+4u))
            {
            wpoints[w_points].my_wheel_heading =ROTATE_RIGHT;
	        wpoints[w_points].heading_angle =90;

            }
            else if (w_points==(INIT_START+9u))
            {
            wpoints[w_points].my_wheel_heading =ROTATE_LEFT;
	        wpoints[w_points].heading_angle =90;
            }
            else
            {
            wpoints[w_points].my_wheel_heading =FORWARD;
	        wpoints[w_points].heading_angle =0;
            }
        }
        for(w_points=KITCHEN_START;w_points<KITCHEN_END;w_points++)
        {
        wpoints[w_points].index =w_points;
	    wpoints[w_points].delay_value =0xFFFF;
	    wpoints[w_points].previous_index =w_points-1;
            if(w_points==KITCHEN_START)
            {
            wpoints[w_points].my_wheel_heading =BACK_ROTATION;
	        wpoints[w_points].heading_angle =180;
            }
            else if ((w_points==(KITCHEN_START+3u)) || (w_points==(KITCHEN_START+9u)) || (w_points==(KITCHEN_START+18u)))
            {
            wpoints[w_points].my_wheel_heading =ROTATE_RIGHT;
	        wpoints[w_points].heading_angle =90;
            }
            else if(w_points==(KITCHEN_START+12u))
            {
            wpoints[w_points].my_wheel_heading =ROTATE_LEFT;
	        wpoints[w_points].heading_angle =90;
            }
            else
            {
            wpoints[w_points].my_wheel_heading =FORWARD;
	        wpoints[w_points].heading_angle =0;
            }
        }
    }


void sensor_status_update(uint8_t *fs_status)
{
    /* PIN PA0 read for sensor value */
    if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==GPIO_PIN_SET)
	{
	    *fs_status=true;

	}
	else
	{
	    *fs_status=false;
    }

}
void init_update(waypoint_info wpoints[WAY_DETAILS])
{
        

        for(int w_points=INIT_START;w_points<INIT_END;w_points++)
        {        
		wpoints[w_points].index =w_points;
	    wpoints[w_points].delay_value =2000;
	    wpoints[w_points].previous_index =w_points-1;

            if(w_points==(INIT_START+4u))
            {
            wpoints[w_points].my_wheel_heading =ROTATE_RIGHT;
	        wpoints[w_points].heading_angle =90;

            }
            else if (w_points==(INIT_START+9u))
            {
            wpoints[w_points].my_wheel_heading =ROTATE_LEFT;
	        wpoints[w_points].heading_angle =90;
            }
            else
            {
            wpoints[w_points].my_wheel_heading =FORWARD;
	        wpoints[w_points].heading_angle =0;
            }
       }

       
}

//void kitchen_update(waypoint_info *wpoints[WAY_DETAILS])
//{
//    for(w_points=KITCHEN_START;w_points<KITCHEN_END;w_points++)
//    {
//    wpoints[w_points]->index =w_points;
//	wpoints[w_points]->delay_value =2000;
//	wpoints[w_points]->previous_index =wpoints[w_points]->index-1;
//        if(w_points==KITCHEN_START)
//        {
//        wpoints[w_points]->my_wheel_heading =BACK_ROTATION;
//	    wpoints[w_points]->heading_angle =180;
//        }
//        else if ((w_points==(KITCHEN_START+3u)) || (w_points==(KITCHEN_START+9u)) || (w_points==(KITCHEN_START+18u)))
//        {
//        wpoints[w_points]->my_wheel_heading =ROTATE_RIGHT;
//	    wpoints[w_points]->heading_angle =90;
//        }
//        else if(w_points==(KITCHEN_START+12u))
//        {
//        wpoints[w_points]->my_wheel_heading =ROTATE_LEFT;
//	    wpoints[w_points]->heading_angle =90;
//        }
//        else
//        {
//        wpoints[w_points]->my_wheel_heading =FORWARD;
//	    wpoints[w_points]->heading_angle =0;
//        }
//    }
//
//}
