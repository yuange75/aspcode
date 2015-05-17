

void over(int fd)
{
  int   strlen;
  char  buff[BUFFSIZE];

  strlen=GetOverStr(buff,server,urlfile,offset);
  send(fd,buff,strlen,0);
}