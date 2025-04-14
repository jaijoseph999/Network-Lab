#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

int main(){
    FILE *fp;
    int sockdesc,clientsock,clientsize,n;
    struct sockaddr_in serveraddr,clientaddr;
    char smsg[200],cmsg[200],fileread[200],fname[200];

    memset(smsg,'\0',sizeof(smsg));
    memset(cmsg,'\0',sizeof(cmsg));

    sockdesc=socket(AF_INET,SOCK_STREAM,0);

    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(2000);
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    if(sockdesc<0){
        printf("socket failed......!\n");
    }
    printf("socket creation successful.......!\n");

    if(bind(sockdesc,(struct sockaddr*)&serveraddr,sizeof(serveraddr))<0){
        printf("binding failed.......!\n");
        return -1;
    }
    printf("binding successful.......!\n");

    if(listen(sockdesc,1)<0){
        printf("listening failed.......!\n");
        return -1;
    }
    printf("listening successful.......!\n");

    clientsize=sizeof(clientaddr);
    clientsock=accept(sockdesc,(struct sockaddr*)&clientaddr,&clientsize);
    recv(clientsock,cmsg,sizeof(cmsg),0);
    if(n<0){
        printf("Receving message failed....!\n");
        return -1;
    }
    printf("Receving message successful....!\n");
    n=strlen(cmsg);
    cmsg[n-1]='\0';
    printf("%s %d\n",cmsg,n);

    fp=fopen(cmsg,"r");

    if(fp!=NULL){
        while(fgets(fileread,sizeof(fileread),fp)!=NULL){
            if(send(clientsock,fileread,strlen(fileread),0)<0){
                printf("Send message failed......!\n");
                return -1;
            }
            memset(fileread,'\0',sizeof(fileread));
        }
        printf("Done..!\n");
        send(clientsock,"complete",8,0);
    }
    else{
        memset(fileread,'\0',sizeof(fileread));
        send(clientsock,"error",5,0);
        printf("File not present....!\n");
    }
    close(sockdesc);
    close(clientsock);
    fclose(fp);
}
