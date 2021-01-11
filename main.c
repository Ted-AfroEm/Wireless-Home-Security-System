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
#include "string.h"

#include "device_Config.h"
#include "IO.h"
#include "Initialize.h"
#include "UART.h"
#include "GSM_Errors.h"
#include "gsmSim800l.h"
#include "HTTP_Service.h"
#include "Interrupt.h"



void main(void) {
    
    PIN_Initialize(); 
    OSCILLATOR_Initialize();
    UART_Initialize();
   
    INTCON0bits.GIE = 1;    //Enable the Global Interrupt
    
    __delay_ms(1000);
    
    UART1_Send_Greeting("What's UP");
    UART1_Send_Greeting("Congrats....UART have successfully send string");
    
    u8 i;
    int ret;
	
        for(i = 0;i < STABLE_TIMES;i++)
        {
                __delay_ms(1000);
        }
    
    while(1)
    {
	__delay_ms(500);       
        LED_1_Toggle();

		if(KEY1()== 0)
            
			{		
            __delay_ms(100); 
			
			if(KEY1()== 0)
			{
				while(!KEY1());
				
				//ret = call_phone_num(phone_num);
                                ret = check_status();

				if(ret == 1)    //1
				{
                    LATB = 0x1;
                    UART1_Send_Greeting("SUCCESS");
                   //success
				}
				else if(ret == -1) //2
				{
                    LATB = 0x2;
                    UART1_Send_Greeting("COMMUNITE_ERROR");
                    //COMMUNITE_ERROR 
				}
				else if(ret == -2) //3
				{
                    LATB = 0x3;
                    UART1_Send_Greeting("NO_SIM_CARD_ERROR");
                    //NO_SIM_CARD_ERROR
                    
				}
				else if(ret == -3) //4
				{
                    LATB = 0x4;
                    UART1_Send_Greeting("SIM_CARD_NO_REG_ERROR");
                    //SIM_CARD_NO_REG_ERROR 
                }
				else if(ret == -4)  //5
				{
                    LATB = 0x5;
				}
				else    //6
				{
                    LATB = 0x6;
				}
				
                __delay_ms(3000);
                LATB = 0x00;
                
				
            }
        }
	
	
        
    }
  
    //return;
}
