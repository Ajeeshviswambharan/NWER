
/* Private includes ----------------------------------------------------------*/
#include "sensor.h"


/* USER CODE BEGIN Includes */
/* Exported macro ------------------------------------------------------------*/
#define ON          1u
#define OFF         0u
extern uint8_t way_numer;
extern uint8_t way_numer_backup;

/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void motor_control(waypoint_info nwer_info[WAY_DETAILS],uint8_t mode,uint8_t mode_sub,uint8_t fs_status);
void forward();
void backward();
void leftturn();
void rightturn();
void turnaround();
void stop();
