#include<stdio.h>
#include<string.h>
#include<unistd.h>
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
        int sd,slen=sizeof(server);
	char msg[512],str[512];

        bzero((char *)&server, sizeof(server));
        server.sin_family=AF_INET;
        server.sin_addr.s_addr=inet_addr(SERVER_IP);
        server.sin_port=htons(SERVER_PORT);

        bzero((char *)&client, sizeof(client));
        client.sin_family=AF_INET;
        client.sin_addr.s_addr=inet_addr(CLIENT_IP);
        client.sin_port=htons(CLIENT_PORT);

        sd=socket(AF_INET, SOCK_DGRAM,0);
	
	do{
		printf("\nEnter a msg from Client1 to Server: ");
		scanf("%s",msg);
		sendto(sd,msg,strlen(msg)+1,0,(struct sockaddr*)&server,slen);
		memset(str,0x0,512);
		recvfrom(sd,str,512,0,(struct sockaddr*)&server,&slen);
		printf("\nThe Server's msg fro Client1: %s",str);
	}while(strcmp(str,"stop"));
	close(sd);
	return 0;
}
