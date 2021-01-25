//static u8 * phone_num = "ATD+251974437960;";
//static u8 * text_phone_num = "AT+CMGS=\"+251974437960\"";

static u8 * phone_num = "ATD+251970751906;";
static u8 * text_phone_num = "AT+CMGS=\"+251970751906\"";

u8 Find(u8 * a) {
  PIE3bits.U1IE = 0;

  if (strstr(Uart1_Buf, a) != NULL) {
    PIE3bits.U1IE = 1;
    return 1;
  } else {
    PIE3bits.U1IE = 1;
    return 0;
  }

}

void delay_ms(u16 ms) {
  int i = 0;
  for (i = 0; i < ms; i++)
    __delay_ms(20);

}

void UART1_Send_Command(char * s) {
  CLR_Buf();
  while ( * s)
  {
    UART1_SendData( * s++); 
  }
  UART1_SendLR();
}
void UART1_Send_Command_END(char *s)
{
	CLR_Buf(); 
	while(*s)
	{
		UART1_SendData(*s++);
	}
}
u8 UART1_Send_AT_Command_END(u8 *b,u8 *a,u8 wait_time,u16 interval_time)         
{
	u8 i;

	CLR_Buf(); 
	i = 0;
	while(i < wait_time)                    
	{
		UART1_Send_Command_END(b);
		delay_ms(interval_time);
		if(Find(a))            
		{
			return 1;
		}
		i++;
	}
	
	return 0;
}

u8 Wait_CREG(u8 query_times) {
  u8 i;
  u8 k;
  u8 j = 0;
  i = 0;
  CLR_Buf();
  while (i == 0) {
    //Network Registration 
    UART1_Send_Command("AT+CREG?");
    __delay_ms(100);

    for (k = 0; k < Buf_Max; k++) {
      if ((Uart1_Buf[k] == '+') && (Uart1_Buf[k + 1] == 'C') && (Uart1_Buf[k + 2] == 'R') && (Uart1_Buf[k + 3] == 'E') && (Uart1_Buf[k + 4] == 'G') && (Uart1_Buf[k + 5] == ':')) {

        if (((Uart1_Buf[k + 7] == '1') || ((Uart1_Buf[k + 7] == '0'))) && ((Uart1_Buf[k + 9] == '1') || (Uart1_Buf[k + 9] == '5'))) {
          i = 1;
          return 1;
        }

      }
    }
    j++;
    if (j > query_times) {
      return 0;
    }

  }
  return 0;
}

u8 UART1_Send_AT_Command(u8 * b, u8 * a, u8 wait_time, u16 interval_time) {
  u8 i;

  CLR_Buf();
  i = 0;
  while (i < wait_time) {
    CLR_Buf();
    UART1_Send_Command(b);
    delay_ms(interval_time);
    if (Find(a)) {
      return 1;
    }
    i++;
  }

  return 0;
}

int call_phone_num(char * phone) {
  int ret;

  //ret = UART1_Send_AT_Command("ATD+251974437960;","OK",3,50);
  ret = UART1_Send_AT_Command("AT", "OK", 3, 50);
  //ATD+251974437960;

  if (ret == 0) {
    return COMMUNITE_ERROR;
  }

  ret = UART1_Send_AT_Command("AT+CPIN?", "READY", 3, 50);
  if (ret == 0) {
    return NO_SIM_CARD_ERROR;
  }
  //shows whether the network has currently indicated the registration
  ret = Wait_CREG(3);
  if (ret == 0) {
    return SIM_CARD_NO_REG_ERROR;
  }

  //Make a voice call
  ret = UART1_Send_AT_Command(phone, "OK", 2, 50);
  if (ret == 0) {
    return CALL_ERROR;
  }
  
  delay_ms(1000);
  UART1_Send_AT_Command("ATH", "OK", 2, 50); //end call
  
  return 1;
}

int send_text_message(char *content)
{
	u8 ret;
	char end_char[2];
	
	end_char[0] = 0x1A;
	end_char[1] = '\0';
	
	//Preferred SMS Message Storage
	ret = UART1_Send_AT_Command("AT+CPMS=\"SM\",\"ME\",\"SM\"","OK",3,100);
	if(ret == 0)
	{
		return AT_CPMS_ERROR;
	}
	//Select SMS Message Format  
	ret = UART1_Send_AT_Command("AT+CMGF=1","OK",3,50); //Text Modes
	if(ret == 0)
	{
		return AT_CMGF_ERROR;
	}
	
	//Select TE Character Set
	ret = UART1_Send_AT_Command("AT+CSCS=\"GSM\"","OK",3,50);//"GSM"  GSM 7 bit default alphabet
	if(ret == 0)
	{
		return AT_CSCS_ERROR;
	}
	//Send SMS Message
	ret = UART1_Send_AT_Command(text_phone_num,">",3,50);
	if(ret == 0)
	{
		return AT_CMGS_ERROR;
	}
	
	UART1_SendString(content); //load text to be sent to Buffer
	ret = UART1_Send_AT_Command_END(end_char,"OK",1,250); // <Ctrl+Z> to specify the end of the SMS
	if(ret == 0)
	{
		return END_CHAR_ERROR;
	}
	
	return 1;
}
