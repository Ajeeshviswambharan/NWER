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
                store_waypoit_D(my_way_poits);
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
							wpoints[0].index =0;
	                        wpoints[0].my_wheel_heading =FORWARD;
	                        wpoints[0].heading_angle =0;
	                        wpoints[0].delay_value =2000;
	                        wpoints[0].mode =INTIAL_MODE;
	                        wpoints[0].stm_mode =RUNNING;
                            wpoints[0].mode_sub = NO_SUB;
	                        wpoints[0].previous_index =0;
                for(uint32_t i=1;i<TOTAL_POINTS;i++)
                    {
                        wpoints[i].index =i;
                        wpoints[i].my_wheel_heading =REVERSE;
                        wpoints[i].heading_angle =360;
                        wpoints[i].delay_value =2000;
                        wpoints[i].mode =INTIAL_MODE;
                        wpoints[i].stm_mode =RUNNING;
                        wpoints[i].mode_sub = BD1;
                        wpoints[i].previous_index =i-1;
                    }

    }
