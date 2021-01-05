/*
 * File:   LEDBlink.c
 * Author: Afro
 *
 * Created on January 5, 2021, 4:53 AM
 */

/*
 Points to make sure
 * Arduino Should be on RESET to use it us UART-TTL converter
 * UART Buadrate is 19200
 * 
 */

#include <xc.h>
//#include <stdio.h>
#include <stdint.h>
//#include <stdbool.h>
//#include "string.h"

#include "device_Config.h"
#include "IO.h"
#include "Initialize.h"
#include "UART.h"
#include "Interrupt.h"

#define _XTAL_FREQ 4000000

void main(void) {
    
    PIN_Initialize(); 
    OSCILLATOR_Initialize();
    UART_Initialize();
   
    INTCON0bits.GIE = 1;    //Enable the Global Interrupt
    
    __delay_ms(1000);
    
    UART1_Send_Greeting("What's UP");
    UART1_Send_Greeting("Congrats....UART have successfully send string");
    
    LATB = 0x00;
     while(1)
    {
        UART1_Send_Greeting("LED ON");
       LED_1_SetHigh();
       LED_3_SetHigh();
       __delay_ms(1000);  
       UART1_Send_Greeting("LED OFF");
       LED_1_SetLow() ;
       LED_3_SetLow() ;
       __delay_ms(1000); 
      
    }
  
    //return;
}
