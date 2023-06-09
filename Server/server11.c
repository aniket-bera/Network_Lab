#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5670

int main(){
	struct sockaddr_in client, server;
	char msg[512];
        int sd,pid,clen=sizeof(client);

        bzero((char *)&server,sizeof(server));
        server.sin_family=AF_INET;
        server.sin_addr.s_addr=inet_addr(SERVER_IP);
        server.sin_port=htons(SERVER_PORT);

        sd=socket(AF_INET,SOCK_DGRAM,0);
        bind(sd,(struct sockaddr*)&server,sizeof(server));

        while(1){
		pid=fork();
		if(pid>0){
			close(sd);
		}
		else if(pid==0){
                	do{
                        	memset(msg,0x0,512);
                        	recvfrom(sd,msg,512,0,(struct sockaddr*)&client,&clen);
                       		sendto(sd,msg,strlen(msg)+1,0,(struct sockaddr*)&client,clen);
                	}while(strcmp(msg,"stop"));
        	}
	}
	return 0;
}
