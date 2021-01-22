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
#include <stdint.h>
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

  INTCON0bits.GIE = 1; //Enable the Global Interrupt

  __delay_ms(1000);

  UART1_Send_Greeting("What's UP");
  UART1_Send_Greeting("Congrats....UART have successfully send string");

  u8 i;
  int ret;

  for (i = 0; i < STABLE_TIMES; i++) {
    __delay_ms(100);
  }

  while (1) {
    __delay_ms(500);
    LED_2_Toggle();
    
        while (PIR_Motion_detection()) {

        ret = check_status();

        if (ret == 1 ) {
          ret = call_phone_num(phone_num);
          //ret = get_data_from_server("\"https://gcpro.herokuapp.com/teset/getdata\"");
          //ret = post_data_to_server("\"https://gcpro.herokuapp.com/teset/send\"");
          UART1_Send_Greeting("SUCCESS");

        }
        if (ret == -56 || ret == -58) {
          terminateBearerHTTP();
          UART1_Send_Greeting("Bearer and HTTP Terminated");
        }
        if (ret == -1) {
          //reset GSM here
          UART1_Send_Greeting("COMMUNITE_ERROR"); 
          //wait for some time
        }
        if (ret == -3) {
          UART1_Send_Greeting("SIM_CARD_NO_REG_ERROR");
        }
        __delay_ms(1000);
        LATB = 0x00;

      }
  }
}