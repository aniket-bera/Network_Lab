#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5670

int main(){
        struct sockaddr_in server,client;
        char smsg[512], rmsg[512];
        int sd, nsd, clen=sizeof(client);

        bzero((char *)&server,sizeof(server));
        server.sin_family=AF_INET;
        server.sin_port=htons(SERVER_PORT);
        server.sin_addr.s_addr=inet_addr(SERVER_IP);

        sd=socket(AF_INET,SOCK_STREAM,0);
        bind(sd,(struct sockaddr*)&server,sizeof(server));
	
	listen(sd,5);
	
	while(1){
		nsd=accept(sd,(struct sockaddr*)&client,&clen);
		do{
			memset(rmsg,0x0,512);
			recv(nsd,rmsg,512,0);
			printf("Client's msg: %s",rmsg);
			if(strcmp(rmsg,"stop")){
				printf("\nEnter msg for client: ");
				scanf("%s",smsg);
				send(nsd,smsg,strlen(smsg)+1,0);
			}
		}while(strcmp(rmsg,"stop"));
		close(nsd);
	}
	return 0;
}
