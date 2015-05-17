
void  printinfo()
{ 

	char buff[BUFFSIZE];

	if(callback_socket!=0)
	{
		_snprintf(buff,BUFFSIZE,"exp_name=\"%s\",exp_ip=%s,exp_port=%s\r\n",exp_name,server,s_port);
	}	
    else
	{
		_snprintf(buff,BUFFSIZE,"exp_name=\"%s\",exp_ip=%s,exp_port=%s\r\n",exp_name,server,s_port);

	}
	strout(buff);
} 