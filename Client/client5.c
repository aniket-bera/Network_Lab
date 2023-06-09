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
        int sd;
        struct sockaddr_in client, server;
        char smsg[512], rmsg[512];

        bzero((char *)&client,sizeof(client));
        client.sin_family=AF_INET;
        client.sin_port=htons(CLIENT_PORT);
        client.sin_addr.s_addr=inet_addr(CLIENT_IP);

        bzero((char *)&server,sizeof(server));
        server.sin_family=AF_INET;
        server.sin_port=htons(SERVER_PORT);
        server.sin_addr.s_addr=inet_addr(SERVER_IP);

        sd=socket(AF_INET,SOCK_STREAM,0);
        bind(sd,(struct sockaddr*)&client,sizeof(client));
        connect(sd,(struct sockaddr*)&server,sizeof(server));

        do{
                printf("\nSending msg for server: ");
                gets(smsg);
                send(sd,smsg,strlen(smsg)+1,0);
		memset(rmsg,0x0,512);
		recv(sd,rmsg,512,0);
		printf("\nEchoed msg: %s",rmsg);
        }while(strcmp(smsg,"stop"));
        close(sd);
}
