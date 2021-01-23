

#define LED_0_SetHigh()            do { LATBbits.LATD0 = 1; } while(0)
#define LED_0_SetLow()             do { LATBbits.LATD0 = 0; } while(0)
#define LED_1_SetHigh()            do { LATBbits.LATD1 = 1; } while(0)
#define LED_1_SetLow()             do { LATBbits.LATD1 = 0; } while(0)

#define LED_0_Toggle()             do { LATBbits.LATD0 = ~LATBbits.LATD0; } while(0)
#define LED_1_Toggle()             do { LATBbits.LATD1 = ~LATBbits.LATD1; } while(0)

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