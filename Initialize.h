
typedef 	char	u8;
typedef 	int	u16;
typedef 	long	u32;

#define Buf_Max 		200
#define STABLE_TIMES	  	10

char Uart1_Buf[Buf_Max];
uint8_t First_Int = 0;

char Server_URL[90];
char getHTTPBuffer[Buf_Max];    //Store data from Server
char getDataSize[3];            //Store getHTTP data size

char getToken[70];
char token[] = "aastumnbvcxzlkj";

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
    TRISB = 0xDD;       //RB2 - input for magnetic contact sensor
                        //RB3 - input for RF_Receiver
                        //RB0 - input for PIR Pin
                        //RB5 - output for Buzzer
    TRISC = 0xBF;       //RC7 - input(RX) : RC6 - output(TX) //set RC5 as input
                        //RC0 - input for IR_Pin
    //TRISDbits.TRISD7 = x0; //GSM Reset pin
    TRISD = 0xFC;       //RD0,RD1 - are LED outputs
    
    ANSELC = 0x1F;      //RC7(TX),RC6(RX) - are Digital 00111111 //set RC5 Digital
    ANSELB = 0xD0;      //RB3,RB2,RB1,RB0 - are Digital
                        //RB5 - is digital for Buzzer
    ANSELD = 0xFC;      //RD0,RD1 are digital
    
    RC6PPS = 0x13;      //RC6->UART1:TX1;    
    U1RXPPS = 0x17;     //RC7->UART1:RX1;    
}

