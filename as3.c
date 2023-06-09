#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

int main(){
	int fd1, n, fd2[2], p;
	char str1[1024], str2[1024];
	fd1=open("test.txt",O_RDONLY,0764);
	n=read(fd1,str1,1024);
	pipe(fd2);
	p=fork();
	if(p==-1){
		printf("error in fork");
		exit(1);
	}
	else if(p==0){
		printf("\nIn Child");
		close(fd2[0]);
		write(fd2[1],str1,n);
	}
	else{
		printf("\nIn Parent");
		close(fd2[1]);
		read(fd2[0],str2,1024);
		str2[n]='\0';
		printf("\nFile content:\n%s",str2);
	}
}
