


typedef 	char	u8;
typedef 	int	u16;
typedef 	long	u32;

#define Buf_Max 		70
#define STABLE_TIMES	  	10

char Uart1_Buf[Buf_Max];
uint8_t First_Int = 0;

struct
{
    unsigned char rx;       //this will hold RX byte
    unsigned char tx;       //this will hold TX byte
    unsigned isrx   :1;     //flag to signal the existance of a new RX byte
}rs232;

void OSCILLATOR_Initialize(void)
{
    // NOSC HFINTOSC; NDIV 1; 
    OSCCON1 = 0x60;
    // CSWHOLD may proceed; SOSCPWR Low power; 
    OSCCON3 = 0x00;
    // MFOEN disabled; LFOEN disabled; ADOEN disabled; SOSCEN disabled; EXTOEN disabled; HFOEN disabled; 
    OSCEN = 0x00;
    // HFFRQ 4_MHz; 
    OSCFRQ = 0x02;
    // TUN 0; 
    OSCTUNE = 0x00;
}

void PIN_Initialize(void)
{
    TRISB = 0xF0;       //RB3,RB2,RB1,RB0 - are LED outputs
    TRISC = 0xBF;       //RC7 - input(RX) : RC6 - output(TX) //set RC5 as input
      
    ANSELC = 0x1F;      //RC7(TX),RC6(RX) - are Digital 00111111 //set RC5 Digital
    ANSELB = 0xF0;      //RB3,RB2,RB1,RB0 - are Digital
	
    RC6PPS = 0x13;      //RC6->UART1:TX1;    
    U1RXPPS = 0x17;     //RC7->UART1:RX1;    
}

