/*==========================================================================*/
/*       I N C L U D E S                                                    */
/*==========================================================================*/
#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>
#include "debug.h"
#include "keyboardMatrix.h"

/*==========================================================================*/
/*       G L O B A L   D A T A   D E C L A R A T I O N S                    */
/*==========================================================================*/
#define MAX_ACCESS_CODE 		4 // Max Code to read it by keypad
/*==========================================================================*/
/*       L O C A L   D A T A   D E C L A R A T I O N S                      */
/*==========================================================================*/
typedef enum
{
	ACCESS_DENIED = 0,
  ACCESS_CONFIRM
}gAccess_Status_t;

/* Define here you Secret Code */ 
static const char accessCode[MAX_ACCESS_CODE] = {'C', '0', 'D', 'A'};

/* Define Array to stock User input key pressed */
static char userCode[MAX_ACCESS_CODE] = {'\0'};
/*==========================================================================*/
/*       L O C A L   F U N C T I O N S   P R O T O T Y P E S                */
/*==========================================================================*/
/*!
 * @brief This function set UART2 for Nucleo-STM32F103RB.
 *
 * @param none
 * @return none
 */
void vInitUart(void);

/*!
 * @brief This function configure systick.
 *
 * @param none
 * @return none
 */
void vConfigSystick(void);

/*!
 * @brief Delay function in ms 
 *
 * @param uint32_t wain in ms
 * @return none
 */
void vDelay(uint32_t waitMS);

/*==========================================================================*/
/*       G L O B A L  F U N C T I O N S                                     */
/*==========================================================================*/			

/*!
 * @brief Main function.
 *
 * @param none
 * @return none
 */
int main()
{
	gAccess_Status_t test = ACCESS_CONFIRM;
	char keyPressed = '\0';
	vInitUart();
	keyboardInit();
	vConfigSystick();

	/*  Message Banner */

	PRINTF("  '##:::'##:'########:'##:::'##:'########:::::'###::::'########:::::'########:'##::::'##:\n");
	PRINTF("   ##::'##:: ##.....::. ##:'##:: ##.... ##:::'## ##::: ##.... ##:::: ##.....::. ##::'##::\n");
	PRINTF("   ##:'##::: ##::::::::. ####::: ##:::: ##::'##:. ##:: ##:::: ##:::: ##::::::::. ##'##:::\n");
	PRINTF("   #####:::: ######:::::. ##:::: ########::'##:::. ##: ##:::: ##:::: ######:::::. ###::::\n");
	PRINTF("   ##. ##::: ##...::::::: ##:::: ##.....::: #########: ##:::: ##:::: ##...:::::: ## ##:::\n");
	PRINTF("   ##:. ##:: ##:::::::::: ##:::: ##:::::::: ##.... ##: ##:::: ##:::: ##:::::::: ##:. ##::\n");
	PRINTF("   ##::. ##: ########:::: ##:::: ##:::::::: ##:::: ##: ########::::: ########: ##:::. ##:\n");
	PRINTF("  ..::::..::........:::::..:::::..:::::::::..:::::..::........::::::........::..:::::..::\n");


	
	
  PRINTF("\n Press any key to start\n");
	
	while(1)
	{


		PRINTF("CODE: \n\t");
		for(uint8_t i = 0; i < MAX_ACCESS_CODE; i++)
		{
			
			keyPressed = getKeyPressed();
			userCode[i] = keyPressed;
			PRINTF("* ");
			vDelay(500);
		}
		
		PRINTF("\n");
		
		for(uint8_t i = 0; i < MAX_ACCESS_CODE; i++)
		{
			if(userCode[i] != accessCode[i])
			{
				test = ACCESS_DENIED;
				break;
			}
		}
		
		if(test == ACCESS_CONFIRM)
		{
			PRINTF("Welcome MR Noomane Acces code right\n");
		}else if (test == ACCESS_DENIED){
			PRINTF("Acces Denied !!!!!!!!!!!!!!!!\n");
		}

		test = ACCESS_CONFIRM;
	}
}

/*!
 * @brief This function set UART2 for Nucleo-STM32F103RB.
 *
 * @param none
 * @return none
 */
void vInitUart(void)
{

	/* Active Clock for GPIOA and UART2 */
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	/* Configure UART BRR register : Baud Rate Register*/
	USART2->BRR = 0x138; // For Baudrate = 115200 and based on PCLK1 ... See STM32 reference manual for more information.
	
	/* Enable UART For Transmitter and Receiver */
	USART2->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
	

	/**USART2 GPIO Configuration    
		PA2     ------> USART2_TX
		PA3     ------> USART2_RX 
	*/
	GPIOA->CRL = (GPIOA->CRL 
						 & ~GPIO_CRL_CNF2
						 & ~GPIO_CRL_CNF3
						 & ~GPIO_CRL_MODE2	
						 & ~GPIO_CRL_MODE3)
						 | GPIO_CRL_CNF2_1
						 | GPIO_CRL_CNF3_1
					   | GPIO_CRL_MODE2_0
						 | GPIO_CRL_MODE3_0
					   ;
}

/*!
 * @brief This function configure systick.
 *
 * @param none
 * @return none
 */
void vConfigSystick(void)
{
	SysTick->CTRL = 0x00;
	SysTick->VAL	= 0x00;
	SysTick->LOAD = SystemCoreClock / 1000;
	SysTick->CTRL = 0x05U;
}

/*!
 * @brief Delay function in ms 
 *
 * @param uint32_t wain in ms
 * @return none
 */
void vDelay(uint32_t waitMS)
{
	for(uint32_t i = 0; i < waitMS; i++)	
		while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
}

