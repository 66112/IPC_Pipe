#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
int main()
{
	umask(0);
  if(mkfifo("mypipe",0644)<0){
      perror("mkfifo:");
      exit(1);
  }
//int fd=open("mypipe",O_RDONLY);
  int fd=open("mypipe",O_RDWR);
  if(fd<0){
      perror("open:");
      exit(1);
  }
  char buf[1024];
  while(1){
      ssize_t s=read(fd,buf,sizeof(buf)-1);
      if(s>0){
          buf[s-1]=0;
          printf("%s\n",buf);
      }
      else if(s==0){
          printf("client quit,server quit too!\n");
          break;
      }
      else{
          break;
      }
  }
  close(fd);
	return 0;
}
