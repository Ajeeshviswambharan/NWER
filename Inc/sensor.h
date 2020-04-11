
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

#define INIT_START 	    (0u)
#define INIT_END 	    (12u)
#define KITCHEN_START 	(15u)
#define KITCHEN_END 	(39u)
/* USER CODE BEGIN EM */

/* USER CODE END EM */
void message_handle(char *msg);
void gps_valuereceive(void);
void sensor_status_update(uint8_t *fs_status);
void init_update(waypoint_info wpoints[WAY_DETAILS]);
void kitchen_update(waypoint_info *wpoints[WAY_DETAILS]);
/* Exported functions prototypes ---------------------------------------------*/
