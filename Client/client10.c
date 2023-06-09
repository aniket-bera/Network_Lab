#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5670
#define CLIENT_IP "127.0.0.1"
#define CLIENT_PORT 5671

int main(){
	struct sockaddr_in server, client;
	int i, j, ws, sd, c=0, slen=sizeof(server);
	char msg[512], buff[512], ack[512];
	
	bzero((char *)&server, sizeof(server));
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr(SERVER_IP);
	server.sin_port=htons(SERVER_PORT);
	
	bzero((char *)&client, sizeof(client));
	client.sin_family=AF_INET;
	client.sin_addr.s_addr=inet_addr(CLIENT_IP);
	client.sin_port=htons(CLIENT_PORT);

	sd=socket(AF_INET, SOCK_STREAM,0);
	bind(sd,(struct sockaddr*)&client,sizeof(client));

	connect(sd,(struct sockaddr*)&server,sizeof(server));

	do{
		printf("\nEnter a msg: ");
		scanf("%s",msg);
		printf("\nEnter the window size: ");
		scanf("%d",&ws);
		j=0;
		for(i=0;i<strlen(msg);i++){
			if(j<ws){
				buff[j++]=msg[i];
			}
			if(j==ws||i==strlen(msg)-1){
				buff[j]='\0';
				send(sd,buff,strlen(buff)+1,0);
				memset(ack,0x0,512);
				recv(sd,ack,512,0);
				printf("\n%s: %d",ack,c++);
				j=0;
			}
		}
	}while(strcmp(msg,"stop"));
	close(sd);
}
