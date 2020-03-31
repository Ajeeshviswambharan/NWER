/*
Library:				STM32F40x Internal FLASH read/write
Written by:			Mohamed Yaqoob (MYaqoobEmbedded YouTube Channel)
Last modified:	15/03/2019
Description:
							MY_FLASH library implements the following basic functionalities
								- Set sectos address
								- Flash Sector Erase
								- Flash Write
								- Flash Read

* Copyright (C) 2019 - M. Yaqoob
   This is a free software under the GNU license, you can redistribute it and/or modify it under the terms
   of the GNU General Public Licenseversion 3 as published by the Free Software Foundation.

   This software library is shared with puplic for educational purposes, without WARRANTY and Author is not liable for any damages caused directly
   or indirectly by this software, read more about this on the GNU General Public License.
*/

#include "stm32f0xx_hal.h"
#include <stdbool.h>
//Typedefs
//1. data size
#define TOTAL_POINTS 	30
#define WAY_DETAILS 	7

typedef enum
{
	DATA_TYPE_8=0,
	DATA_TYPE_16,
	DATA_TYPE_32,
}DataTypeDef;

typedef enum
{
	STOP=0,
	FORWARD,
	BACKWARD,
	ROTATE_RIGHT,
	ROTATE_LEFT,
	REVERSE
}wheel_heading;

typedef enum
{
	SLEEP = 0,
	RUNNING, 
	INTERRUPT
}newr_STM_mode;

typedef struct
{
	uint32_t index;
	wheel_heading my_wheel_heading;
	int32_t heading_angle;
	uint32_t delay_value;	
	uint32_t dummy;
	newr_STM_mode stm_mode; 
	uint32_t previous_index;
	bool PIR_VALUE;
}waypoint_info;


extern waypoint_info my_way_poits[TOTAL_POINTS];
extern waypoint_info my_way_poits_r[TOTAL_POINTS];
void store_waypoit_D(waypoint_info wpoints[WAY_DETAILS]);

//functions prototypes
//1. Erase Sector
void MY_FLASH_EraseSector(uint32_t PageAddress);

//2. Set Sector Adress
void MY_FLASH_SetSectorAddrs(uint8_t sector, uint32_t addrs);
//3. Write Flash
void MY_FLASH_WriteN(uint32_t idx, waypoint_info *wrBuf[][WAY_DETAILS], uint32_t Nsize, DataTypeDef dataType);
//4. Read Flash
void MY_FLASH_ReadN(uint32_t idx,waypoint_info *rdBuf[][WAY_DETAILS], uint32_t Nsize, DataTypeDef dataType);














