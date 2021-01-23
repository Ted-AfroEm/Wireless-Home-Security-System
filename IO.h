

//#define LED_1_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
//#define LED_1_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define LED_2_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define LED_2_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define LED_3_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define LED_3_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
//#define LED_4_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
//#define LED_4_SetLow()             do { LATBbits.LATB3 = 0; } while(0)

//#define LED_1_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define LED_2_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define LED_3_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
//#define LED_4_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)

#define UART1_SendLR() UART1_SendData(0X0D);UART1_SendData(0X0A)

#define KEY1()           PORTCbits.RC5

#define ir RC0 

#define PIR_Motion_detection()      PORTBbits.RB0
#define PIR_Disable()               do { LATBbits.LATB0 = 0; } while(0)      
    
#define TurnON_Buzzer()             do { LATBbits.LATB5 = 1; } while(0)
#define TurnOFF_Buzzer()            do { LATBbits.LATB5 = 0; } while(0)
#define Toggle_Buzzer()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)

//#define GSM_ResetON()               do { LATDbits.LATD7 = 0; } while(0)
//#define GSM_ResetOFF()              do { LATDbits.LATD7 = 1; } while(0)