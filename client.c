#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    int fd=open("mypipe",O_WRONLY);
    if(fd<0){
        perror("open:");
    }
    printf("Please write your question!#");
    fflush(stdout);
    char buf[1024]={0};
    while(1){
        ssize_t s=read(0,buf,sizeof(buf)-1);
        if(s>0){
            buf[s]=0;
            printf("Please write your question!#");
            fflush(stdout);
            write(fd,buf,s);
        }
        else{
            break;
        }
    }
    close(fd);
    return 0;
}
