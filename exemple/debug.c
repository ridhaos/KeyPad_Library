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
 * This file define Simple Printf via USART.
 *
 * \section info Change Information
 *	
 *
*/

#include "debug.h"


/*!
 * @brief numberToString function used to convert number to string.
 *
 * @param Char, ...,
 * @return none
 */
static int iNumberToString(int i, char * array)
{
    int length = 0;

    if(i == 0)
    {
        array[0] = 0;
				while (!((DEBUG_UART_PORT->SR & USART_SR_TXE) >> 7));
				DEBUG_UART_PORT->DR = (array[0] + '0') & (uint16_t)0x01FF ;
        return 1;
    }
    if(i<0)
    {
        while (!((DEBUG_UART_PORT->SR & USART_SR_TXE) >> 7));
				DEBUG_UART_PORT->DR = ('-') & (uint16_t)0x01FF ;
        i = i * -1;
    }
    while(i>0)
    {
        array[length] = i % 10;
        i = i/10;
        length++;
    }
    for(int k = length-1; k>=0; k--)
		{
        while (!((DEBUG_UART_PORT->SR & USART_SR_TXE) >> 7));
				DEBUG_UART_PORT->DR = (array[k] + '0') & (uint16_t)0x01FF ;
		}
    return length;
}

/*!
 * @brief PRINTF function used to print character via UART.
 *
 * @param Char, ...,
 * @return none
 */
void PRINTF(const char *c, ...)
{
    va_list va;
    
    char valDigit[33] = {0};
    int length = 0;
    va_start(va, c);
    while(*c != '\0')
    {
        if(*c == '%')
        {
            c++;
            length=0;
            switch(*c)
            {
                case 'd':
                case 'i':
                    {
                        int i = va_arg(va, int);
                        length = iNumberToString(i, valDigit);
                    }    
                break;
                case 'f':
                {
                    double f = 0;
                    int i = 0, j=0,p=0;
                    double digit=0;
                    f = va_arg(va, double);
                    i = (int)f;
                    p = iNumberToString(i, valDigit);
                    j=p;
                    digit=(f-i)*10;
                    while((int)digit!=0)
                    {
                        valDigit[j]  = (int)digit;
                        digit=(digit - (int)digit) * 10;
                        j++;
                    }
                    
                    for(int k = p; k<j; k++)
                    {
                            if(k == p)
														{
                                while (!((DEBUG_UART_PORT->SR & USART_SR_TXE) >> 7));
																DEBUG_UART_PORT->DR = ('.') & (uint16_t)0x01FF ;
														}
														while (!((DEBUG_UART_PORT->SR & USART_SR_TXE) >> 7));
														DEBUG_UART_PORT->DR = ('0' + valDigit[k]) & (uint16_t)0x01FF ;
                            
                    }
                } 
                break;
								case 'c':
								{
									char i = (char)va_arg(va, int);
									while (!((DEBUG_UART_PORT->SR & USART_SR_TXE) >> 7));
									DEBUG_UART_PORT->DR = (i) & (uint16_t)0x01FF ;
							
								}
							}
        }else{
           while (!((DEBUG_UART_PORT->SR & USART_SR_TXE) >> 7));
					 DEBUG_UART_PORT->DR = (*c) & (uint16_t)0x01FF ;
        }
        
        c++;
    }
    va_end(va);
}



