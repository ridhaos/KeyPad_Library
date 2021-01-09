/**
 *
 *                 Copyright (C) Noomane Ridha
 *
 * This source code is free to use for any project
 *
 * \file debug.h
 *
 * \version 1.0
 *
 * \date 25 June 2020
 *
 * \brief
 *
 *
 * \section info Change Information
 *	
 *
*/

#ifndef __DEBUG__H__
#define __DEBUG__H__

#include <stdio.h>
#include <stdarg.h>
#include "stm32f10x.h"  

#define DEBUG_UART_PORT					 USART2


/*!
 * @brief PRINTF function used to print character via UART.
 * 	print only char, int and float type.
 * @param Char, ...,
 * @return none
 */
void PRINTF(const char *c, ...);


#endif /* __DEBUG__H__ */
