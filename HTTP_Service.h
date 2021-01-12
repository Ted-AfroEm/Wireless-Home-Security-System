
int check_status (void)
{
	int  ret;
	
        ret = UART1_Send_AT_Command("AT","OK",3,50);
	if(ret == 0)
	{
		return COMMUNITE_ERROR;
	}
	
	ret = UART1_Send_AT_Command("AT+CPIN?","READY",3,50);
	if(ret == 0)
	{
		return NO_SIM_CARD_ERROR;
	}
	//shows whether the network has currently indicated the registration
	ret = Wait_CREG(3);
	if(ret == 0)
	{
		return SIM_CARD_NO_REG_ERROR;
	}
	
	return 1;
}



//Terminate Bearer and HTTP
void terminateBearerHTTP(void){
    UART1_Send_AT_Command("AT+SAPBR=0,1","OK",2,70);  //terminate bearer
    UART1_Send_AT_Command("AT+HTTPTERM","OK",2,50);   //terminate HTTP
}

u8 Wait_SAPBR(u8 query_times){
    u8 i;
    u8 k;
    u8 j = 0;
    i = 0;
    CLR_Buf();
    while(i == 0)        			
    {
       
        //Query bearer
        UART1_Send_Command("AT+SAPBR=2,1");
        __delay_ms(100); 

        for(k=0;k<Buf_Max;k++)      			
        {
            if((Uart1_Buf[k] == '+')&&(Uart1_Buf[k+1] == 'S')&&(Uart1_Buf[k+2] == 'A')&&(Uart1_Buf[k+3] == 'P')&&(Uart1_Buf[k+4] == 'B')&&(Uart1_Buf[k+5] == 'R')&&(Uart1_Buf[k+6] == ':'))
            {
                if(((Uart1_Buf[k+8] == '1')||(Uart1_Buf[k+8] == '0')||(Uart1_Buf[k+8] == '2')||(Uart1_Buf[k+8] == '3')||(Uart1_Buf[k+8] == '4'))&&
                    ((Uart1_Buf[k+10] == '1')||(Uart1_Buf[k+10] == '2')||(Uart1_Buf[k+10] == '3')))
                {
                    i = 1;
                    return 1;
                }
            }
        }
        j++;
        if(j > query_times)
        {
            return 0;
        }
    }
    return 0;
}


int activate_bearer()
{
    int ret;
    
    ret = UART1_Send_AT_Command("AT+SAPBR=3,1,\"Contype\",\"GPRS\"","OK",2,50); // Open GPRS
    if(ret==0){
        return AT_SAPBR_GPRS_ERROR;
    }
    ret = UART1_Send_AT_Command("AT+SAPBR=3,1,\"APN\",\"CMNET\"","OK",2,50);    // Set Access point name
    if(ret==0){
        return AT_SAPBR_APN_ERROR;
    }
    ret = UART1_Send_AT_Command("AT+SAPBR=1,1","OK",2,50); //Open bearer
    if(ret==0){
        return AT_SAPBR_OPEN_ERROR;
    }
    ret = Wait_SAPBR(3);
    if(ret==0){
        return AT_SAPBR_QUERY_ERROR;
    }
    return 1;
    
}

//To get Data from server
int get_data_from_server(char *URL)
{
    int ret;

   ret = activate_bearer();
    if(ret==0){
        return AT_SAPBR_ERROR;
    }
    //Initialize HTTP Service 
    ret = UART1_Send_AT_Command("AT+HTTPINIT","OK",2,50);
    if(ret==0){
        return AT_HTTPINTI_ERROR;
    }
    //Set HTTP to Use SSL(secure sockets layer) Function
    ret = UART1_Send_AT_Command("AT+HTTPSSL=1","OK",2,50);
    if(ret==0){
        return AT_HTTPSSL_ERROR;
    }
    //Set HTTP Bearer profile identifier
    ret = UART1_Send_AT_Command("AT+HTTPPARA=\"CID\",1","OK",2,50);
    if(ret==0){
        return AT_HTTPPARA_ERROR;
    }
    
    memset(Server_URL,'\0',90);
    strcpy(Server_URL,"AT+HTTPPARA=\"URL\",");
    strcat(Server_URL, URL);
    //Set HTTP URL
    ret = UART1_Send_AT_Command(Server_URL,"OK",3,50*2);
    if(ret==0){
        return AT_HTTPARA_URL_ERROR;
    }
    
    return ret;
     
}
