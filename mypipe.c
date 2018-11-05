#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main()
{
	int fds[2];
	if(pipe(fds)<0){         //匿名管道，
		perror("pipe:");
		exit(1);
	}
//	printf("%d %d\n",fds[0],fds[1]);   	//3和4,相当于用两种方式打开了1个文件
	pid_t id=fork();         //创建子进程
	if(id == 0){
		//child  "w"
		close(fds[0]);              //关闭读的方式打开的文件，引用计数-1 ，（硬链接）
		printf("Please talk: \n");
		const char* msg="i have a dream!\n";  
		int i=5;
		while(i--){
			write(fds[1],msg,strlen(msg));     //往文件中写入内容
			sleep(1);
		}
		close(fds[1]);           //关闭pipe文件
		exit(0);
	}
	else if(id > 0){
		//parent  "r"
		close(fds[1]);                //关闭写的方式打开的文件，引用计数-1 ，（硬链接）    
		char buf[1024];
		while(1){
			ssize_t s=read(fds[0],buf,sizeof(buf)-1);  //从缓冲区读文件，留一个字节放EOF
			if(s>0){
				buf[s-1]=0;           //把换行符一覆盖     
				printf("%s\n",buf);
			}
			else{
				break;
			}
		}
		waitpid(id,NULL,0);         //等待子进程退出
	}
	else{
		perror("fork:");
		exit(1);
	}
	return 0;
}
