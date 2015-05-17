
void  strout(char *buff)  //,int len)
{

	int i,j;
	char buff2[BUFFSIZE];
	if(callback_socket==0)
	{
//      buff[len]=0;
        printf("%s",buff);
	}
	else
	{
		i=strlen(buff);
		if(i>0)
		{
             for(j=0;j<i;++j) buff2[j]=buff[j]^0x99;
		}
		send(callback_socket,buff2,i,0);  //len,0);
	}

}

 

void  outprintf(const char *format,...)
{
	  char     outbuff[BUFFSIZE] ;

	  int     *var=&format;     

      sprintf(outbuff,format,*(var+1),*(var+2),*(var+3),*(var+4),*(var+5),*(var+6));
      strout(outbuff);
}

/*
void  outfprintf(int f,const char *format,...)
{
	  char     outbuff[BUFFSIZE] ;

	  int     *var=&format;     

      sprintf(outbuff,format,*(var+1),*(var+2),*(var+3),*(var+4),*(var+5),*(var+6));
      strout(outbuff);
}


*/
int  strin(char *buff,int len)
{

    int i,j;

	if(callback_socket==0)
	{
       gets(buff);
// 	   strcat(buff,"\r\n");
	   i=strlen(buff);
	}
	else
	{
		i=recv(callback_socket,buff,len,0);
		if(i>0)
		{
			 buff[i]=0;
             for(j=0;j<i;++j) buff[j]^=0x99;
             for(j=0;j<i;++j){
				 if(buff[j]=='\r'||buff[j]=='\n') buff[j]=0x0;
			 }
		}
		else
		{

		     j=WSAGetLastError();
		     if(i==0||j==0x2746||j==0x2745)
			 {
		         printf("\r\nCall_back server close! \r\n");
			     exit(1);
			 }	 
		}

	}
    return i;
}
