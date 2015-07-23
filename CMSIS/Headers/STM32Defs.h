/* ===============================================================
   == CMSIS Library                                             ==
   == Copyright Rotork Controls Ltd                             ==
   ===============================================================
   == $Workfile::   STM32Defs.h                               $ ==
   == $Revision::   1.6                                       $ ==
   ==  $Modtime::   22 Jun 2009 15:53:10                      $ ==
   ==   $Author::   Alan Budden                               $ ==
   ==                                                           ==
   == Compiler:     Keil uVision                                ==
   == Target:       STM32                                       ==
   == Description:  STM32 Extra Definitions                     ==
   ==                                                           ==
   =============================================================== */

#ifndef _STM32DEFS_H
#define _STM32DEFS_H

/* == include files ============================================== */
#include "stm32f10x.h"

/* == #defines =================================================== */
/* The Keil library headers don't include a lot of bit definitions,
   so we add our own */

/**
 * @{
 * Pin Macros.
 *
 * These are a hardware abstraction layer and are not intended to be used
 * directly: they are remapped to other macros with more meaningful names.
 *
 * Call as (e.g.):
 * 
 *     PIN_SetHigh(GPIOA, 0)
 *
 * or:
 *     
 *     #define PORT_LED_BLUE GPIOB
 *     #define PIN_LED_BLUE  ((u8) 5)
 *     #define LED_BlueOn    PIN_SetLow(PORT_LED_BLUE, PIN_LED_BLUE)
 *     #define LED_BlueOff   PIN_SetHigh(PORT_LED_BLUE, PIN_LED_BLUE)
 */

/** Check whether an input GPIO pin is currently high. */
#define PIN_IsHigh(port, u8Number) GLOBAL_bIsTrue(((port)->IDR  & (((u32) 1) << (u8Number))) == (((u32) 1) << (u8Number)))
/** Check whether an input GPIO pin is currently high (alternative name for naming convention) */
#define PIN_bIsHigh(port, u8Number) PIN_IsHigh(port, u8Number)
/** Check whether an input GPIO pin is currently low. */
#define PIN_IsLow(port, u8Number)  GLOBAL_bIsFalse(((port)->IDR & (((u32) 1) << (u8Number))) == (((u32) 1) << (u8Number)))
/** Check whether an input GPIO pin is currently low (alternative name for naming convention) */
#define PIN_bIsLow(port, u8Number) PIN_IsLow(port, u8Number)
/** Drive an output GPIO pin high or set it to pull-up mode (depending on whether it's an output or input). */
#define PIN_SetHigh(port, u8Number)   MACROOP((port)->BSRR = (u32) (((u32) 1) << (u8Number));)
/** Drive an output GPIO pin low or set it to pull-down mode (depending on whether it's an output or input). */
#define PIN_SetLow(port, u8Number)    MACROOP((port)->BRR  = (u32) (((u32) 1) << (u8Number));)
/** Toggle the state of an output GPIO pin. */
#define PIN_Toggle(port, u8Number) \
	MACROOP((port)->BSRR = \
			PIN_IsHigh(port, u8Number) \
			? ((u32) (((u32) 1) << (u8Number+16))) \
			: ((u32) (((u32) 1) << (u8Number)));)
/** Set a pin in a required mode. */
/* TODO: Consider making this into a function.
 * Need to decide where to put the source for the function and how to handle Lint if
 * it isn't then used.
 */
#define PIN_SetMode(port, u8Number, mode)                           \
	MACROOP(                                                        \
			/*lint -save -e774 -e506 -e778 */                       \
			/* These errors are related to the fact that */         \
			/* different code will be produced depending on */      \
			/* whether u8Number is 0-7 or 8-15 */                   \
			u8 u8Shift = (u8) (((u8) (((u8) u8Number) & 0x07u)) << 2u);    \
			u32 u32Mask = (u32) (((u32) 0x0Fu) << u8Shift);         \
			if (u8Number < 8)                                       \
			{                                                       \
				(port)->CRL &= (u32) ~u32Mask;                      \
				(port)->CRL |= ((u32) (((u32) mode) ) << u8Shift);  \
			}                                                       \
			else                                                    \
			{                                                       \
				(port)->CRH &= (u32) ~u32Mask;                      \
				(port)->CRH |= ((u32) (((u32) mode) ) << u8Shift);  \
			}                                                       \
			/*lint -restore */                                      \
			)

/** Pin is analogue input */
#define PIN_InputAnalogue (GPIO_CR_MODE_In | GPIO_CR_CNF_InAnalog)
/** Pin is input with pull up or pull down */
#define PIN_InputPull (GPIO_CR_MODE_In | GPIO_CR_CNF_InPull)
/** Pin is floating input */
#define PIN_InputFloat (GPIO_CR_MODE_In | GPIO_CR_CNF_InFloat)
/** Pin is a 2MHz max output in push-pull GPIO mode */
#define PIN_OutputGPIO_PP2MHz (GPIO_CR_MODE_Out2MHz | GPIO_CR_CNF_OutGP_PP)
/** Pin is a 2MHz max output in open-drain GPIO mode */
#define PIN_OutputGPIO_OD2MHz (GPIO_CR_MODE_Out2MHz | GPIO_CR_CNF_OutGP_OD)
/** Pin is a 2MHz max output in push-pull AFIO mode */
#define PIN_OutputAFIO_PP2MHz (GPIO_CR_MODE_Out2MHz | GPIO_CR_CNF_OutAF_PP)
/** Pin is a 2MHz max output in open-drain AFIO mode */
#define PIN_OutputAFIO_OD2MHz (GPIO_CR_MODE_Out2MHz | GPIO_CR_CNF_OutAF_OD)
/** Pin is a 10MHz max output in push-pull GPIO mode */
#define PIN_OutputGPIO_PP10MHz (GPIO_CR_MODE_Out10MHz | GPIO_CR_CNF_OutGP_PP)
/** Pin is a 10MHz max output in open-drain GPIO mode */
#define PIN_OutputGPIO_OD10MHz (GPIO_CR_MODE_Out10MHz | GPIO_CR_CNF_OutGP_OD)
/** Pin is a 10MHz max output in push-pull AFIO mode */
#define PIN_OutputAFIO_PP10MHz (GPIO_CR_MODE_Out10MHz | GPIO_CR_CNF_OutAF_PP)
/** Pin is a 10MHz max output in open-drain AFIO mode */
#define PIN_OutputAFIO_OD10MHz (GPIO_CR_MODE_Out10MHz | GPIO_CR_CNF_OutAF_OD)
/** Pin is a 50MHz max output in push-pull GPIO mode */
#define PIN_OutputGPIO_PP50MHz (GPIO_CR_MODE_Out50MHz | GPIO_CR_CNF_OutGP_PP)
/** Pin is a 50MHz max output in open-drain GPIO mode */
#define PIN_OutputGPIO_OD50MHz (GPIO_CR_MODE_Out50MHz | GPIO_CR_CNF_OutGP_OD)
/** Pin is a 50MHz max output in push-pull AFIO mode */
#define PIN_OutputAFIO_PP50MHz (GPIO_CR_MODE_Out50MHz | GPIO_CR_CNF_OutAF_PP)
/** Pin is a 50MHz max output in open-drain AFIO mode */
#define PIN_OutputAFIO_OD50MHz (GPIO_CR_MODE_Out50MHz | GPIO_CR_CNF_OutAF_OD)

/** Set a pin as an analogue input */
#define PIN_SetInputAnalogue(port, u8Number) PIN_SetMode(port, u8Number, PIN_InputAnalogue)
/** Set a pin as a pulled input */
#define PIN_SetInputPull(port, u8Number) PIN_SetMode(port, u8Number, PIN_InputPull)
/** Set a pin as a floating input */
#define PIN_SetInputFloat(port, u8Number) PIN_SetMode(port, u8Number, PIN_InputFloat)
/** Set a pin as a 2MHz max output in push-pull GPIO mode */
#define PIN_SetOutputGPIO_PP2MHz(port, u8Number) PIN_SetMode(port, u8Number, PIN_OutputGPIO_PP2MHz)
/** Set a pin as a 2MHz max output in open-drain GPIO mode */
#define PIN_SetOutputGPIO_OD2MHz(port, u8Number) PIN_SetMode(port, u8Number, PIN_OutputGPIO_OD2MHz)
/** Set a pin as a 2MHz max output in push-pull AFIO mode */
#define PIN_SetOutputAFIO_PP2MHz(port, u8Number) PIN_SetMode(port, u8Number, PIN_OutputAFIO_PP2MHz)
/** Set a pin as a 2MHz max output in open-drain AFIO mode */
#define PIN_SetOutputAFIO_OD2MHz(port, u8Number) PIN_SetMode(port, u8Number, PIN_OutputAFIO_OD2MHz)
/** Set a pin as a 10MHz max output in push-pull GPIO mode */
#define PIN_SetOutputGPIO_PP10MHz(port, u8Number) PIN_SetMode(port, u8Number, PIN_OutputGPIO_PP10MHz)
/** Set a pin as a 10MHz max output in open-drain GPIO mode */
#define PIN_SetOutputGPIO_OD10MHz(port, u8Number) PIN_SetMode(port, u8Number, PIN_OutputGPIO_OD10MHz)
/** Set a pin as a 10MHz max output in push-pull AFIO mode */
#define PIN_SetOutputAFIO_PP10MHz(port, u8Number) PIN_SetMode(port, u8Number, PIN_OutputAFIO_PP10MHz)
/** Set a pin as a 10MHz max output in open-drain AFIO mode */
#define PIN_SetOutputAFIO_OD10MHz(port, u8Number) PIN_SetMode(port, u8Number, PIN_OutputAFIO_OD10MHz)
/** Set a pin as a 50MHz max output in push-pull GPIO mode */
#define PIN_SetOutputGPIO_PP50MHz(port, u8Number) PIN_SetMode(port, u8Number, PIN_OutputGPIO_PP50MHz)
/** Set a pin as a 50MHz max output in open-drain GPIO mode */
#define PIN_SetOutputGPIO_OD50MHz(port, u8Number) PIN_SetMode(port, u8Number, PIN_OutputGPIO_OD50MHz)
/** Set a pin as a 50MHz max output in push-pull AFIO mode */
#define PIN_SetOutputAFIO_PP50MHz(port, u8Number) PIN_SetMode(port, u8Number, PIN_OutputAFIO_PP50MHz)
/** Set a pin as a 50MHz max output in open-drain AFIO mode */
#define PIN_SetOutputAFIO_OD50MHz(port, u8Number) PIN_SetMode(port, u8Number, PIN_OutputAFIO_OD50MHz)

/** @} */

/** Reset the CPU. */
#define CPU_Reset() MACROOP(SCB->AIRCR = (SCB->AIRCR & ((u32) 0x0000FFFFu)) | ((u32) 0x05FA0004u);)

/* --------------------------------------------------------------- */
/* Power control (PWR) */

/* PWR_CR: Power control register */

#define PWR_CR_PLS_2_2V    (u32) 0x00000000
#define PWR_CR_PLS_2_3V    (PWR_CR_PLS_0)
#define PWR_CR_PLS_2_4V    (PWR_CR_PLS_1)
#define PWR_CR_PLS_2_5V    (PWR_CR_PLS_0 | PWR_CR_PLS_1)
#define PWR_CR_PLS_2_6V    (PWR_CR_PLS_2)
#define PWR_CR_PLS_2_7V    (PWR_CR_PLS_2 | PWR_CR_PLS_0)
#define PWR_CR_PLS_2_8V    (PWR_CR_PLS_2 | PWR_CR_PLS_1)
#define PWR_CR_PLS_2_9V    (PWR_CR_PLS_2 | PWR_CR_PLS_1 | PWR_CR_PLS_0)

/* --------------------------------------------------------------- */
/* USART Configuration */
#define USART_CR2_STOP_1_BIT  ((u16) 0)
#define USART_CR2_STOP_0_5_BIT  USART_CR2_STOP_0
#define USART_CR2_STOP_2_BITS USART_CR2_STOP_1
#define USART_CR2_STOP_1_5_BITS (USART_CR2_STOP_1 | USART_CR2_STOP_0)

/* --------------------------------------------------------------- */
/* Reset & clock control (RCC) */

/* Clock control register (RCC_CR) */

#define RCC_CR_HSITRIM_MASK  (u32) 0x000000F8
#define RCC_CR_HSITRIM_SHIFT (u8) 3

#define RCC_CR_Default       ((u32) 0x00000083)
#define RCC_CFGR_Default     ((u32) 0x00000000)


/* Windowed Watchdog registers */
#define WWDG_CFR_WDGTB_1   (u32) 0x00000000
#define WWDG_CFR_WDGTB_2   (u32) 0x00000080
#define WWDG_CFR_WDGTB_4   (u32) 0x00000100
#define WWDG_CFR_WDGTB_8   (u32) 0x00000180


/* --------------------------------------------------------------- */
/* GPIO */

/* Pins */
#define GPIO_Pin_0                 ((u16)0x0001)  /* Pin 0 selected */
#define GPIO_Pin_1                 ((u16)0x0002)  /* Pin 1 selected */
#define GPIO_Pin_2                 ((u16)0x0004)  /* Pin 2 selected */
#define GPIO_Pin_3                 ((u16)0x0008)  /* Pin 3 selected */
#define GPIO_Pin_4                 ((u16)0x0010)  /* Pin 4 selected */
#define GPIO_Pin_5                 ((u16)0x0020)  /* Pin 5 selected */
#define GPIO_Pin_6                 ((u16)0x0040)  /* Pin 6 selected */
#define GPIO_Pin_7                 ((u16)0x0080)  /* Pin 7 selected */
#define GPIO_Pin_8                 ((u16)0x0100)  /* Pin 8 selected */
#define GPIO_Pin_9                 ((u16)0x0200)  /* Pin 9 selected */
#define GPIO_Pin_10                ((u16)0x0400)  /* Pin 10 selected */
#define GPIO_Pin_11                ((u16)0x0800)  /* Pin 11 selected */
#define GPIO_Pin_12                ((u16)0x1000)  /* Pin 12 selected */
#define GPIO_Pin_13                ((u16)0x2000)  /* Pin 13 selected */
#define GPIO_Pin_14                ((u16)0x4000)  /* Pin 14 selected */
#define GPIO_Pin_15                ((u16)0x8000)  /* Pin 15 selected */
#define GPIO_Pin_All               ((u16)0xFFFF)  /* All pins selected */

#define GPIO_Pin_N(u8Number)       ((u16) (1u << u8Number))

/* GPIOx_CRy: Port configuration registers */
/* Mode */
#define GPIO_CR_MODE_In          (u32) 0x0
#define GPIO_CR_MODE_Out10MHz    (u32) 0x1
#define GPIO_CR_MODE_Out2MHz     (u32) 0x2
#define GPIO_CR_MODE_Out50MHz    (u32) 0x3
/* Inputs */
#define GPIO_CR_CNF_InAnalog     (u32) 0x0
#define GPIO_CR_CNF_InFloat      (u32) 0x4
#define GPIO_CR_CNF_InPull       (u32) 0x8
#define GPIO_CR_CNF_InReserved   (u32) 0xC
/* Outputs */
#define GPIO_CR_CNF_OutGP_PP     (u32) 0x0 /* General purpose; push-pull */
#define GPIO_CR_CNF_OutGP_OD     (u32) 0x4 /* General purpose; open drain */
#define GPIO_CR_CNF_OutAF_PP     (u32) 0x8 /* Alternate function; push-pull*/
#define GPIO_CR_CNF_OutAF_OD     (u32) 0xC /* Alternate function; open drain */

/* GPIOx_CRH: Port configuration register high */
#define GPIO_CRH15(u4Config)   (u32) ((u4Config) << 28)
#define GPIO_CRH14(u4Config)   (u32) ((u4Config) << 24)
#define GPIO_CRH13(u4Config)   (u32) ((u4Config) << 20)
#define GPIO_CRH12(u4Config)   (u32) ((u4Config) << 16)
#define GPIO_CRH11(u4Config)   (u32) ((u4Config) << 12)
#define GPIO_CRH10(u4Config)   (u32) ((u4Config) <<  8)
#define GPIO_CRH09(u4Config)   (u32) ((u4Config) <<  4)
#define GPIO_CRH08(u4Config)   (u32) ((u4Config) <<  0)

/* GPIOx_CRL: Port configuration register low */
#define GPIO_CRL07(u4Config)   (u32) ((u4Config) << 28)
#define GPIO_CRL06(u4Config)   (u32) ((u4Config) << 24)
#define GPIO_CRL05(u4Config)   (u32) ((u4Config) << 20)
#define GPIO_CRL04(u4Config)   (u32) ((u4Config) << 16)
#define GPIO_CRL03(u4Config)   (u32) ((u4Config) << 12)
#define GPIO_CRL02(u4Config)   (u32) ((u4Config) <<  8)
#define GPIO_CRL01(u4Config)   (u32) ((u4Config) <<  4)
#define GPIO_CRL00(u4Config)   (u32) ((u4Config) <<  0)

/* --------------------------------------------------------------- */
/* NVIC */

#ifdef STM32F10X_CL

/** Interrupt Enable for Window Watchdog interrupt global interrupt. */
#define NVIC_ISER0_WWDG          ((u32) 0x00000001)
/** Interrupt Enable for PVD through EXTI Line detection interrupt global interrupt. */
#define NVIC_ISER0_PVD           ((u32) 0x00000002)
/** Interrupt Enable for Tamper interrupt global interrupt. */
#define NVIC_ISER0_TAMPER        ((u32) 0x00000004)
/** Interrupt Enable for RTC global interrupt global interrupt. */
#define NVIC_ISER0_RTC           ((u32) 0x00000008)
/** Interrupt Enable for Flash global interrupt global interrupt. */
#define NVIC_ISER0_FLASH         ((u32) 0x00000010)
/** Interrupt Enable for RCC global interrupt global interrupt. */
#define NVIC_ISER0_RCC           ((u32) 0x00000020)
/** Interrupt Enable for EXTI Line0 interrupt global interrupt. */
#define NVIC_ISER0_EXTI0         ((u32) 0x00000040)
/** Interrupt Enable for EXTI Line1 interrupt global interrupt. */
#define NVIC_ISER0_EXTI1         ((u32) 0x00000080)
/** Interrupt Enable for EXTI Line2 interrupt global interrupt. */
#define NVIC_ISER0_EXTI2         ((u32) 0x00000100)
/** Interrupt Enable for EXTI Line3 interrupt global interrupt. */
#define NVIC_ISER0_EXTI3         ((u32) 0x00000200)
/** Interrupt Enable for EXTI Line4 interrupt global interrupt. */
#define NVIC_ISER0_EXTI4         ((u32) 0x00000400)
/** Interrupt Enable for DMA1 Channel1 global interrupt global interrupt. */
#define NVIC_ISER0_DMA1_Channel1 ((u32) 0x00000800)
/** Interrupt Enable for DMA1 Channel2 global interrupt global interrupt. */
#define NVIC_ISER0_DMA1_Channel2 ((u32) 0x00001000)
/** Interrupt Enable for DMA1 Channel3 global interrupt global interrupt. */
#define NVIC_ISER0_DMA1_Channel3 ((u32) 0x00002000)
/** Interrupt Enable for DMA1 Channel4 global interrupt global interrupt. */
#define NVIC_ISER0_DMA1_Channel4 ((u32) 0x00004000)
/** Interrupt Enable for DMA1 Channel5 global interrupt global interrupt. */
#define NVIC_ISER0_DMA1_Channel5 ((u32) 0x00008000)
/** Interrupt Enable for DMA1 Channel6 global interrupt global interrupt. */
#define NVIC_ISER0_DMA1_Channel6 ((u32) 0x00010000)
/** Interrupt Enable for DMA1 Channel7 global interrupt global interrupt. */
#define NVIC_ISER0_DMA1_Channel7 ((u32) 0x00020000)
/** Interrupt Enable for ADC1 and ADC2 global interrupt global interrupt. */
#define NVIC_ISER0_ADC1_2        ((u32) 0x00040000)
/** Interrupt Enable for CAN1 TX interrupts global interrupt. */
#define NVIC_ISER0_CAN1_TX       ((u32) 0x00080000)
/** Interrupt Enable for CAN1 RX0 interrupts global interrupt. */
#define NVIC_ISER0_CAN1_RX0      ((u32) 0x00100000)
/** Interrupt Enable for CAN1 RX1 interrupt global interrupt. */
#define NVIC_ISER0_CAN1_RX1      ((u32) 0x00200000)
/** Interrupt Enable for CAN1 SCE interrupt global interrupt. */
#define NVIC_ISER0_CAN1_SCE      ((u32) 0x00400000)
/** Interrupt Enable for EXTI Line[9:5] interrupts global interrupt. */
#define NVIC_ISER0_EXTI9_5       ((u32) 0x00800000)
/** Interrupt Enable for TIM1 Break interrupt global interrupt. */
#define NVIC_ISER0_TIM1_BRK      ((u32) 0x01000000)
/** Interrupt Enable for TIM1 Update interrupt global interrupt. */
#define NVIC_ISER0_TIM1_UP       ((u32) 0x02000000)
/** Interrupt Enable for TIM1 Trigger and Commutation interrupts global interrupt. */
#define NVIC_ISER0_TIM1_TRG_COM  ((u32) 0x04000000)
/** Interrupt Enable for TIM1 Capture Compare interrupt global interrupt. */
#define NVIC_ISER0_TIM1_CC       ((u32) 0x08000000)
/** Interrupt Enable for TIM2 global interrupt global interrupt. */
#define NVIC_ISER0_TIM2          ((u32) 0x10000000)
/** Interrupt Enable for TIM3 global interrupt global interrupt. */
#define NVIC_ISER0_TIM3          ((u32) 0x20000000)
/** Interrupt Enable for TIM4 global interrupt global interrupt. */
#define NVIC_ISER0_TIM4          ((u32) 0x40000000)
/** Interrupt Enable for I2C1 event interrupt global interrupt. */
#define NVIC_ISER0_I2C1_EV       ((u32) 0x80000000)
/** Interrupt Enable for I2C1 error interrupt global interrupt. */
#define NVIC_ISER1_I2C1_ER       ((u32) 0x00000001)
/** Interrupt Enable for I2C2 event interrupt global interrupt. */
#define NVIC_ISER1_I2C2_EV       ((u32) 0x00000002)
/** Interrupt Enable for I2C2 error interrupt global interrupt. */
#define NVIC_ISER1_I2C2_ER       ((u32) 0x00000004)
/** Interrupt Enable for SPI1 global interrupt global interrupt. */
#define NVIC_ISER1_SPI1          ((u32) 0x00000008)
/** Interrupt Enable for SPI2 global interrupt global interrupt. */
#define NVIC_ISER1_SPI2          ((u32) 0x00000010)
/** Interrupt Enable for USART1 global interrupt global interrupt. */
#define NVIC_ISER1_USART1        ((u32) 0x00000020)
/** Interrupt Enable for USART2 global interrupt global interrupt. */
#define NVIC_ISER1_USART2        ((u32) 0x00000040)
/** Interrupt Enable for USART3 global interrupt global interrupt. */
#define NVIC_ISER1_USART3        ((u32) 0x00000080)
/** Interrupt Enable for EXTI Line[15:10] interrupts global interrupt. */
#define NVIC_ISER1_EXTI15_10     ((u32) 0x00000100)
/** Interrupt Enable for RTC alarm through EXTI line interrupt global interrupt. */
#define NVIC_ISER1_RTCAlarm      ((u32) 0x00000200)
/** Interrupt Enable for USB On-The-Go FS Wakeup through EXTI line interrupt global interrupt. */
#define NVIC_ISER1_OTG_FS_WKUP   ((u32) 0x00000400)
/* RESERVED SPACE IN HERE */
/** Interrupt Enable for TIM5 global interrupt global interrupt. */
#define NVIC_ISER1_TIM5          ((u32) 0x00040000)
/** Interrupt Enable for SPI3 global interrupt global interrupt. */
#define NVIC_ISER1_SPI3          ((u32) 0x00080000)
/** Interrupt Enable for UART4 global interrupt global interrupt. */
#define NVIC_ISER1_UART4         ((u32) 0x00100000)
/** Interrupt Enable for UART5 global interrupt global interrupt. */
#define NVIC_ISER1_UART5         ((u32) 0x00200000)
/** Interrupt Enable for TIM6 global interrupt global interrupt. */
#define NVIC_ISER1_TIM6          ((u32) 0x00400000)
/** Interrupt Enable for TIM7 global interrupt global interrupt. */
#define NVIC_ISER1_TIM7          ((u32) 0x00800000)
/** Interrupt Enable for DMA2 Channel1 global interrupt global interrupt. */
#define NVIC_ISER1_DMA2_Channel1 ((u32) 0x01000000)
/** Interrupt Enable for DMA2 Channel2 global interrupt global interrupt. */
#define NVIC_ISER1_DMA2_Channel2 ((u32) 0x02000000)
/** Interrupt Enable for DMA2 Channel3 global interrupt global interrupt. */
#define NVIC_ISER1_DMA2_Channel3 ((u32) 0x04000000)
/** Interrupt Enable for DMA2 Channel4 global interrupt global interrupt. */
#define NVIC_ISER1_DMA2_Channel4 ((u32) 0x08000000)
/** Interrupt Enable for DMA2 Channel5 global interrupt global interrupt. */
#define NVIC_ISER1_DMA2_Channel5 ((u32) 0x10000000)
/** Interrupt Enable for Ethernet global interrupt global interrupt. */
#define NVIC_ISER1_ETH           ((u32) 0x20000000)
/** Interrupt Enable for Ethernet Wakeup through EXTI line interrupt global interrupt. */
#define NVIC_ISER1_ETH_WKUP      ((u32) 0x40000000)
/** Interrupt Enable for CAN2 TX interrupts global interrupt. */
#define NVIC_ISER1_CAN2_TX       ((u32) 0x80000000)
/** Interrupt Enable for CAN2 RX0 interrupts global interrupt. */
#define NVIC_ISER2_CAN2_RX0      ((u32) 0x00000001)
/** Interrupt Enable for CAN2 RX1 interrupt global interrupt. */
#define NVIC_ISER2_CAN2_RX1      ((u32) 0x00000002)
/** Interrupt Enable for CAN2 SCE interrupt global interrupt. */
#define NVIC_ISER2_CAN2_SCE      ((u32) 0x00000004)
/** Interrupt Enable for USB On The Go FS global interrupt global interrupt. */
#define NVIC_ISER2_OTG_FS        ((u32) 0x00000008)

/* Indices into the NVIC->IP array of u8 priorities. */

/** Interrupt Priority Address for Window Watchdog interrupt global interrupt. */
#define NVIC_IP_INDEX_WWDG          ((u8) 0)
/** Interrupt Priority Address for PVD through EXTI Line detection interrupt global interrupt. */
#define NVIC_IP_INDEX_PVD           ((u8) 1)
/** Interrupt Priority Address for Tamper interrupt global interrupt. */
#define NVIC_IP_INDEX_TAMPER        ((u8) 2)
/** Interrupt Priority Address for RTC global interrupt global interrupt. */
#define NVIC_IP_INDEX_RTC           ((u8) 3)
/** Interrupt Priority Address for Flash global interrupt global interrupt. */
#define NVIC_IP_INDEX_FLASH         ((u8) 4)
/** Interrupt Priority Address for RCC global interrupt global interrupt. */
#define NVIC_IP_INDEX_RCC           ((u8) 5)
/** Interrupt Priority Address for EXTI Line0 interrupt global interrupt. */
#define NVIC_IP_INDEX_EXTI0         ((u8) 6)
/** Interrupt Priority Address for EXTI Line1 interrupt global interrupt. */
#define NVIC_IP_INDEX_EXTI1         ((u8) 7)
/** Interrupt Priority Address for EXTI Line2 interrupt global interrupt. */
#define NVIC_IP_INDEX_EXTI2         ((u8) 8)
/** Interrupt Priority Address for EXTI Line3 interrupt global interrupt. */
#define NVIC_IP_INDEX_EXTI3         ((u8) 9)
/** Interrupt Priority Address for EXTI Line4 interrupt global interrupt. */
#define NVIC_IP_INDEX_EXTI4         ((u8) 10)
/** Interrupt Priority Address for DMA1 Channel1 global interrupt global interrupt. */
#define NVIC_IP_INDEX_DMA1_Channel1 ((u8) 11)
/** Interrupt Priority Address for DMA1 Channel2 global interrupt global interrupt. */
#define NVIC_IP_INDEX_DMA1_Channel2 ((u8) 12)
/** Interrupt Priority Address for DMA1 Channel3 global interrupt global interrupt. */
#define NVIC_IP_INDEX_DMA1_Channel3 ((u8) 13)
/** Interrupt Priority Address for DMA1 Channel4 global interrupt global interrupt. */
#define NVIC_IP_INDEX_DMA1_Channel4 ((u8) 14)
/** Interrupt Priority Address for DMA1 Channel5 global interrupt global interrupt. */
#define NVIC_IP_INDEX_DMA1_Channel5 ((u8) 15)
/** Interrupt Priority Address for DMA1 Channel6 global interrupt global interrupt. */
#define NVIC_IP_INDEX_DMA1_Channel6 ((u8) 16)
/** Interrupt Priority Address for DMA1 Channel7 global interrupt global interrupt. */
#define NVIC_IP_INDEX_DMA1_Channel7 ((u8) 17)
/** Interrupt Priority Address for ADC1 and ADC2 global interrupt global interrupt. */
#define NVIC_IP_INDEX_ADC1_2        ((u8) 18)
/** Interrupt Priority Address for CAN1 TX interrupts global interrupt. */
#define NVIC_IP_INDEX_CAN1_TX       ((u8) 19)
/** Interrupt Priority Address for CAN1 RX0 interrupts global interrupt. */
#define NVIC_IP_INDEX_CAN1_RX0      ((u8) 20)
/** Interrupt Priority Address for CAN1 RX1 interrupt global interrupt. */
#define NVIC_IP_INDEX_CAN1_RX1      ((u8) 21)
/** Interrupt Priority Address for CAN1 SCE interrupt global interrupt. */
#define NVIC_IP_INDEX_CAN1_SCE      ((u8) 22)
/** Interrupt Priority Address for EXTI Line[9:5] interrupts global interrupt. */
#define NVIC_IP_INDEX_EXTI9_5       ((u8) 23)
/** Interrupt Priority Address for TIM1 Break interrupt global interrupt. */
#define NVIC_IP_INDEX_TIM1_BRK      ((u8) 24)
/** Interrupt Priority Address for TIM1 Update interrupt global interrupt. */
#define NVIC_IP_INDEX_TIM1_UP       ((u8) 25)
/** Interrupt Priority Address for TIM1 Trigger and Commutation interrupts global interrupt. */
#define NVIC_IP_INDEX_TIM1_TRG_COM  ((u8) 26)
/** Interrupt Priority Address for TIM1 Capture Compare interrupt global interrupt. */
#define NVIC_IP_INDEX_TIM1_CC       ((u8) 27)
/** Interrupt Priority Address for TIM2 global interrupt global interrupt. */
#define NVIC_IP_INDEX_TIM2          ((u8) 28)
/** Interrupt Priority Address for TIM3 global interrupt global interrupt. */
#define NVIC_IP_INDEX_TIM3          ((u8) 29)
/** Interrupt Priority Address for TIM4 global interrupt global interrupt. */
#define NVIC_IP_INDEX_TIM4          ((u8) 30)
/** Interrupt Priority Address for I2C1 event interrupt global interrupt. */
#define NVIC_IP_INDEX_I2C1_EV       ((u8) 31)
/** Interrupt Priority Address for I2C1 error interrupt global interrupt. */
#define NVIC_IP_INDEX_I2C1_ER       ((u8) 32)
/** Interrupt Priority Address for I2C2 event interrupt global interrupt. */
#define NVIC_IP_INDEX_I2C2_EV       ((u8) 33)
/** Interrupt Priority Address for I2C2 error interrupt global interrupt. */
#define NVIC_IP_INDEX_I2C2_ER       ((u8) 34)
/** Interrupt Priority Address for SPI1 global interrupt global interrupt. */
#define NVIC_IP_INDEX_SPI1          ((u8) 35)
/** Interrupt Priority Address for SPI2 global interrupt global interrupt. */
#define NVIC_IP_INDEX_SPI2          ((u8) 36)
/** Interrupt Priority Address for USART1 global interrupt global interrupt. */
#define NVIC_IP_INDEX_USART1        ((u8) 37)
/** Interrupt Priority Address for USART2 global interrupt global interrupt. */
#define NVIC_IP_INDEX_USART2        ((u8) 38)
/** Interrupt Priority Address for USART3 global interrupt global interrupt. */
#define NVIC_IP_INDEX_USART3        ((u8) 39)
/** Interrupt Priority Address for EXTI Line[15:10] interrupts global interrupt. */
#define NVIC_IP_INDEX_EXTI15_10     ((u8) 40)
/** Interrupt Priority Address for RTC alarm through EXTI line interrupt global interrupt. */
#define NVIC_IP_INDEX_RTCAlarm      ((u8) 41)
/** Interrupt Priority Address for USB On-The-Go FS Wakeup through EXTI line interrupt global interrupt. */
#define NVIC_IP_INDEX_OTG_FS_WKUP   ((u8) 42)
/* RESERVED SPACE HERE */
/** Interrupt Priority Address for TIM5 global interrupt global interrupt. */
#define NVIC_IP_INDEX_TIM5          ((u8) 50)
/** Interrupt Priority Address for SPI3 global interrupt global interrupt. */
#define NVIC_IP_INDEX_SPI3          ((u8) 51)
/** Interrupt Priority Address for UART4 global interrupt global interrupt. */
#define NVIC_IP_INDEX_UART4         ((u8) 52)
/** Interrupt Priority Address for UART5 global interrupt global interrupt. */
#define NVIC_IP_INDEX_UART5         ((u8) 53)
/** Interrupt Priority Address for TIM6 global interrupt global interrupt. */
#define NVIC_IP_INDEX_TIM6          ((u8) 54)
/** Interrupt Priority Address for TIM7 global interrupt global interrupt. */
#define NVIC_IP_INDEX_TIM7          ((u8) 55)
/** Interrupt Priority Address for DMA2 Channel1 global interrupt global interrupt. */
#define NVIC_IP_INDEX_DMA2_Channel1 ((u8) 56)
/** Interrupt Priority Address for DMA2 Channel2 global interrupt global interrupt. */
#define NVIC_IP_INDEX_DMA2_Channel2 ((u8) 57)
/** Interrupt Priority Address for DMA2 Channel3 global interrupt global interrupt. */
#define NVIC_IP_INDEX_DMA2_Channel3 ((u8) 58)
/** Interrupt Priority Address for DMA2 Channel4 global interrupt global interrupt. */
#define NVIC_IP_INDEX_DMA2_Channel4 ((u8) 59)
/** Interrupt Priority Address for DMA2 Channel5 global interrupt global interrupt. */
#define NVIC_IP_INDEX_DMA2_Channel5 ((u8) 60)
/** Interrupt Priority Address for Ethernet global interrupt global interrupt. */
#define NVIC_IP_INDEX_ETH           ((u8) 61)
/** Interrupt Priority Address for Ethernet Wakeup through EXTI line interrupt global interrupt. */
#define NVIC_IP_INDEX_ETH_WKUP      ((u8) 62)
/** Interrupt Priority Address for CAN2 TX interrupts global interrupt. */
#define NVIC_IP_INDEX_CAN2_TX       ((u8) 63)
/** Interrupt Priority Address for CAN2 RX0 interrupts global interrupt. */
#define NVIC_IP_INDEX_CAN2_RX0      ((u8) 64)
/** Interrupt Priority Address for CAN2 RX1 interrupt global interrupt. */
#define NVIC_IP_INDEX_CAN2_RX1      ((u8) 65)
/** Interrupt Priority Address for CAN2 SCE interrupt global interrupt. */
#define NVIC_IP_INDEX_CAN2_SCE      ((u8) 66)
/** Interrupt Priority Address for USB On The Go FS global interrupt global interrupt. */
#define NVIC_IP_INDEX_OTG_FS        ((u8) 67)

#elif defined(STM32F10X_XL) /* XL-density devices */

/* NVIC Enable Register Numbers and Bit Patterns. */
/** Interrupt Enable for Window Watchdog interrupt. */
#define NVIC_ISER0_WWDG            ((u32) 0x00000001)
/** Interrupt Enable for PVD through EXTI Line detection interrupt. */
#define NVIC_ISER0_PVD             ((u32) 0x00000002)
/** Interrupt Enable for Tamper interrupt. */
#define NVIC_ISER0_TAMPER          ((u32) 0x00000004)
/** Interrupt Enable for RTC global interrupt. */
#define NVIC_ISER0_RTC             ((u32) 0x00000008)
/** Interrupt Enable for Flash global interrupt. */
#define NVIC_ISER0_FLASH           ((u32) 0x00000010)
/** Interrupt Enable for RCC global interrupt. */
#define NVIC_ISER0_RCC             ((u32) 0x00000020)
/** Interrupt Enable for EXTI Line0 interrupt. */
#define NVIC_ISER0_EXTI0           ((u32) 0x00000040)
/** Interrupt Enable for EXTI Line1 interrupt. */
#define NVIC_ISER0_EXTI1           ((u32) 0x00000080)
/** Interrupt Enable for EXTI Line2 interrupt. */
#define NVIC_ISER0_EXTI2           ((u32) 0x00000100)
/** Interrupt Enable for EXTI Line3 interrupt. */
#define NVIC_ISER0_EXTI3           ((u32) 0x00000200)
/** Interrupt Enable for EXTI Line4 interrupt. */
#define NVIC_ISER0_EXTI4           ((u32) 0x00000400)
/** Interrupt Enable for DMA Channel1 global interrupt. */
#define NVIC_ISER0_DMA_Channel1    ((u32) 0x00000800)
#define NVIC_ISER0_DMA1_Channel1   ((u32) 0x00000800)
/** Interrupt Enable for DMA Channel2 global interrupt. */
#define NVIC_ISER0_DMA_Channel2    ((u32) 0x00001000)
#define NVIC_ISER0_DMA1_Channel2   ((u32) 0x00001000)
/** Interrupt Enable for DMA Channel3 global interrupt. */
#define NVIC_ISER0_DMA_Channel3    ((u32) 0x00002000)
#define NVIC_ISER0_DMA1_Channel3   ((u32) 0x00002000)
/** Interrupt Enable for DMA Channel4 global interrupt. */
#define NVIC_ISER0_DMA_Channel4    ((u32) 0x00004000)
#define NVIC_ISER0_DMA1_Channel4   ((u32) 0x00004000)
/** Interrupt Enable for DMA Channel5 global interrupt. */
#define NVIC_ISER0_DMA_Channel5    ((u32) 0x00008000)
#define NVIC_ISER0_DMA1_Channel5   ((u32) 0x00008000)
/** Interrupt Enable for DMA Channel6 global interrupt. */
#define NVIC_ISER0_DMA_Channel6    ((u32) 0x00010000)
#define NVIC_ISER0_DMA1_Channel6   ((u32) 0x00010000)
/** Interrupt Enable for DMA Channel7 global interrupt. */
#define NVIC_ISER0_DMA_Channel7    ((u32) 0x00020000)
#define NVIC_ISER0_DMA1_Channel7   ((u32) 0x00020000)
/** Interrupt Enable for ADC1 and ADC2 global interrupt. */
#define NVIC_ISER0_ADC1_2          ((u32) 0x00040000)
/** Interrupt Enable for USB High Priority or CAN TX interrupts. */
#define NVIC_ISER0_USB_HP_CAN_TX   ((u32) 0x00080000)
/** Interrupt Enable for USB Low Priority or CAN RX0 interrupts. */
#define NVIC_ISER0_USB_LP_CAN_RX0  ((u32) 0x00100000)
/** Interrupt Enable for CAN RX1 interrupt. */
#define NVIC_ISER0_CAN_RX1         ((u32) 0x00200000)
/** Interrupt Enable for CAN SCE interrupt. */
#define NVIC_ISER0_CAN_SCE         ((u32) 0x00400000)
/** Interrupt Enable for EXTI Line[9:5] interrupts. */
#define NVIC_ISER0_EXTI9_5         ((u32) 0x00800000)
/** Interrupt Enable for TIM1 Break interrupt and TIM9 global interrupt. */
#define NVIC_ISER0_TIM1_BRK_TIM9   ((u32) 0x01000000)
/** Interrupt Enable for TIM1 Update interrupt and TIM10 global interrupt. */
#define NVIC_ISER0_TIM1_UP_TIM10   ((u32) 0x02000000)
/** Interrupt Enable for TIM1 Trigger and Commutation interrupts and TIM11 global interrupt. */
#define NVIC_ISER0_TIM1_TRG_COM_TIM11 ((u32) 0x04000000)
/** Interrupt Enable for TIM1 Capture Compare interrupt. */
#define NVIC_ISER0_TIM1_CC         ((u32) 0x08000000)
/** Interrupt Enable for TIM2 global interrupt. */
#define NVIC_ISER0_TIM2            ((u32) 0x10000000)
/** Interrupt Enable for TIM3 global interrupt. */
#define NVIC_ISER0_TIM3            ((u32) 0x20000000)
/** Interrupt Enable for TIM4 global interrupt. */
#define NVIC_ISER0_TIM4            ((u32) 0x40000000)
/** Interrupt Enable for I2C1 event interrupt. */
#define NVIC_ISER0_I2C1_EV         ((u32) 0x80000000)
/** Interrupt Enable for I2C1 error interrupt. */
#define NVIC_ISER1_I2C1_ER         ((u32) 0x00000001)
/** Interrupt Enable for I2C2 event interrupt. */
#define NVIC_ISER1_I2C2_EV         ((u32) 0x00000002)
/** Interrupt Enable for I2C2 error interrupt. */
#define NVIC_ISER1_I2C2_ER         ((u32) 0x00000004)
/** Interrupt Enable for SPI1 global interrupt. */
#define NVIC_ISER1_SPI1            ((u32) 0x00000008)
/** Interrupt Enable for SPI2 global interrupt. */
#define NVIC_ISER1_SPI2            ((u32) 0x00000010)
/** Interrupt Enable for USART1 global interrupt. */
#define NVIC_ISER1_USART1          ((u32) 0x00000020)
/** Interrupt Enable for USART2 global interrupt. */
#define NVIC_ISER1_USART2          ((u32) 0x00000040)
/** Interrupt Enable for USART3 global interrupt. */
#define NVIC_ISER1_USART3          ((u32) 0x00000080)
/** Interrupt Enable for EXTI Line[15:10] interrupts. */
#define NVIC_ISER1_EXTI15_10       ((u32) 0x00000100)
/** Interrupt Enable for RTC alarm through EXTI line interrupt. */
#define NVIC_ISER1_RTCAlarm        ((u32) 0x00000200)
/** Interrupt Enable for USB wakeup from suspend through EXTI line interrupt. */
#define NVIC_ISER1_USBWakeup       ((u32) 0x00000400)
/** Interrupt Enable for TIM8 Break interrupt and TIM12 global interrupt. */
#define NVIC_ISER1_TIM8_BRK_TIM12  ((u32) 0x00000800)
/** Interrupt Enable for TIM8 Update interrupt and TIM13 global interrupt. */
#define NVIC_ISER1_TIM8_UP_TIM13   ((u32) 0x00001000)
/** Interrupt Enable for TIM8 Trigger and Commutation interrupts and TIM14 global interrupt. */
#define NVIC_ISER1_TIM8_TRG_COM_TIM14 ((u32) 0x00002000)
/** Interrupt Enable for TIM8 Capture Compare interrupt. */
#define NVIC_ISER1_TIM8_CC         ((u32) 0x00004000)
/** Interrupt Enable for ADC3 global interrupt. */
#define NVIC_ISER1_ADC3            ((u32) 0x00008000)
/** Interrupt Enable for FSMC global interrupt. */
#define NVIC_ISER1_FSMC            ((u32) 0x00010000)
/** Interrupt Enable for SDIO global interrupt. */
#define NVIC_ISER1_SDIO            ((u32) 0x00020000)
/** Interrupt Enable for TIM5 global interrupt. */
#define NVIC_ISER1_TIM5            ((u32) 0x00040000)
/** Interrupt Enable for SPI3 global interrupt. */
#define NVIC_ISER1_SPI3            ((u32) 0x00080000)
/** Interrupt Enable for UART4 global interrupt. */
#define NVIC_ISER1_UART4           ((u32) 0x00100000)
/** Interrupt Enable for UART5 global interrupt. */
#define NVIC_ISER1_UART5           ((u32) 0x00200000)
/** Interrupt Enable for TIM6 global interrupt. */
#define NVIC_ISER1_TIM6            ((u32) 0x00400000)
/** Interrupt Enable for TIM7 global interrupt. */
#define NVIC_ISER1_TIM7            ((u32) 0x00800000)
/** Interrupt Enable for DMA2 Channel1 global interrupt. */
#define NVIC_ISER1_DMA2_Channel1   ((u32) 0x01000000)
/** Interrupt Enable for DMA2 Channel2 global interrupt. */
#define NVIC_ISER1_DMA2_Channel2   ((u32) 0x02000000)
/** Interrupt Enable for DMA2 Channel3 global interrupt. */
#define NVIC_ISER1_DMA2_Channel3   ((u32) 0x04000000)
/** Interrupt Enable for DMA2 Channel4 and DMA2 Channel5 global interrupts. */
#define NVIC_ISER1_DMA2_Channel4_5 ((u32) 0x08000000)

/* Indices into the NVIC->IP array of u8 priorities. */

/** Interrupt Priority Address for Window watchdog interrupt. */
#define NVIC_IP_INDEX_WWDG            ((u8) 0)
/** Interrupt Priority Address for PVD through EXTI Line detection interrupt. */
#define NVIC_IP_INDEX_PVD             ((u8) 1)
/** Interrupt Priority Address for Tamper interrupt. */
#define NVIC_IP_INDEX_TAMPER          ((u8) 2)
/** Interrupt Priority Address for RTC global interrupt. */
#define NVIC_IP_INDEX_RTC             ((u8) 3)
/** Interrupt Priority Address for Flash global interrupt. */
#define NVIC_IP_INDEX_FLASH           ((u8) 4)
/** Interrupt Priority Address for RCC global interrupt. */
#define NVIC_IP_INDEX_RCC             ((u8) 5)
/** Interrupt Priority Address for EXTI Line0 interrupt. */
#define NVIC_IP_INDEX_EXTI0           ((u8) 6)
/** Interrupt Priority Address for EXTI Line1 interrupt. */
#define NVIC_IP_INDEX_EXTI1           ((u8) 7)
/** Interrupt Priority Address for EXTI Line2 interrupt. */
#define NVIC_IP_INDEX_EXTI2           ((u8) 8)
/** Interrupt Priority Address for EXTI Line3 interrupt. */
#define NVIC_IP_INDEX_EXTI3           ((u8) 9)
/** Interrupt Priority Address for EXTI Line4 interrupt. */
#define NVIC_IP_INDEX_EXTI4           ((u8) 10)
/** Interrupt Priority Address for DMA1 Channel1 global interrupt. */
#define NVIC_IP_INDEX_DMA1_Channel1   ((u8) 11)
#define NVIC_IP_INDEX_DMA_Channel1    ((u8) 11)
/** Interrupt Priority Address for DMA1 Channel2 global interrupt. */
#define NVIC_IP_INDEX_DMA1_Channel2   ((u8) 12)
#define NVIC_IP_INDEX_DMA_Channel2    ((u8) 12)
/** Interrupt Priority Address for DMA1 Channel3 global interrupt. */
#define NVIC_IP_INDEX_DMA1_Channel3   ((u8) 13)
#define NVIC_IP_INDEX_DMA_Channel3    ((u8) 13)
/** Interrupt Priority Address for DMA1 Channel4 global interrupt. */
#define NVIC_IP_INDEX_DMA1_Channel4   ((u8) 14)
#define NVIC_IP_INDEX_DMA_Channel4    ((u8) 14)
/** Interrupt Priority Address for DMA1 Channel5 global interrupt. */
#define NVIC_IP_INDEX_DMA1_Channel5   ((u8) 15)
#define NVIC_IP_INDEX_DMA_Channel5    ((u8) 15)
/** Interrupt Priority Address for DMA1 Channel6 global interrupt. */
#define NVIC_IP_INDEX_DMA1_Channel6   ((u8) 16)
#define NVIC_IP_INDEX_DMA_Channel6    ((u8) 16)
/** Interrupt Priority Address for DMA1 Channel7 global interrupt. */
#define NVIC_IP_INDEX_DMA1_Channel7   ((u8) 17)
#define NVIC_IP_INDEX_DMA_Channel7    ((u8) 17)
/** Interrupt Priority Address for ADC1 and ADC2 global interrupt. */
#define NVIC_IP_INDEX_ADC1_2          ((u8) 18)
/** Interrupt Priority Address for USB High Priority or CAN TX interrupts. */
#define NVIC_IP_INDEX_USB_HP_CAN_TX   ((u8) 19)
/** Interrupt Priority Address for USB Low Priority or CAN RX0 interrupts. */
#define NVIC_IP_INDEX_USB_LP_CAN_RX0  ((u8) 20)
/** Interrupt Priority Address for CAN RX1 interrupt. */
#define NVIC_IP_INDEX_CAN_RX1         ((u8) 21)
/** Interrupt Priority Address for CAN SCE interrupt. */
#define NVIC_IP_INDEX_CAN_SCE         ((u8) 22)
/** Interrupt Priority Address for EXTI Line[9:5] interrupts. */
#define NVIC_IP_INDEX_EXTI9_5         ((u8) 23)
/** Interrupt Priority Address for TIM1 Break interrupt and TIM9 global interrupt. */
#define NVIC_IP_INDEX_TIM1_BRK_TIM9   ((u8) 24)
/** Interrupt Priority Address for TIM1 Update interrupt and TIM10 global interrupt. */
#define NVIC_IP_INDEX_TIM1_UP_TIM10   ((u8) 25)
/** Interrupt Priority Address for TIM1 Trigger and Commutation interrupts and TIM11 global interrupt. */
#define NVIC_IP_INDEX_TIM1_TRG_COM_TIM11 ((u8) 26)
/** Interrupt Priority Address for TIM1 Capture Compare interrupt. */
#define NVIC_IP_INDEX_TIM1_CC         ((u8) 27)
/** Interrupt Priority Address for TIM2 global interrupt. */
#define NVIC_IP_INDEX_TIM2            ((u8) 28)
/** Interrupt Priority Address for TIM3 global interrupt. */
#define NVIC_IP_INDEX_TIM3            ((u8) 29)
/** Interrupt Priority Address for TIM4 global interrupt. */
#define NVIC_IP_INDEX_TIM4            ((u8) 30)
/** Interrupt Priority Address for I2C1 event interrupt. */
#define NVIC_IP_INDEX_I2C1_EV         ((u8) 31)
/** Interrupt Priority Address for I2C1 error interrupt. */
#define NVIC_IP_INDEX_I2C1_ER         ((u8) 32)
/** Interrupt Priority Address for I2C2 event interrupt. */
#define NVIC_IP_INDEX_I2C2_EV         ((u8) 33)
/** Interrupt Priority Address for I2C2 error interrupt. */
#define NVIC_IP_INDEX_I2C2_ER         ((u8) 34)
/** Interrupt Priority Address for SPI1 global interrupt. */
#define NVIC_IP_INDEX_SPI1            ((u8) 35)
/** Interrupt Priority Address for SPI2 global interrupt. */
#define NVIC_IP_INDEX_SPI2            ((u8) 36)
/** Interrupt Priority Address for USART1 global interrupt. */
#define NVIC_IP_INDEX_USART1          ((u8) 37)
/** Interrupt Priority Address for USART2 global interrupt. */
#define NVIC_IP_INDEX_USART2          ((u8) 38)
/** Interrupt Priority Address for USART3 global interrupt. */
#define NVIC_IP_INDEX_USART3          ((u8) 39)
/** Interrupt Priority Address for EXTI Line[15:10] interrupts. */
#define NVIC_IP_INDEX_EXTI15_10       ((u8) 40)
/** Interrupt Priority Address for RTC alarm through EXTI line interrupt. */
#define NVIC_IP_INDEX_RTCAlarm        ((u8) 41)
/** Interrupt Priority Address for USB wakeup from suspend through EXTI line interrupt. */
#define NVIC_IP_INDEX_USBWakeup       ((u8) 42)
/** Interrupt Priority Address for TIM8 Break interrupt and TIM12 global interrupt. */
#define NVIC_IP_INDEX_TIM8_BRK_TIM12  ((u8) 43)
/** Interrupt Priority Address for TIM8 Update interrupt and TIM13 global interrupt. */
#define NVIC_IP_INDEX_TIM8_UP_TIM13   ((u8) 44)
/** Interrupt Priority Address for TIM8 Trigger and Commutation interrupts and TIM14 global interrupt. */
#define NVIC_IP_INDEX_TIM8_TRG_COM_TIM14 ((u8) 45)
/** Interrupt Priority Address for TIM8 Capture Compare interrupt. */
#define NVIC_IP_INDEX_TIM8_CC         ((u8) 46)
/** Interrupt Priority Address for ADC3 global interrupt. */
#define NVIC_IP_INDEX_ADC3            ((u8) 47)
/** Interrupt Priority Address for FSMC global interrupt. */
#define NVIC_IP_INDEX_FSMC            ((u8) 48)
/** Interrupt Priority Address for SDIO global interrupt. */
#define NVIC_IP_INDEX_SDIO            ((u8) 49)
/** Interrupt Priority Address for TIM5 global interrupt. */
#define NVIC_IP_INDEX_TIM5            ((u8) 50)
/** Interrupt Priority Address for SPI3 global interrupt. */
#define NVIC_IP_INDEX_SPI3            ((u8) 51)
/** Interrupt Priority Address for UART4 global interrupt. */
#define NVIC_IP_INDEX_UART4           ((u8) 52)
/** Interrupt Priority Address for UART5 global interrupt. */
#define NVIC_IP_INDEX_UART5           ((u8) 53)
/** Interrupt Priority Address for TIM6 global interrupt. */
#define NVIC_IP_INDEX_TIM6            ((u8) 54)
/** Interrupt Priority Address for TIM7 global interrupt. */
#define NVIC_IP_INDEX_TIM7            ((u8) 55)
/** Interrupt Priority Address for DMA2 Channel1 global interrupt. */
#define NVIC_IP_INDEX_DMA2_Channel1   ((u8) 56)
/** Interrupt Priority Address for DMA2 Channel2 global interrupt. */
#define NVIC_IP_INDEX_DMA2_Channel2   ((u8) 57)
/** Interrupt Priority Address for DMA2 Channel3 global interrupt. */
#define NVIC_IP_INDEX_DMA2_Channel3   ((u8) 58)
/** Interrupt Priority Address for DMA2 Channel4 and DMA2 Channel5 global interrupts. */
#define NVIC_IP_INDEX_DMA2_Channel4_5 ((u8) 59)


#else /* Not Connectivity line or XL-density */

/* NVIC Enable Register Numbers and Bit Patterns. */
/** Interrupt Enable for Window Watchdog interrupt. */
#define NVIC_ISER0_WWDG            ((u32) 0x00000001)
/** Interrupt Enable for PVD through EXTI Line detection interrupt. */
#define NVIC_ISER0_PVD             ((u32) 0x00000002)
/** Interrupt Enable for Tamper interrupt. */
#define NVIC_ISER0_TAMPER          ((u32) 0x00000004)
/** Interrupt Enable for RTC global interrupt. */
#define NVIC_ISER0_RTC             ((u32) 0x00000008)
/** Interrupt Enable for Flash global interrupt. */
#define NVIC_ISER0_FLASH           ((u32) 0x00000010)
/** Interrupt Enable for RCC global interrupt. */
#define NVIC_ISER0_RCC             ((u32) 0x00000020)
/** Interrupt Enable for EXTI Line0 interrupt. */
#define NVIC_ISER0_EXTI0           ((u32) 0x00000040)
/** Interrupt Enable for EXTI Line1 interrupt. */
#define NVIC_ISER0_EXTI1           ((u32) 0x00000080)
/** Interrupt Enable for EXTI Line2 interrupt. */
#define NVIC_ISER0_EXTI2           ((u32) 0x00000100)
/** Interrupt Enable for EXTI Line3 interrupt. */
#define NVIC_ISER0_EXTI3           ((u32) 0x00000200)
/** Interrupt Enable for EXTI Line4 interrupt. */
#define NVIC_ISER0_EXTI4           ((u32) 0x00000400)
/** Interrupt Enable for DMA Channel1 global interrupt. */
#define NVIC_ISER0_DMA_Channel1    ((u32) 0x00000800)
#define NVIC_ISER0_DMA1_Channel1   ((u32) 0x00000800)
/** Interrupt Enable for DMA Channel2 global interrupt. */
#define NVIC_ISER0_DMA_Channel2    ((u32) 0x00001000)
#define NVIC_ISER0_DMA1_Channel2   ((u32) 0x00001000)
/** Interrupt Enable for DMA Channel3 global interrupt. */
#define NVIC_ISER0_DMA_Channel3    ((u32) 0x00002000)
#define NVIC_ISER0_DMA1_Channel3   ((u32) 0x00002000)
/** Interrupt Enable for DMA Channel4 global interrupt. */
#define NVIC_ISER0_DMA_Channel4    ((u32) 0x00004000)
#define NVIC_ISER0_DMA1_Channel4   ((u32) 0x00004000)
/** Interrupt Enable for DMA Channel5 global interrupt. */
#define NVIC_ISER0_DMA_Channel5    ((u32) 0x00008000)
#define NVIC_ISER0_DMA1_Channel5   ((u32) 0x00008000)
/** Interrupt Enable for DMA Channel6 global interrupt. */
#define NVIC_ISER0_DMA_Channel6    ((u32) 0x00010000)
#define NVIC_ISER0_DMA1_Channel6   ((u32) 0x00010000)
/** Interrupt Enable for DMA Channel7 global interrupt. */
#define NVIC_ISER0_DMA_Channel7    ((u32) 0x00020000)
#define NVIC_ISER0_DMA1_Channel7   ((u32) 0x00020000)
/** Interrupt Enable for ADC1 and ADC2 global interrupt. */
#define NVIC_ISER0_ADC1_2          ((u32) 0x00040000)
/** Interrupt Enable for USB High Priority or CAN TX interrupts. */
#define NVIC_ISER0_USB_HP_CAN_TX   ((u32) 0x00080000)
/** Interrupt Enable for USB Low Priority or CAN RX0 interrupts. */
#define NVIC_ISER0_USB_LP_CAN_RX0  ((u32) 0x00100000)
/** Interrupt Enable for CAN RX1 interrupt. */
#define NVIC_ISER0_CAN_RX1         ((u32) 0x00200000)
/** Interrupt Enable for CAN SCE interrupt. */
#define NVIC_ISER0_CAN_SCE         ((u32) 0x00400000)
/** Interrupt Enable for EXTI Line[9:5] interrupts. */
#define NVIC_ISER0_EXTI9_5         ((u32) 0x00800000)
/** Interrupt Enable for TIM1 Break interrupt. */
#define NVIC_ISER0_TIM1_BRK        ((u32) 0x01000000)
/** Interrupt Enable for TIM1 Update interrupt. */
#define NVIC_ISER0_TIM1_UP         ((u32) 0x02000000)
/** Interrupt Enable for TIM1 Trigger and Commutation interrupts. */
#define NVIC_ISER0_TIM1_TRG_COM    ((u32) 0x04000000)
/** Interrupt Enable for TIM1 Capture Compare interrupt. */
#define NVIC_ISER0_TIM1_CC         ((u32) 0x08000000)
/** Interrupt Enable for TIM2 global interrupt. */
#define NVIC_ISER0_TIM2            ((u32) 0x10000000)
/** Interrupt Enable for TIM3 global interrupt. */
#define NVIC_ISER0_TIM3            ((u32) 0x20000000)
/** Interrupt Enable for TIM4 global interrupt. */
#define NVIC_ISER0_TIM4            ((u32) 0x40000000)
/** Interrupt Enable for I2C1 event interrupt. */
#define NVIC_ISER0_I2C1_EV         ((u32) 0x80000000)
/** Interrupt Enable for I2C1 error interrupt. */
#define NVIC_ISER1_I2C1_ER         ((u32) 0x00000001)
/** Interrupt Enable for I2C2 event interrupt. */
#define NVIC_ISER1_I2C2_EV         ((u32) 0x00000002)
/** Interrupt Enable for I2C2 error interrupt. */
#define NVIC_ISER1_I2C2_ER         ((u32) 0x00000004)
/** Interrupt Enable for SPI1 global interrupt. */
#define NVIC_ISER1_SPI1            ((u32) 0x00000008)
/** Interrupt Enable for SPI2 global interrupt. */
#define NVIC_ISER1_SPI2            ((u32) 0x00000010)
/** Interrupt Enable for USART1 global interrupt. */
#define NVIC_ISER1_USART1          ((u32) 0x00000020)
/** Interrupt Enable for USART2 global interrupt. */
#define NVIC_ISER1_USART2          ((u32) 0x00000040)
/** Interrupt Enable for USART3 global interrupt. */
#define NVIC_ISER1_USART3          ((u32) 0x00000080)
/** Interrupt Enable for EXTI Line[15:10] interrupts. */
#define NVIC_ISER1_EXTI15_10       ((u32) 0x00000100)
/** Interrupt Enable for RTC alarm through EXTI line interrupt. */
#define NVIC_ISER1_RTCAlarm        ((u32) 0x00000200)
/** Interrupt Enable for USB wakeup from suspend through EXTI line interrupt. */
#define NVIC_ISER1_USBWakeup       ((u32) 0x00000400)
/** Interrupt Enable for TIM8 Break interrupt. */
#define NVIC_ISER1_TIM8_BRK        ((u32) 0x00000800)
/** Interrupt Enable for TIM8 Update interrupt. */
#define NVIC_ISER1_TIM8_UP         ((u32) 0x00001000)
/** Interrupt Enable for TIM8 Trigger and Commutation interrupts. */
#define NVIC_ISER1_TIM8_TRG_COM    ((u32) 0x00002000)
/** Interrupt Enable for TIM8 Capture Compare interrupt. */
#define NVIC_ISER1_TIM8_CC         ((u32) 0x00004000)
/** Interrupt Enable for ADC3 global interrupt. */
#define NVIC_ISER1_ADC3            ((u32) 0x00008000)
/** Interrupt Enable for FSMC global interrupt. */
#define NVIC_ISER1_FSMC            ((u32) 0x00010000)
/** Interrupt Enable for SDIO global interrupt. */
#define NVIC_ISER1_SDIO            ((u32) 0x00020000)
/** Interrupt Enable for TIM5 global interrupt. */
#define NVIC_ISER1_TIM5            ((u32) 0x00040000)
/** Interrupt Enable for SPI3 global interrupt. */
#define NVIC_ISER1_SPI3            ((u32) 0x00080000)
/** Interrupt Enable for UART4 global interrupt. */
#define NVIC_ISER1_UART4           ((u32) 0x00100000)
/** Interrupt Enable for UART5 global interrupt. */
#define NVIC_ISER1_UART5           ((u32) 0x00200000)
/** Interrupt Enable for TIM6 global interrupt. */
#define NVIC_ISER1_TIM6            ((u32) 0x00400000)
/** Interrupt Enable for TIM7 global interrupt. */
#define NVIC_ISER1_TIM7            ((u32) 0x00800000)
/** Interrupt Enable for DMA2 Channel1 global interrupt. */
#define NVIC_ISER1_DMA2_Channel1   ((u32) 0x01000000)
/** Interrupt Enable for DMA2 Channel2 global interrupt. */
#define NVIC_ISER1_DMA2_Channel2   ((u32) 0x02000000)
/** Interrupt Enable for DMA2 Channel3 global interrupt. */
#define NVIC_ISER1_DMA2_Channel3   ((u32) 0x04000000)
/** Interrupt Enable for DMA2 Channel4 and DMA2 Channel5 global interrupts. */
#define NVIC_ISER1_DMA2_Channel4_5 ((u32) 0x08000000)

/* Indices into the NVIC->IP array of u8 priorities. */

/** Interrupt Priority Address for Window watchdog interrupt. */
#define NVIC_IP_INDEX_WWDG            ((u8) 0)
/** Interrupt Priority Address for PVD through EXTI Line detection interrupt. */
#define NVIC_IP_INDEX_PVD             ((u8) 1)
/** Interrupt Priority Address for Tamper interrupt. */
#define NVIC_IP_INDEX_TAMPER          ((u8) 2)
/** Interrupt Priority Address for RTC global interrupt. */
#define NVIC_IP_INDEX_RTC             ((u8) 3)
/** Interrupt Priority Address for Flash global interrupt. */
#define NVIC_IP_INDEX_FLASH           ((u8) 4)
/** Interrupt Priority Address for RCC global interrupt. */
#define NVIC_IP_INDEX_RCC             ((u8) 5)
/** Interrupt Priority Address for EXTI Line0 interrupt. */
#define NVIC_IP_INDEX_EXTI0           ((u8) 6)
/** Interrupt Priority Address for EXTI Line1 interrupt. */
#define NVIC_IP_INDEX_EXTI1           ((u8) 7)
/** Interrupt Priority Address for EXTI Line2 interrupt. */
#define NVIC_IP_INDEX_EXTI2           ((u8) 8)
/** Interrupt Priority Address for EXTI Line3 interrupt. */
#define NVIC_IP_INDEX_EXTI3           ((u8) 9)
/** Interrupt Priority Address for EXTI Line4 interrupt. */
#define NVIC_IP_INDEX_EXTI4           ((u8) 10)
/** Interrupt Priority Address for DMA1 Channel1 global interrupt. */
#define NVIC_IP_INDEX_DMA1_Channel1   ((u8) 11)
#define NVIC_IP_INDEX_DMA_Channel1    ((u8) 11)
/** Interrupt Priority Address for DMA1 Channel2 global interrupt. */
#define NVIC_IP_INDEX_DMA1_Channel2   ((u8) 12)
#define NVIC_IP_INDEX_DMA_Channel2    ((u8) 12)
/** Interrupt Priority Address for DMA1 Channel3 global interrupt. */
#define NVIC_IP_INDEX_DMA1_Channel3   ((u8) 13)
#define NVIC_IP_INDEX_DMA_Channel3    ((u8) 13)
/** Interrupt Priority Address for DMA1 Channel4 global interrupt. */
#define NVIC_IP_INDEX_DMA1_Channel4   ((u8) 14)
#define NVIC_IP_INDEX_DMA_Channel4    ((u8) 14)
/** Interrupt Priority Address for DMA1 Channel5 global interrupt. */
#define NVIC_IP_INDEX_DMA1_Channel5   ((u8) 15)
#define NVIC_IP_INDEX_DMA_Channel5    ((u8) 15)
/** Interrupt Priority Address for DMA1 Channel6 global interrupt. */
#define NVIC_IP_INDEX_DMA1_Channel6   ((u8) 16)
#define NVIC_IP_INDEX_DMA_Channel6    ((u8) 16)
/** Interrupt Priority Address for DMA1 Channel7 global interrupt. */
#define NVIC_IP_INDEX_DMA1_Channel7   ((u8) 17)
#define NVIC_IP_INDEX_DMA_Channel7    ((u8) 17)
/** Interrupt Priority Address for ADC1 and ADC2 global interrupt. */
#define NVIC_IP_INDEX_ADC1_2          ((u8) 18)
/** Interrupt Priority Address for USB High Priority or CAN TX interrupts. */
#define NVIC_IP_INDEX_USB_HP_CAN_TX   ((u8) 19)
/** Interrupt Priority Address for USB Low Priority or CAN RX0 interrupts. */
#define NVIC_IP_INDEX_USB_LP_CAN_RX0  ((u8) 20)
/** Interrupt Priority Address for CAN RX1 interrupt. */
#define NVIC_IP_INDEX_CAN_RX1         ((u8) 21)
/** Interrupt Priority Address for CAN SCE interrupt. */
#define NVIC_IP_INDEX_CAN_SCE         ((u8) 22)
/** Interrupt Priority Address for EXTI Line[9:5] interrupts. */
#define NVIC_IP_INDEX_EXTI9_5         ((u8) 23)
/** Interrupt Priority Address for TIM1 Break interrupt. */
#define NVIC_IP_INDEX_TIM1_BRK        ((u8) 24)
/** Interrupt Priority Address for TIM1 Update interrupt. */
#define NVIC_IP_INDEX_TIM1_UP         ((u8) 25)
/** Interrupt Priority Address for TIM1 Trigger and Commutation interrupts. */
#define NVIC_IP_INDEX_TIM1_TRG_COM    ((u8) 26)
/** Interrupt Priority Address for TIM1 Capture Compare interrupt. */
#define NVIC_IP_INDEX_TIM1_CC         ((u8) 27)
/** Interrupt Priority Address for TIM2 global interrupt. */
#define NVIC_IP_INDEX_TIM2            ((u8) 28)
/** Interrupt Priority Address for TIM3 global interrupt. */
#define NVIC_IP_INDEX_TIM3            ((u8) 29)
/** Interrupt Priority Address for TIM4 global interrupt. */
#define NVIC_IP_INDEX_TIM4            ((u8) 30)
/** Interrupt Priority Address for I2C1 event interrupt. */
#define NVIC_IP_INDEX_I2C1_EV         ((u8) 31)
/** Interrupt Priority Address for I2C1 error interrupt. */
#define NVIC_IP_INDEX_I2C1_ER         ((u8) 32)
/** Interrupt Priority Address for I2C2 event interrupt. */
#define NVIC_IP_INDEX_I2C2_EV         ((u8) 33)
/** Interrupt Priority Address for I2C2 error interrupt. */
#define NVIC_IP_INDEX_I2C2_ER         ((u8) 34)
/** Interrupt Priority Address for SPI1 global interrupt. */
#define NVIC_IP_INDEX_SPI1            ((u8) 35)
/** Interrupt Priority Address for SPI2 global interrupt. */
#define NVIC_IP_INDEX_SPI2            ((u8) 36)
/** Interrupt Priority Address for USART1 global interrupt. */
#define NVIC_IP_INDEX_USART1          ((u8) 37)
/** Interrupt Priority Address for USART2 global interrupt. */
#define NVIC_IP_INDEX_USART2          ((u8) 38)
/** Interrupt Priority Address for USART3 global interrupt. */
#define NVIC_IP_INDEX_USART3          ((u8) 39)
/** Interrupt Priority Address for EXTI Line[15:10] interrupts. */
#define NVIC_IP_INDEX_EXTI15_10       ((u8) 40)
/** Interrupt Priority Address for RTC alarm through EXTI line interrupt. */
#define NVIC_IP_INDEX_RTCAlarm        ((u8) 41)
/** Interrupt Priority Address for USB wakeup from suspend through EXTI line interrupt. */
#define NVIC_IP_INDEX_USBWakeup       ((u8) 42)
/** Interrupt Priority Address for TIM8 Break interrupt. */
#define NVIC_IP_INDEX_TIM8_BRK        ((u8) 43)
/** Interrupt Priority Address for TIM8 Update interrupt. */
#define NVIC_IP_INDEX_TIM8_UP         ((u8) 44)
/** Interrupt Priority Address for TIM8 Trigger and Commutation interrupts. */
#define NVIC_IP_INDEX_TIM8_TRG_COM    ((u8) 45)
/** Interrupt Priority Address for TIM8 Capture Compare interrupt. */
#define NVIC_IP_INDEX_TIM8_CC         ((u8) 46)
/** Interrupt Priority Address for ADC3 global interrupt. */
#define NVIC_IP_INDEX_ADC3            ((u8) 47)
/** Interrupt Priority Address for FSMC global interrupt. */
#define NVIC_IP_INDEX_FSMC            ((u8) 48)
/** Interrupt Priority Address for SDIO global interrupt. */
#define NVIC_IP_INDEX_SDIO            ((u8) 49)
/** Interrupt Priority Address for TIM5 global interrupt. */
#define NVIC_IP_INDEX_TIM5            ((u8) 50)
/** Interrupt Priority Address for SPI3 global interrupt. */
#define NVIC_IP_INDEX_SPI3            ((u8) 51)
/** Interrupt Priority Address for UART4 global interrupt. */
#define NVIC_IP_INDEX_UART4           ((u8) 52)
/** Interrupt Priority Address for UART5 global interrupt. */
#define NVIC_IP_INDEX_UART5           ((u8) 53)
/** Interrupt Priority Address for TIM6 global interrupt. */
#define NVIC_IP_INDEX_TIM6            ((u8) 54)
/** Interrupt Priority Address for TIM7 global interrupt. */
#define NVIC_IP_INDEX_TIM7            ((u8) 55)
/** Interrupt Priority Address for DMA2 Channel1 global interrupt. */
#define NVIC_IP_INDEX_DMA2_Channel1   ((u8) 56)
/** Interrupt Priority Address for DMA2 Channel2 global interrupt. */
#define NVIC_IP_INDEX_DMA2_Channel2   ((u8) 57)
/** Interrupt Priority Address for DMA2 Channel3 global interrupt. */
#define NVIC_IP_INDEX_DMA2_Channel3   ((u8) 58)
/** Interrupt Priority Address for DMA2 Channel4 and DMA2 Channel5 global interrupts. */
#define NVIC_IP_INDEX_DMA2_Channel4_5 ((u8) 59)

#endif

/* --------------------------------------------------------------- */
/* DMA */


#define DMA_CCR1_PL_Low       (u32) 0x00000000
#define DMA_CCR1_PL_Medium    DMA_CCR1_PL_0
#define DMA_CCR1_PL_High      DMA_CCR1_PL_1
#define DMA_CCR1_PL_VeryHigh  (DMA_CCR1_PL_1 | DMA_CCR1_PL_0)

#define DMA_CCR1_MSIZE_8bits  (u32) 0x00000000
#define DMA_CCR1_MSIZE_16bits DMA_CCR1_MSIZE_0
#define DMA_CCR1_MSIZE_32bits DMA_CCR1_MSIZE_1

#define DMA_CCR1_PSIZE_8bits  (u32) 0x00000000
#define DMA_CCR1_PSIZE_16bits DMA_CCR1_PSIZE_0
#define DMA_CCR1_PSIZE_32bits DMA_CCR1_PSIZE_1

#define DMA_CCR2_PL_Low       (u32) 0x00000000
#define DMA_CCR2_PL_Medium    DMA_CCR2_PL_0
#define DMA_CCR2_PL_High      DMA_CCR2_PL_1
#define DMA_CCR2_PL_VeryHigh  (DMA_CCR2_PL_1 | DMA_CCR2_PL_0)

#define DMA_CCR2_MSIZE_8bits  (u32) 0x00000000
#define DMA_CCR2_MSIZE_16bits DMA_CCR2_MSIZE_0
#define DMA_CCR2_MSIZE_32bits DMA_CCR2_MSIZE_1

#define DMA_CCR2_PSIZE_8bits  (u32) 0x00000000
#define DMA_CCR2_PSIZE_16bits DMA_CCR2_PSIZE_0
#define DMA_CCR2_PSIZE_32bits DMA_CCR2_PSIZE_1

#define DMA_CCR3_PL_Low       (u32) 0x00000000
#define DMA_CCR3_PL_Medium    DMA_CCR3_PL_0
#define DMA_CCR3_PL_High      DMA_CCR3_PL_1
#define DMA_CCR3_PL_VeryHigh  (DMA_CCR3_PL_1 | DMA_CCR3_PL_0)

#define DMA_CCR3_MSIZE_8bits  (u32) 0x00000000
#define DMA_CCR3_MSIZE_16bits DMA_CCR3_MSIZE_0
#define DMA_CCR3_MSIZE_32bits DMA_CCR3_MSIZE_1

#define DMA_CCR3_PSIZE_8bits  (u32) 0x00000000
#define DMA_CCR3_PSIZE_16bits DMA_CCR3_PSIZE_0
#define DMA_CCR3_PSIZE_32bits DMA_CCR3_PSIZE_1

#define DMA_CCR4_PL_Low       (u32) 0x00000000
#define DMA_CCR4_PL_Medium    DMA_CCR4_PL_0
#define DMA_CCR4_PL_High      DMA_CCR4_PL_1
#define DMA_CCR4_PL_VeryHigh  (DMA_CCR4_PL_1 | DMA_CCR4_PL_0)

#define DMA_CCR4_MSIZE_8bits  (u32) 0x00000000
#define DMA_CCR4_MSIZE_16bits DMA_CCR4_MSIZE_0
#define DMA_CCR4_MSIZE_32bits DMA_CCR4_MSIZE_1

#define DMA_CCR4_PSIZE_8bits  (u32) 0x00000000
#define DMA_CCR4_PSIZE_16bits DMA_CCR4_PSIZE_0
#define DMA_CCR4_PSIZE_32bits DMA_CCR4_PSIZE_1

#define DMA_CCR5_PL_Low       (u32) 0x00000000
#define DMA_CCR5_PL_Medium    DMA_CCR5_PL_0
#define DMA_CCR5_PL_High      DMA_CCR5_PL_1
#define DMA_CCR5_PL_VeryHigh  (DMA_CCR5_PL_1 | DMA_CCR5_PL_0)

#define DMA_CCR5_MSIZE_8bits  (u32) 0x00000000
#define DMA_CCR5_MSIZE_16bits DMA_CCR5_MSIZE_0
#define DMA_CCR5_MSIZE_32bits DMA_CCR5_MSIZE_1

#define DMA_CCR5_PSIZE_8bits  (u32) 0x00000000
#define DMA_CCR5_PSIZE_16bits DMA_CCR5_PSIZE_0
#define DMA_CCR5_PSIZE_32bits DMA_CCR5_PSIZE_1

#define DMA_CCR6_PL_Low       (u32) 0x00000000
#define DMA_CCR6_PL_Medium    DMA_CCR6_PL_0
#define DMA_CCR6_PL_High      DMA_CCR6_PL_1
#define DMA_CCR6_PL_VeryHigh  (DMA_CCR6_PL_1 | DMA_CCR6_PL_0)

#define DMA_CCR6_MSIZE_8bits  (u32) 0x00000000
#define DMA_CCR6_MSIZE_16bits DMA_CCR6_MSIZE_0
#define DMA_CCR6_MSIZE_32bits DMA_CCR6_MSIZE_1

#define DMA_CCR6_PSIZE_8bits  (u32) 0x00000000
#define DMA_CCR6_PSIZE_16bits DMA_CCR6_PSIZE_0
#define DMA_CCR6_PSIZE_32bits DMA_CCR6_PSIZE_1

#define DMA_CCR7_PL_Low       (u32) 0x00000000
#define DMA_CCR7_PL_Medium    DMA_CCR7_PL_0
#define DMA_CCR7_PL_High      DMA_CCR7_PL_1
#define DMA_CCR7_PL_VeryHigh  (DMA_CCR7_PL_1 | DMA_CCR7_PL_0)

#define DMA_CCR7_MSIZE_8bits  (u32) 0x00000000
#define DMA_CCR7_MSIZE_16bits DMA_CCR7_MSIZE_0
#define DMA_CCR7_MSIZE_32bits DMA_CCR7_MSIZE_1

#define DMA_CCR7_PSIZE_8bits  (u32) 0x00000000
#define DMA_CCR7_PSIZE_16bits DMA_CCR7_PSIZE_0
#define DMA_CCR7_PSIZE_32bits DMA_CCR7_PSIZE_1

/* --------------------------------------------------------------- */
/* Timers. (Timer 1 has some bits unique to it) */

/* TIMx_CR1: Control register 1 */

#define TIM_CR1_CKD_Div1  (u16) 0x0000
#define TIM_CR1_CKD_Div2  TIM_CR1_CKD_0
#define TIM_CR1_CKD_Div4  TIM_CR1_CKD_1

#define TIM_CR2_MMS_Reset       (u16) 0
#define TIM_CR2_MMS_Enable      TIM_CR2_MMS_0
#define TIM_CR2_MMS_Update      TIM_CR2_MMS_1
#define TIM_CR2_MMS_CmpPulse    (TIM_CR2_MMS_1 | TIM_CR2_MMS_0)
#define TIM_CR2_MMS_CmpOC1REF   TIM_CR2_MMS_2
#define TIM_CR2_MMS_CmpOC2REF   (TIM_CR2_MMS_2 | TIM_CR2_MMS_0)
#define TIM_CR2_MMS_CmpOC3REF   (TIM_CR2_MMS_2 | TIM_CR2_MMS_1)
#define TIM_CR2_MMS_CmpOC4REF   (TIM_CR2_MMS_2 | TIM_CR2_MMS_1 | TIM_CR2_MMS_0)

/* OCxM: output compare mode */
#define TIM_CCMR1_OC1M_Frozen   (u16) 0x0000
#define TIM_CCMR1_OC1M_ActiveOnMatch   (TIM_CCMR1_OC1M_0)
#define TIM_CCMR1_OC1M_InactiveOnMatch (TIM_CCMR1_OC1M_1)
#define TIM_CCMR1_OC1M_ToggleOnMatch   (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0)
#define TIM_CCMR1_OC1M_ForceInactive   (TIM_CCMR1_OC1M_2)
#define TIM_CCMR1_OC1M_ForceActive     (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_0)
#define TIM_CCMR1_OC1M_PWM1            (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1)
#define TIM_CCMR1_OC1M_PWM2            (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0)

#define TIM_CCMR1_OC2M_Frozen          ((u16) 0x0000)
#define TIM_CCMR1_OC2M_ActiveOnMatch   (TIM_CCMR1_OC2M_0)
#define TIM_CCMR1_OC2M_InactiveOnMatch (TIM_CCMR1_OC2M_1)
#define TIM_CCMR1_OC2M_ToggleOnMatch   (TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_0)
#define TIM_CCMR1_OC2M_ForceInactive   (TIM_CCMR1_OC2M_2)
#define TIM_CCMR1_OC2M_ForceActive     (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_0)
#define TIM_CCMR1_OC2M_PWM1            (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1)
#define TIM_CCMR1_OC2M_PWM2            (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_0)

/* CCxS: capture/compare selection */
#define TIM_CCMR1_CC2S_Output   (u16) 0x0000
#define TIM_CCMR1_CC2S_InputTI2 TIM_CCMR1_CC2S_0
#define TIM_CCMR1_CC2S_InputTI1 TIM_CCMR1_CC2S_1
#define TIM_CCMR1_CC2S_InputTRC (TIM_CCMR1_CC2S_1 | TIM_CCMR1_CC2S_0)

#define TIM_CCMR1_CC1S_Output   (u16) 0x0000
#define TIM_CCMR1_CC1S_InputTI1 TIM_CCMR1_CC1S_0
#define TIM_CCMR1_CC1S_InputTI2 TIM_CCMR1_CC1S_1
#define TIM_CCMR1_CC1S_InputTRC (TIM_CCMR1_CC1S_1 | TIM_CCMR1_CC1S_0)


#define TIM_CCMR2_OC3M_Frozen          ((u16) 0x0000)
#define TIM_CCMR2_OC3M_ActiveOnMatch   (TIM_CCMR2_OC3M_0)
#define TIM_CCMR2_OC3M_InactiveOnMatch (TIM_CCMR2_OC3M_1)
#define TIM_CCMR2_OC3M_ToggleOnMatch   (TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_0)
#define TIM_CCMR2_OC3M_ForceInactive   (TIM_CCMR2_OC3M_2)
#define TIM_CCMR2_OC3M_ForceActive     (TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_0)
#define TIM_CCMR2_OC3M_PWM1            (TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1)
#define TIM_CCMR2_OC3M_PWM2            (TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_0)

#define TIM_CCMR2_OC4M_Frozen   (u16) 0x0000
#define TIM_CCMR2_OC4M_ActiveOnMatch   (TIM_CCMR2_OC4M_0)
#define TIM_CCMR2_OC4M_InactiveOnMatch (TIM_CCMR2_OC4M_1)
#define TIM_CCMR2_OC4M_ToggleOnMatch   (TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_0)
#define TIM_CCMR2_OC4M_ForceInactive   (TIM_CCMR2_OC4M_2)
#define TIM_CCMR2_OC4M_ForceActive     (TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_0)
#define TIM_CCMR2_OC4M_PWM1            (TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1)
#define TIM_CCMR2_OC4M_PWM2            (TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_0)

#define TIM_CCMR2_CC3S_Output   (u16) 0x0000
#define TIM_CCMR2_CC3S_InputTI3 TIM_CCMR2_CC3S_0
#define TIM_CCMR2_CC3S_InputTI4 TIM_CCMR2_CC3S_1
#define TIM_CCMR2_CC3S_InputTRC (TIM_CCMR2_CC3S_1 | TIM_CCMR2_CC3S_0)

#define TIM_CCMR2_CC4S_Output   (u16) 0x0000
#define TIM_CCMR2_CC4S_InputTI4 TIM_CCMR2_CC4S_0
#define TIM_CCMR2_CC4S_InputTI3 TIM_CCMR2_CC4S_1
#define TIM_CCMR2_CC4S_InputTRC (TIM_CCMR2_CC4S_1 | TIM_CCMR2_CC4S_0)


#define ADC_CR1_DISCNUM0(u3Data) (u32) ((u32) 0x0000E000 & (((u32) (u5Data)) << 13))


/* ADC 1&2 regular external triggers */
#define ADC_CR2_EXTSEL_T1CC1        (u32) 0
#define ADC_CR2_EXTSEL_T1CC2        ADC_CR2_EXTSEL_0
#define ADC_CR2_EXTSEL_T1CC3        ADC_CR2_EXTSEL_1
#define ADC_CR2_EXTSEL_T2CC2        (ADC_CR2_EXTSEL_1 | ADC_CR2_EXTSEL_0)
#define ADC_CR2_EXTSEL_T3TRGO       ADC_CR2_EXTSEL_2
#define ADC_CR2_EXTSEL_T4CC4        (ADC_CR2_EXTSEL_2 | ADC_CR2_EXTSEL_0)
#define ADC_CR2_EXTSEL_EXTI11_T8TRGO   (ADC_CR2_EXTSEL_2 | ADC_CR2_EXTSEL_1)
#define ADC_CR2_EXTSEL_SWSTART      (ADC_CR2_EXTSEL_2 | ADC_CR2_EXTSEL_1 | ADC_CR2_EXTSEL_0)

/* ADC 1&2 injected external triggers */
#define ADC_CR2_JEXTSEL_T1TRGO      (u32) 0
#define ADC_CR2_JEXTSEL_T1CC4       ADC_CR2_JEXTSEL_0
#define ADC_CR2_JEXTSEL_T2TRGO      ADC_CR2_JEXTSEL_1
#define ADC_CR2_JEXTSEL_T2CC1       (ADC_CR2_JEXTSEL_1 | ADC_CR2_JEXTSEL_0)
#define ADC_CR2_JEXTSEL_T3CC4       ADC_CR2_JEXTSEL_2
#define ADC_CR2_JEXTSEL_T4TRGO      (ADC_CR2_JEXTSEL_2 | ADC_CR2_JEXTSEL_0)
#define ADC_CR2_JEXTSEL_EXTI15_T8CC4   (ADC_CR2_JEXTSEL_2 | ADC_CR2_JEXTSEL_1)
#define ADC_CR2_JEXTSEL_JSWSTART    (ADC_CR2_JEXTSEL_2 | ADC_CR2_JEXTSEL_1 | ADC_CR2_JEXTSEL_0)


#define SysTick_CTRL_CLK_AHB     SysTick_CTRL_CLKSOURCE
#define SysTick_CTRL_CLK_AHBDIV8 (u32) 0x00000000

/* Application Interrupt and Reset Control Register; SCB->AIRC; p165 */
#define SCB_AIRCR_VECTKEY_WRITE  (u32) 0x05FA0000

/* SPI Registers */
#define SPI_CR1_BIDIR_ONELINE (u16) 0x8000
#define SPI_CR1_BIDIR_OE      (u16) 0x4000
#define SPI_CR1_CRC_CRCNEXT   (u16) 0x1000
#define SPI_CR1_CRC_DATANEXT  (u16) 0x0000
#define SPI_CR1_DFF_8BIT      (u16) 0x0000
#define SPI_CR1_DFF_16BIT     (u16) 0x0800
#define SPI_CR1_BR_DIV2       (u16) 0x0000
#define SPI_CR1_BR_DIV4       (u16) 0x0008
#define SPI_CR1_BR_DIV8       (u16) 0x0010
#define SPI_CR1_BR_DIV16      (u16) 0x0018
#define SPI_CR1_BR_DIV32      (u16) 0x0020
#define SPI_CR1_BR_DIV64      (u16) 0x0028
#define SPI_CR1_BR_DIV128     (u16) 0x0030
#define SPI_CR1_BR_DIV256     (u16) 0x0038
#define SPI_CR1_MASTER        (u16) 0x0004
#define SPI_CR1_SLAVE         (u16) 0x0000
#define SPI_CR1_MODE_MASK     (u16) 0x0003
#define SPI_CR1_CPOL_HIGH     (u16) 0x0002
#define SPI_CR1_CPHA_HIGH     (u16) 0x0001



/** Flash Key Register (FLASH_KEYR) Unlock Key 1 */
#define FLASH_KEYR_KEY1    ((u32)0x45670123)
/** Flash Key Register (FLASH_KEYR) Unlock Key 2 */
#define FLASH_KEYR_KEY2    ((u32)0xCDEF89AB)
/** Flash read protection disable */
#define OB_RDP_DISABLE     ((u8) 0xA5)
/** Flash read protection enable */
#define OB_RDB_ENABLE      ((u8) 0x00)

/** Slave mode disabled - if CEN = ‘1’ then the prescaler is clocked directly by the internal clock. */
#define TIM_SMCR_SMS_NOSLAVE  ((u16) 0)
/** Encoder mode 1 - Counter counts up/down on TI2FP2 edge depending on TI1FP1 level. */
#define TIM_SMCR_SMS_ENCODER1 ((u16) TIM_SMCR_SMS_0)
/** Encoder mode 2 - Counter counts up/down on TI1FP1 edge depending on TI2FP2 level. */
#define TIM_SMCR_SMS_ENCODER2 ((u16) TIM_SMCR_SMS_1) 
/** Encoder mode 3 - Counter counts up/down on both TI1FP1 and TI2FP2 edges depending on the level of the other input. */
#define TIM_SMCR_SMS_ENCODER3 ((u16) TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1)
/** Reset Mode - Rising edge of the selected trigger input (TRGI) reinitializes the counter and generates an update of the registers. */
#define TIM_SMCR_SMS_RESET    ((u16) TIM_SMCR_SMS_2)
/** Gated Mode - The counter clock is enabled when the trigger input (TRGI) is high. The counter stops (but is not reset) as soon as the trigger becomes low. Both start and stop of the counter are controlled. */
#define TIM_SMCR_SMS_GATED    ((u16) TIM_SMCR_SMS_2 | TIM_SMCR_SMS_0)
/** Trigger Mode - The counter starts at a rising edge of the trigger TRGI (but it is not reset). Only the start of the counter is controlled. */
#define TIM_SMCR_SMS_TRIGGER  ((u16) TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1)
/** External Clock Mode 1 - Rising edges of the selected trigger (TRGI) clock the counter. */
#define TIM_SMCR_SMS_EXTERNAL ((u16) TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0)

#define AFIO_EXTICR_INDEX_EXTICR1 ((u8) 0)
#define AFIO_EXTICR_INDEX_EXTICR2 ((u8) 1)
#define AFIO_EXTICR_INDEX_EXTICR3 ((u8) 2)
#define AFIO_EXTICR_INDEX_EXTICR4 ((u8) 3)

/**
 * @{
 * Clearer naming for CAN Remap.
 */
#define AFIO_MAPR_CAN_REMAP_PA11_PA12 AFIO_MAPR_CAN_REMAP_REMAP1
#define AFIO_MAPR_CAN_REMAP_PB8_PB9   AFIO_MAPR_CAN_REMAP_REMAP2
#define AFIO_MAPR_CAN_REMAP_PD0_PD1   AFIO_MAPR_CAN_REMAP_REMAP3
/** @} */

#define CAN_ESR_LEC_NoError         ((u32) 0)
#define CAN_ESR_LEC_StuffErr        CAN_ESR_LEC_0
#define CAN_ESR_LEC_FormErr         CAN_ESR_LEC_1
#define CAN_ESR_LEC_AckErr          (CAN_ESR_LEC_1 | CAN_ESR_LEC_0)
#define CAN_ESR_LEC_BitRecessiveErr CAN_ESR_LEC_2
#define CAN_ESR_LEC_BitDominantErr  (CAN_ESR_LEC_2 | CAN_ESR_LEC_0)
#define CAN_ESR_LEC_CrcErr          (CAN_ESR_LEC_2 | CAN_ESR_LEC_1)

/* == types ====================================================== */
/* == global constants (extern) ================================== */
/* == global variables (extern) ================================== */
/* == access function prototypes ================================= */
/* == public function prototypes ================================= */
/* =============================================================== */
/* == End of $Workfile::   STM32Defs.h                        $ == */
/* =============================================================== */
/* --------------------------------------------------------------- */

#endif
