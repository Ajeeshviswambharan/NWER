/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include "main.h"
#include "cmsis_os.h"
#include "my_flash.h"
/*variables Declaration*/
typedef enum
{
	CHARGING_M = 0,
	INTIAL_MODE,
	SERVICE_M,
	CLEANING,
	NIGHT
}newr_mode;

typedef enum
{
	NO_SUB = 0,
	KITCHEN, 
	BD1
}newr_sub_mode;

extern volatile uint8_t mode;
extern volatile uint8_t submode;
extern volatile uint8_t fs_status;

extern UART_HandleTypeDef huart2;
/* DMA Handler */
extern DMA_HandleTypeDef hdma_usart2_rx;
/*function declaration */
extern bool start_init(void);
extern void motor_cyclic_uart_check(void);
extern void joystick_cyclic_uart_check(void);
extern void spi_cyclic_check(void);
void gps_valuereceive(void);
void pir_iot_cyclic_check(void);
void revert_state();
