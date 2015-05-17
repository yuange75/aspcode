
int newrecv(int fd,char *buff,int size,int flag){
    
	int i,k;
	k=recv(fd,buff,size,flag); 
    if(k==0||k<0)
	{

		 i=WSAGetLastError();
		 if(k==0||i==0x2746||i==0x2745)
		 {
            strout("\r\n\r\nServer close!\r\n");
			Sleep(1000);
			exit(1);  
         }
	}

    if(xordatabegin==1){
			  for(i=0;i<k;++i){
                lockintvar1=lockintvar1*0x100;
				lockintvar1=lockintvar1%LOCKBIGNUM;
				lockcharvar=lockintvar1%0x100;
                buff[i]^=lockcharvar;   // DATAXORCODE;
			  }
    
	}
	else{
		if(k>0){
			buff[k]=0;
			if(strstr(buff,"XORDATA")!=0) {
		      xordatabegin=1;
			  i=strstr(buff,"XORDATA");
              memcpy(i,"\r\nok!!\r\n",8);
              for(i=strstr(buff,"\r\nok!!\r\n")-buff+8;i<k;++i)
			  {
                lockintvar1=lockintvar1*0x100;
				lockintvar1=lockintvar1%LOCKBIGNUM;
				lockcharvar=lockintvar1%0x100;
                buff[i]^=lockcharvar;   // DATAXORCODE;
			  }
			}
         }
			
	}
    return(k);


}

int newsend(int fd,char *buff,int size,int flag){
          int i;
	
          for(i=0;i<size;++i){
                lockintvar2=lockintvar2*0x100;
				lockintvar2=lockintvar2%LOCKBIGNUM;
				lockcharvar=lockintvar2%0x100;
                buff[i]^=lockcharvar;   // DATAXORCODE;
  //              buff[i]^=DATAXORCODE;
		  }

      return(send(fd,buff,size,flag));   

}


