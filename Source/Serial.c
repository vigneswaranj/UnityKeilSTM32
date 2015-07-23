/*----------------------------------------------------------------------------
 * Name:    Serial.c
 * Purpose: Low Level Serial Routines
 * Note(s): possible defines select the used communication interface:
 *            __DBG_ITM   - ITM SWO interface
 *            __USART1    - USART1 interface
 *                        - USART2 interface  (default)
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2008-2011 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include "STM32F10x.h"
#include "Serial.h"

#ifdef __DBG_ITM
volatile int ITM_RxBuffer = ITM_RXBUFFER_EMPTY;  /*  CMSIS Debug Input        */
#endif


/*----------------------------------------------------------------------------
 Define  USART 
 *----------------------------------------------------------------------------*/
#ifdef __USART1
  #define USARTx  USART1
#else
  #define USARTx  USART2
#endif


/*----------------------------------------------------------------------------
 Define  Baudrate setting (BRR) for USART 
 *----------------------------------------------------------------------------*/
#define __DIV(__PCLK, __BAUD)       ((__PCLK*25)/(4*__BAUD))
#define __DIVMANT(__PCLK, __BAUD)   (__DIV(__PCLK, __BAUD)/100)
#define __DIVFRAQ(__PCLK, __BAUD)   (((__DIV(__PCLK, __BAUD) - (__DIVMANT(__PCLK, __BAUD) * 100)) * 16 + 50) / 100)
#define __USART_BRR(__PCLK, __BAUD) ((__DIVMANT(__PCLK, __BAUD) << 4)|(__DIVFRAQ(__PCLK, __BAUD) & 0x0F))


/*----------------------------------------------------------------------------
  Initialize UART pins, Baudrate
 *----------------------------------------------------------------------------*/
void SER_Init (void) {
#ifndef __DBG_ITM
  int i;

#ifdef __USART1                            /* USART1 */
  RCC->APB2ENR |=  (   1UL <<  0);         /* enable clock Alternate Function */
  AFIO->MAPR   &= ~(   1UL <<  2);         /* clear USART1 remap              */

  RCC->APB2ENR |=  (   1UL <<  2);         /* enable GPIOA clock              */
  GPIOA->CRH   &= ~(0xFFUL <<  4);         /* clear PA9, PA10                 */
  GPIOA->CRH   |=  (0x0BUL <<  4);         /* USART1 Tx (PA9) output push-pull*/
  GPIOA->CRH   |=  (0x04UL <<  8);         /* USART1 Rx (PA10) input floating */

  RCC->APB2ENR |=  (   1UL << 14);         /* enable USART#1 clock            */
#else                                      /* USART2 */
  RCC->APB2ENR |=  (   1UL <<  0);         /* enable clock Alternate Function */
  AFIO->MAPR   &= ~(   1UL <<  3);         /* clear USART2 remap              */

  RCC->APB2ENR |=  (   1UL <<  2);         /* enable GPIOA clock              */
  GPIOA->CRL   &= ~(0xFFUL <<  8);         /* clear PA2, PA3                  */
  GPIOA->CRL   |=  (0x0BUL <<  8);         /* USART2 Tx (PA2) output push-pull*/
  GPIOA->CRL   |=  (0x04UL << 12);         /* USART2 Rx (PA3) input floating  */

  RCC->APB1ENR |=  (   1UL << 17);         /* enable USART#2 clock            */
#endif

  USARTx->BRR  = __USART_BRR(72000000UL, 115200UL);  /* 115200 baud @ 72MHz   */
  USARTx->CR3   = 0x0000;                  /* no flow control                 */
  USARTx->CR2   = 0x0000;                  /* 1 stop bit                      */
  for (i = 0; i < 0x1000; i++) __NOP();    /* avoid unwanted output           */
  USARTx->CR1   = ((   1UL <<  2) |        /* enable RX                       */
                   (   1UL <<  3) |        /* enable TX                       */
                   (   0UL << 12) |        /* 1 start bit, 8 data bits        */
                   (   1UL << 13) );       /* enable USART                    */

#endif
}


/*----------------------------------------------------------------------------
  Write character to Serial Port
 *----------------------------------------------------------------------------*/
int SER_PutChar (int c) {

#ifdef __DBG_ITM
    ITM_SendChar(c);
#else
  while (!(USARTx->SR & 0x0080));
  USARTx->DR = (c & 0x1FF);
#endif
  return (c);
}


/*----------------------------------------------------------------------------
  Read character from Serial Port   (blocking read)
 *----------------------------------------------------------------------------*/
int SER_GetChar (void) {

#ifdef __DBG_ITM
  while (ITM_CheckChar() != 1) __NOP();
  return (ITM_ReceiveChar());
#else
  while (!(USARTx->SR & 0x0020));
  return (USARTx->DR & 0x1FF);
#endif
}


/*----------------------------------------------------------------------------
  Check if a character is received
 *----------------------------------------------------------------------------*/
int SER_CheckChar (void) {

#ifdef __DBG_ITM
  return (ITM_CheckChar());
#else
  if (USARTx->SR & 0x0020)
    return (1);
  else
    return (0);
#endif
}
