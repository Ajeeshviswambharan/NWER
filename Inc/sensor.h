
/* Private includes ----------------------------------------------------------*/
#include "user.h"
#include <string.h>
/* USER CODE BEGIN Includes */
/* Exported macro ------------------------------------------------------------*/
typedef enum
{
    UART_CHECK=0,
    UART_DATA,
    UART_UNK

}Uart_Statemachine;
static Uart_Statemachine my_uart_se=UART_CHECK;
/* USER CODE BEGIN EM */
char rx_buffer_gps[25];
uint8_t rxData_ledon[32]="ONE RECEIVED SO LED WILL ON\r\n";
uint8_t rxData_ledoz[33]="ZERO RECEIVED SO LED WILL OFF\r\n";
uint8_t rxData_ledou[17]="UNKNOWN ENTRY\r\n";
uint8_t rxData_wrong[24]="WRONG DATA...........\r\n";
/* USER CODE END EM */
void message_handle(char *msg);
void gps_valuereceive(void);
/* Exported functions prototypes ---------------------------------------------*/
