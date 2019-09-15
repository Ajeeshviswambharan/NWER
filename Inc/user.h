/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include "main.h"
#include "cmsis_os.h"

/*variables Declaration*/

extern UART_HandleTypeDef huart2;

/*function declaration */
extern bool start_init(void);
extern void motor_cyclic_uart_check(void);
extern void sensor_cyclic_uart_check(void);
extern void gps_cyclic_uart_check(void);
