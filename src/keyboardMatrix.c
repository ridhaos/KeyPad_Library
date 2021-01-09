/**
 *
 *                 Copyright (C) Noomane Ridha
 *
 * This source code is free to usefor any project
 *
 * \file keyboardMatrix.c
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

/*==========================================================================*/
/*       I N C L U D E S                                                    */
/*==========================================================================*/
#include "keyboardMatrix.h"
#include "keybaordMatrix_def.h"


/*==========================================================================*/
/*       L O C A L   D A T A   D E C L A R A T I O N S                      */
/*==========================================================================*/
typedef enum
{
	KEYPAD_LOW =0,
	KEYPAD_HIGH
}writeReadKeypadState_t;

static uint16_t arrayOfRowPin[4]           = {KEYPAD_ROW_1_PIN, KEYPAD_ROW_2_PIN, KEYPAD_ROW_3_PIN, KEYPAD_ROW_4_PIN};
static uint16_t arrayOfColumnPin[4]        = {KEYPAD_COLUMN_1_PIN, KEYPAD_COLUMN_2_PIN, KEYPAD_COLUMN_3_PIN, KEYPAD_COLUMN_4_PIN};
static GPIO_TypeDef * arrayOfRowPort[4]    = {KEYPAD_ROW_1_PORT, KEYPAD_ROW_2_PORT, KEYPAD_ROW_3_PORT, KEYPAD_ROW_4_PORT};
static GPIO_TypeDef * arrayOfColumnPort[4] = {KEYPAD_COLUMN_1_PORT, KEYPAD_COLUMN_2_PORT, KEYPAD_COLUMN_3_PORT, KEYPAD_COLUMN_4_PORT};

static const char keys[4][4] = {{'1','2','3','A'},
																{'4','5','6','B'},
																{'7','8','9','C'},
																{'*','0','#','D'}};
/*==========================================================================*/
/*       L O C A L   F U N C T I O N S   P R O T O T Y P E S                */
/*==========================================================================*/			
																
/*!
 * @brief This function set all bits of row at HIGH state.
 *
 * @param writeReadKeypadState_t
 * @return none
 */
static void WriteRowBits(writeReadKeypadState_t);	
																
/*!
 * @brief This function read columns states.
 *
 * @param none
 * @return writeReadKeypadState_t
 */																
static writeReadKeypadState_t ReadColumnsBits(void);
	
/*==========================================================================*/
/*       G L O B A L  F U N C T I O N S                                     */
/*==========================================================================*/

/*!
 * @brief Keypad Init all rows GPIO and Columns GPIO
 *
 * @param none
 * @return none
 */
void keyboardInit()
{
	GPIO_InitTypeDef GPIO_Column_InitStruct = {0};
	GPIO_InitTypeDef GPIO_Ligne_InitStruct = {0};


	for(uint8_t i = 0; i<KEYPAD_MAX_COLUMN; i++)
	{
		/* Active Clock for Row Port */
		if(arrayOfColumnPort[i] == GPIOA)
		__RCC_GPIOA_KEYPAD_CLK_ENABLE();
	  else if(arrayOfColumnPort[i] == GPIOB)
		__RCC_GPIOB_KEYPAD_CLK_ENABLE();
		else if(arrayOfColumnPort[i] == GPIOC)
		__RCC_GPIOC_KEYPAD_CLK_ENABLE();
		else if(arrayOfColumnPort[i] == GPIOD)
		__RCC_GPIOD_KEYPAD_CLK_ENABLE();
		else if(arrayOfColumnPort[i] == GPIOE)
		__RCC_GPIOE_KEYPAD_CLK_ENABLE();
		else if(arrayOfColumnPort[i] == GPIOF)
		__RCC_GPIOF_KEYPAD_CLK_ENABLE();
		else if(arrayOfColumnPort[i] == GPIOG)
		__RCC_GPIOG_KEYPAD_CLK_ENABLE();
		
		/* Configure Column Pins */
#if defined (USE_HAL_DRIVER)
		GPIO_Ligne_InitStruct.Pin   = arrayOfColumnPin[i];
		GPIO_Ligne_InitStruct.Mode  = GPIO_MODE_IT_RISING;
		GPIO_Ligne_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(arrayOfColumnPort[i], &GPIO_Column_InitStruct);
		
#else
		GPIO_Column_InitStruct.GPIO_Pin    = arrayOfColumnPin[i];
		GPIO_Column_InitStruct.GPIO_Mode   = GPIO_Mode_IPD;
		GPIO_Init(arrayOfColumnPort[i], &GPIO_Column_InitStruct);
#endif
	}
	
	for(uint8_t i = 0; i < KEYPAD_MAX_ROW; i++)
	{
		if(arrayOfRowPort[i] == GPIOA)
		__RCC_GPIOA_KEYPAD_CLK_ENABLE();
	  else if(arrayOfRowPort[i] == GPIOB)
		__RCC_GPIOB_KEYPAD_CLK_ENABLE();
		else if(arrayOfRowPort[i] == GPIOC)
		__RCC_GPIOC_KEYPAD_CLK_ENABLE();
		else if(arrayOfRowPort[i] == GPIOD)
		__RCC_GPIOD_KEYPAD_CLK_ENABLE();
		else if(arrayOfRowPort[i] == GPIOE)
		__RCC_GPIOE_KEYPAD_CLK_ENABLE();
		else if(arrayOfRowPort[i] == GPIOF)
		__RCC_GPIOF_KEYPAD_CLK_ENABLE();
		else if(arrayOfRowPort[i] == GPIOG)
		__RCC_GPIOG_KEYPAD_CLK_ENABLE();
		
		
		/* Configure Row Pins */
#if defined (USE_HAL_DRIVER)
		GPIO_Ligne_InitStruct.Pin   = arrayOfRowPin[i];
		GPIO_Ligne_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
		GPIO_Ligne_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
		HAL_GPIO_Init(arrayOfRowPort[i], &GPIO_Ligne_InitStruct);
		
#else
		GPIO_Ligne_InitStruct.GPIO_Pin		 = arrayOfRowPin[i];
		GPIO_Ligne_InitStruct.GPIO_Mode    = GPIO_Mode_Out_PP;
		GPIO_Ligne_InitStruct.GPIO_Speed   = GPIO_Speed_10MHz;
	  GPIO_Init(arrayOfRowPort[i], &GPIO_Ligne_InitStruct);
#endif
	}

}


/*!
 * @brief return key pressed.
 *
 * @param none
 * @return char
 */
char getKeyPressed()
{
	uint8_t check = 0;
	char keyPressed = '\0';

	WriteRowBits(KEYPAD_HIGH);
	while(!ReadColumnsBits());
	WriteRowBits(KEYPAD_LOW);
	
	for(uint8_t i = 0 ; i < KEYPAD_MAX_ROW; i++)
	{
#if defined (USE_HAL_DRIVER)
	  HAL_GPIO_WritePin(arrayOfRowPort[i], arrayOfRowPin[i], GPIO_PIN_SET);
#else
		GPIO_SetBits(arrayOfRowPort[i], arrayOfRowPin[i]);
#endif
		for(uint8_t j = 0; j < KEYPAD_MAX_COLUMN ; j++)
		{
#if defined (USE_HAL_DRIVER)
		  check = (uint8__t)HAL_GPIO_ReadPin(arrayOfColumnPort[j], arrayOfColumnPin[j]);
#else
			check = GPIO_ReadInputDataBit(arrayOfColumnPort[j], arrayOfColumnPin[j]);
#endif
			if(check == 1)
			{
				keyPressed =  keys[i][j];
				return keyPressed;
			}
		}
		WriteRowBits(KEYPAD_LOW);
	}
	
	return keyPressed;

}

/*!
 * @brief This function set all bits of row at HIGH state.
 *
 * @param writeReadKeypadState_t
 * @return none
 */
static void WriteRowBits(writeReadKeypadState_t state)
{
	switch(state)
	{
		case KEYPAD_HIGH:
			for(uint8_t i = 0; i < KEYPAD_MAX_ROW; i++)
			{
#if defined (USE_HAL_DRIVER)
				HAL_GPIO_WritePin(arrayOfRowPort[i], arrayOfRowPin[i], GPIO_PIN_SET);
#else
				GPIO_SetBits(arrayOfRowPort[i], arrayOfRowPin[i]);
#endif
			}
			break;
		case KEYPAD_LOW:
			for(uint8_t i = 0; i < KEYPAD_MAX_ROW; i++)
			{
#if defined (USE_HAL_DRIVER)
				HAL_GPIO_WritePin(arrayOfRowPort[i], arrayOfRowPin[i], GPIO_PIN_RESET);
#else
				GPIO_ResetBits(arrayOfRowPort[i], arrayOfRowPin[i]);
#endif
			}			
			break;
	}
}

/*!
 * @brief This function read columns states.
 *
 * @param none
 * @return writeReadKeypadState_t
 */
static writeReadKeypadState_t ReadColumnsBits(void)
{
	uint8_t check = 0;
	for(uint8_t i = 0; i < KEYPAD_MAX_COLUMN; i++)
	{
#if defined (USE_HAL_DRIVER)
		check = (uint8__t)HAL_GPIO_ReadPin(arrayOfColumnPort[i], arrayOfColumnPin[i]);
#else
		check = GPIO_ReadInputDataBit(arrayOfColumnPort[i], arrayOfColumnPin[i]);
#endif
		if(check == 1)
				return KEYPAD_HIGH;
	}
	return KEYPAD_LOW;
}
