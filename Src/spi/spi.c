/*
 * motor.c
 *
 *  Created on: Sep 24, 2019
 *      Author: AJEESH
 */

/* Used  for updation of Sensor codes */
/* Private includes ----------------------------------------------------------*/
#include "spi_header.h"




/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN Includes */
void spi_update( uint8_t *n_mode,uint8_t *n_submode)
{
    *n_mode=(newr_mode)INTIAL_MODE;
    *n_submode=(newr_sub_mode)NO_SUB;
}