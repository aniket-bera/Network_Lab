#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<time.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5670

int main(){
        struct sockaddr_in client, server;
        int sd, nsd, clen=sizeof(client);
        char *msg;
        char stime[512], ntime[]="Invalid Request";
        time_t t;

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
                        memset(stime,0x0,512);
                        recv(nsd,stime,512,0);
                        if(!strcmp(stime,"time")){
                                t=time(NULL);
                                msg=ctime(&t);
                                send(nsd,msg,strlen(msg)+1,0);
				}
                        else{
                                send(nsd,ntime,strlen(ntime)+1,0);
                        }
                }while(strcmp(stime,"stop"));
                close(nsd);
        }
}
