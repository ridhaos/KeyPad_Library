/**
 *
 *                 Copyright (C) Noomane Ridha
 *
 * This source code is free to usefor any project
 *
 * \file keyboardMatrix.h
 *
 * \version 1.0
 *
 * \date 25 June 2020
 *
 * \brief
 *
 * Use this File to define your rows GPIO and column GPIO
 *
 * \section info Change Information
 *
 *
*/

#ifndef __KEYBOARD_MATRIX_DEF_H__
#define __KEYBOARD_MATRIX_DEF_H__


/* Here define your keypad type for exemple : 4x4*/
/* Keypad Type available : 4x4, 3x3, 4x3, 3x4 */
#define KEYPAD_MAX_ROW				4
#define KEYPAD_MAX_COLUMN			4

/*Here define Row Port and Pin*/
#define KEYPAD_ROW_1_PORT      GPIOA
#define KEYPAD_ROW_1_PIN			 GPIO_Pin_5
#define KEYPAD_ROW_2_PORT      GPIOA
#define KEYPAD_ROW_2_PIN			 GPIO_Pin_6
#define KEYPAD_ROW_3_PORT      GPIOA
#define KEYPAD_ROW_3_PIN			 GPIO_Pin_7
#if (KEYPAD_MAX_ROW == 4)
#define KEYPAD_ROW_4_PORT			 GPIOA
#define KEYPAD_ROW_4_PIN			 GPIO_Pin_9
#endif

/*Here define Column Port and Pin*/
#define KEYPAD_COLUMN_1_PORT   GPIOB
#define KEYPAD_COLUMN_1_PIN		 GPIO_Pin_8
#define KEYPAD_COLUMN_2_PORT   GPIOB
#define KEYPAD_COLUMN_2_PIN    GPIO_Pin_6
#define KEYPAD_COLUMN_3_PORT   GPIOB
#define KEYPAD_COLUMN_3_PIN    GPIO_Pin_5
#if (KEYPAD_MAX_COLUMN == 4)
#define KEYPAD_COLUMN_4_PORT   GPIOB
#define KEYPAD_COLUMN_4_PIN    GPIO_Pin_10
#endif


#if defined (USE_HAL_DRIVER)
#define	__RCC_GPIOA_KEYPAD_CLK_ENABLE()    __HAL_RCC_GPIOA_CLK_ENABLE()
#define	__RCC_GPIOB_KEYPAD_CLK_ENABLE()    __HAL_RCC_GPIOB_CLK_ENABLE()
#define	__RCC_GPIOC_KEYPAD_CLK_ENABLE()    __HAL_RCC_GPIOC_CLK_ENABLE()
#define	__RCC_GPIOD_KEYPAD_CLK_ENABLE()    __HAL_RCC_GPIOD_CLK_ENABLE()
#define	__RCC_GPIOE_KEYPAD_CLK_ENABLE()    __HAL_RCC_GPIOE_CLK_ENABLE()
#define	__RCC_GPIOF_KEYPAD_CLK_ENABLE()    __HAL_RCC_GPIOF_CLK_ENABLE()
#define	__RCC_GPIOG_KEYPAD_CLK_ENABLE()    __HAL_RCC_GPIOG_CLK_ENABLE()
#else	
	
#define	__RCC_GPIOA_KEYPAD_CLK_ENABLE()		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE)
#define	__RCC_GPIOB_KEYPAD_CLK_ENABLE()		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE)
#define	__RCC_GPIOC_KEYPAD_CLK_ENABLE()		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE)
#define	__RCC_GPIOD_KEYPAD_CLK_ENABLE()		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE)
#define	__RCC_GPIOE_KEYPAD_CLK_ENABLE()		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE)
#define	__RCC_GPIOF_KEYPAD_CLK_ENABLE()		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE)
#define	__RCC_GPIOG_KEYPAD_CLK_ENABLE()		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE)
#endif

#endif /* __KEYBOARD_MATRIX_DEF_H__ */
