
/* Private includes ----------------------------------------------------------*/
#include "user.h"
#include <string.h>
#include "my_flash.h"
/* USER CODE BEGIN Includes */
/* Exported macro ------------------------------------------------------------*/
typedef enum
{
    UART_CHECK=0,
    UART_DATA,
    UART_UNK

}Uart_Statemachine;

/* USER CODE BEGIN EM */

/* USER CODE END EM */
void message_handle(char *msg);
void gps_valuereceive(void);
/* Exported functions prototypes ---------------------------------------------*/
