
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