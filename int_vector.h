/*----------------------------------------------------------------------------
 * Copyright (c) 2015 Mega Electronics Ltd. All rights reserved.                
 *---------------------------------------------------------------------------*/
#if !defined(__INT_VECTOR_H__)
#define __INT_VECTOR_H__

#include <stdint.h>

/* 
 * Utility macros for producing IAR ISR code which can be compiled for
 * devices using interrupt vectors from RAM and flash. 
 * Just define the INT_VECTORS_IN_RAM in project file etc. 
 */
#if (0 == INT_VECTORS_IN_RAM) 
    #define VECTPRAGMA(X)                  _Pragma(#X)
    #define SET_INTERRUPT_VECTOR(_vect)     VECTPRAGMA(vector=_vect)
    #define SET_RAM_ISR                     (void)
    #define DECLARE_RAM_INT_VECTOR()
#else
    #define SET_INTERRUPT_VECTOR(_vect)

/* Get the start address for interrupt vectors in RAM. */
    #define INT_VECTOR_START_ADDRESS                                           \
        ((HIGHEST_RAM_ADDRESS + 1u) - sizeof(int_vector_t))

    #define SET_RAM_ISR(_vect, _isrptr)                                        \
        do {                                                                   \
            extern isr_type_t  __isr_vector[64] @ INT_VECTOR_START_ADDRESS;    \
            uint32_t _tmp = (uint32_t)(_isrptr);                               \
            __isr_vector[((_vect) >> 1)] = (isr_type_t)(_tmp);                 \
        } while (0)

    #define DECLARE_RAM_INT_VECTOR()                                           \
        __no_init isr_type_t  __isr_vector[64] @ INT_VECTOR_START_ADDRESS;                


#endif


#if defined(__MSP430F5528)
/*******************************************************************************
 * MSP430F5528 specific definitions
 ******************************************************************************/

typedef unsigned int isr_type_t;

#define HIGHEST_RAM_ADDRESS			0x43FFu

typedef struct 
{
    isr_type_t unused[41];
    isr_type_t rtc;          /* 0xFFD2 RTC */
    isr_type_t port2;        /* 0xFFD4 Port 2 */
    isr_type_t timer2_a1;    /* 0xFFD6 Timer2_A5 CC1-4, TA */
    isr_type_t timer2_a0;    /* 0xFFD8 Timer2_A5 CC0 */
    isr_type_t usci_b1;      /* 0xFFDA USCI B1 Receive/Transmit */
    isr_type_t usci_a1;      /* 0xFFDC USCI A1 Receive/Transmit */
    isr_type_t port1;        /* 0xFFDE Port 1 */
    isr_type_t timer1_a1;    /* 0xFFE0 Timer1_A3 CC1-2, TA1 */
    isr_type_t timer1_a0;    /* 0xFFE2 Timer1_A3 CC0 */
    isr_type_t dma;          /* 0xFFE4 DMA */
    isr_type_t usb_ubm;      /* 0xFFE6 USB Timer / cable event / USB reset */
    isr_type_t timer0_a1;    /* 0xFFE8 Timer0_A5 CC1-4, TA */
    isr_type_t timer0_a0;    /* 0xFFEA Timer0_A5 CC0 */
    isr_type_t adc12;        /* 0xFFEC ADC */
    isr_type_t usci_b0;      /* 0xFFEE USCI B0 Receive/Transmit */
    isr_type_t usci_a0;      /* 0xFFF0 USCI A0 Receive/Transmit */
    isr_type_t wdt;          /* 0xFFF2 Watchdog Timer */
    isr_type_t timer0_b1;    /* 0xFFF4 Timer0_B7 CC1-6, TB */
    isr_type_t timer0_b0;    /* 0xFFF6 Timer0_B7 CC0 */
    isr_type_t comp_b;       /* 0xFFF8 Comparator B */
    isr_type_t unmi;         /* 0xFFFA User Non-maskable */
    isr_type_t sysnmi;       /* 0xFFFC System Non-maskable */
    isr_type_t reset;        /* 0xFFFE Reset [Highest Priority] */
} msp430f5528_int_vector_t;

static_assert(sizeof(msp430f5528_int_vector_t) == 128, 
              "Invalid MSP430F5528 Interrupt vector size.");


typedef msp430f5528_int_vector_t int_vector_t;

#elif defined(__MSP430F5659)
/*******************************************************************************
 * MSP430F5659 specific definitions
 ******************************************************************************/
typedef uint16_t isr_type_t;

#define HIGHEST_RAM_ADDRESS			(isr_type_t)0x63FF 

typedef struct 
{
    isr_type_t reserved[36];
    isr_type_t usci_b2;      /* 0xFFC6 USCI B2 Receive/Transmit */
    isr_type_t usci_a2;      /* 0xFFC8 USCI A2 Receive/Transmit */
    isr_type_t port4;        /* 0xFFCA Port 4 */
    isr_type_t port3;        /* 0xFFCC Port 3 */
    isr_type_t timer2_a1;    /* 0xFFCE Timer2_A5 CC1-4, TA */
    isr_type_t timer2_a0;    /* 0xFFD0 Timer2_A5 CC0 */
    isr_type_t dac12;        /* 0xFFD3 DAC12 */
    isr_type_t rtc;          /* 0xFFD4 RTC */
    isr_type_t port2;        /* 0xFFD8 Port 2 */
    isr_type_t usci_b1;      /* 0xFFDA USCI B1 Receive/Transmit */
    isr_type_t usci_a1;      /* 0xFFDC USCI A1 Receive/Transmit */
    isr_type_t port1;        /* 0xFFDE Port 1 */
    isr_type_t timer1_a1;    /* 0xFFE0 Timer1_A3 CC1-2, TA1 */
    isr_type_t timer1_a0;    /* 0xFFE2 Timer1_A3 CC0 */
    isr_type_t dma;          /* 0xFFE4 DMA */
    isr_type_t usb_ubm;      /* 0xFFE6 USB Timer / cable event / USB reset */
    isr_type_t timer0_a1;    /* 0xFFE8 Timer0_A5 CC1-4, TA */
    isr_type_t timer0_a0;    /* 0xFFEA Timer0_A5 CC0 */
    isr_type_t adc12;        /* 0xFFEC ADC */
    isr_type_t usci_b0;      /* 0xFFEE USCI B0 Receive/Transmit */
    isr_type_t usci_a0;      /* 0xFFF0 USCI A0 Receive/Transmit */
    isr_type_t wdt;          /* 0xFFF2 Watchdog Timer */
    isr_type_t timer0_b1;    /* 0xFFF4 Timer0_B7 CC1-6, TB */
    isr_type_t timer0_b0;    /* 0xFFF6 Timer0_B7 CC0 */
    isr_type_t comp_b;       /* 0xFFF8 Comparator B */
    isr_type_t unmi;         /* 0xFFFA User Non-maskable */
    isr_type_t sysnmi;       /* 0xFFFC System Non-maskable */
    isr_type_t reset;        /* 0xFFFE Reset [Highest Priority] */
} msp430f5659_int_vector_t;

static_assert(sizeof(msp430f5659_int_vector_t) == 128, 
              "Invalid MSP430F5659 Interrupt vector size.");

typedef msp430f5659_int_vector_t int_vector_t;

#else
/******************************************************************************* 
 * Unsupported MSP430 variant!
 ******************************************************************************/
#error "Selected MSP430 type not supported!"

#endif

#endif // if !defined(__INT_VECTOR_H__)