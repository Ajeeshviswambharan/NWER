
/* Private includes ----------------------------------------------------------*/
#include "user.h"


/* USER CODE BEGIN Includes */
/* Exported macro ------------------------------------------------------------*/

/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void motor_control(waypoint_info nwer_info[WAY_DETAILS],uint8_t mode,uint8_t mode_sub);
void forward();
void backward();
void leftturn();
void rightturn();
void turnaround();
void stop();
