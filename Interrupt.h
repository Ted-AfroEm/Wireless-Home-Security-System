
//#include "Initialize.h"

void __interrupt() InterruptManager()
{
    // interrupt handler
    if(PIE3bits.U1IE == 1 && PIR3bits.U1IF == 1)
    {
        Uart1_Buf[First_Int] = U1RXB;  	  
		First_Int++;                	  
		if(First_Int > Buf_Max)       	  
		{
			First_Int = 0;
		} 
        PIR3bits.U1IF = 0;
    }
    else if(PIE3bits.U1RXIE == 1 && PIR3bits.U1RXIF == 1)
    {
     
		Uart1_Buf[First_Int] = U1RXB;  	  
		First_Int++;                	  
		if(First_Int > Buf_Max)       	  
		{
			First_Int = 0;
		}     
        
	rs232.rx = U1RXB;       //read RX buffer
        rs232.isrx = 1;         //set RX flag
        PIR3bits.U1RXIF = 0;    //clear RX Interrupt flag
    }
	if(PIR3bits.U1IF)
	{
		PIR3bits.U1IF = 0;
	}
    else
    {
        
    }
}