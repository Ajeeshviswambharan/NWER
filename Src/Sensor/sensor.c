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
uint32_t my_test_data[180]={0,01,20,38.639,135.66,0x373736799,0x373736799,0x373736799,0x373736799,0x363636,\
							0x363636,0x3737367,0x3737367,0x3737367,0x3737367,0x373736799,0x373736799,0x373736799,0x373736799,0x363636,\
							0x363636,0x3737367,0x3737367,0x3737367,0x3737367,0x373736799,0x373736799,0x373736799,0x373736799,0x363636,\
							0x363636,0x3737367,0x3737367,0x3737367,0x3737367,0x373736799,0x373736799,0x373736799,0x373736799,0x363636,\
							0x363636,0x3737367,0x3737367,0x3737367,0x3737367,0x373736799,0x373736799,0x373736799,0x373736799,0x363636,\
							0x363636,0x3737367,0x3737367,0x3737367,0x3737367,0x373736799,0x373736799,0x373736799,0x373736799,0x363636,\
							0x363636,0x3737367,0x3737367,0x3737367,0x3737367,0x373736799,0x373736799,0x373736799,0x373736799,0x363636,\
							0x363636,0x3737367,0x3737367,0x3737367,0x3737367,0x373736799,0x373736799,0x373736799,0x373736799,0x363636,\
							0x363636,0x3737367,0x3737367,0x3737367,0x3737367,0x373736799,0x373736799,0x373736799,0x373736799,0x363636,\
							0x363636,0x3737367,0x3737367,0x3737367,0x3737367,0x373736799,0x373736799,0x373736799,0x373736799,0x363636,\
							0x363636,0x3737367,0x3737367,0x3737367,0x3737367,0x373736799,0x373736799,0x373736799,0x373736799,0x363636,\
							0x363636,0x3737367,0x3737367,0x3737367,0x3737367,0x373736799,0x373736799,0x373736799,0x373736799,0x363636,\
							0x363636,0x3737367,0x3737367,0x3737367,0x3737367,0x373736799,0x373736799,0x373736799,0x373736799,0x363636,\
							0x363636,0x3737367,0x3737367,0x3737367,0x3737367,0x373736799,0x373736799,0x373736799,0x373736799,0x363636,\
							0x363636,0x3737367,0x3737367,0x3737367,0x3737367,0x373736799,0x373736799,0x373736799,0x373736799,0x363636,\
							0x363636,0x3737367,0x3737367,0x3737367,0x3737367,0x373736799,0x373736799,0x373736799,0x373736799,0x363636,\
							0x363636,0x3737367,0x3737367,0x3737367,0x3737367,0x373736799,0x373736799,0x373736799,0x373736799,0x363636,\
							0x363636,0x3737367,0x3737367,0x3737367,0x3737367,0x373736799,0x373736799,0x373736799,0x373736799,0x363636,\
																																																																						0x363636,0x3737367,0x3737367,0x3737367,0x3737367,0x373736799,0x373736799,0x373736799,0x373736799,\
																																																	0x363636,0x3737367,0x3737367,0x3737367,0x3737367,0x373736799,0x373736799,0x373736799,0x373736799,\
																																																								0x363636,0x3737367,0x3737367,0x3737367,0x3737367,0x373736799,0x373736799,0x373736799,0x373736799,\
};
uint32_t my_test_read[180];


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
  /* Check for the Received value */
  MY_FLASH_SetSectorAddrs(15,0x0800F000);
  MY_FLASH_WriteN(0,my_test_data,180,DATA_TYPE_32);
  MY_FLASH_ReadN(0,my_test_read,180,DATA_TYPE_32);
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



//   if((rx_buffer_gps[0]=='*') && (rx_buffer_gps[2]=='#') )//Valid vata
// 	{
// 		if(rx_buffer_gps[1]== 1)//LED ON
// 			{
// 				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,1);	
// 				HAL_UART_Transmit(&huart2,rxData_ledon,32,1);
// 			}
// 		else if(rx_buffer_gps[1]== 0 )//LED OFF
// 			{
// 				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,0);	
// 				HAL_UART_Transmit(&huart2,rxData_ledoz,33,1);	
			
// 			}
// 		else
// 			{
// 			/* Recevied data is unknown */
// 			HAL_UART_Transmit(&huart2,rxData_ledou,17,1);	
// 			}
		
// 	}
// 	else
// 	{
// 		{
// 			HAL_UART_Receive_DMA(&huart2,(uint8_t *)rx_buffer_gps,3);
// 		}
// 	}
	
//}
