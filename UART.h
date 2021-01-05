

void CLR_Buf(void)
{
	u8 k;
	for(k=0;k<Buf_Max;k++)      
	{
		Uart1_Buf[k] = 0x00;
	}
    First_Int = 0;              
}

void UART1_SendData(uint8_t dat)
{
    
    while(U1FIFObits.TXBE == 0); // wait for buffer to be empty 
    //transmit buffer empty status bit
	U1TXB = dat;		// serial port buffeer	
   
}

void UART1_Send_Greeting(char *s)
{
    
	while(*s)//????????
	{
		UART1_SendData(*s++);//??????
	}
    CLR_Buf();  
	UART1_SendLR();
}


void UART_Initialize(void)
{
    rs232.rx = 0;
    rs232.tx = 0;
    rs232.isrx = 0;
    
    U1FIFO = 0x00;      //Clear status register
    U1CON0 = 0xB0;      //8bit Asyn,TX enable,RX enable
    U1CON1 = 0x80;      //serial port enable
    
    //19200 baud rate from: BRGS = 1, FOSC = 4MHZ
    // calculated value = (FOSC/19200)/4 - 1 = 51.08333 ~ 51 
    // 51 = 0x0033(in Hex): 
    U1BRGL = 0x33;
    U1BRGH = 0x00;

    PIE3bits.U1RXIE = 1;    //enable RX interrupt
    
    PIE3bits.U1IE = 1;      //uart1 interrupt enable
   
}
