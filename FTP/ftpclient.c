#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

int main(){
    FILE *fp;
    int sockdesc;
    struct sockaddr_in serveraddr;
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

    if(connect(sockdesc,(struct sockaddr*)&serveraddr,sizeof(serveraddr))<0){
        printf("connection failed.......!\n");
        return -1;
    }

    printf("connection successful......!\n");

    printf("Enter the file name:");
    fgets(cmsg,sizeof(cmsg),stdin);
    if(send(sockdesc,cmsg,sizeof(cmsg),0)<0){
        printf("Send message failed......!\n");
        return -1;
    }
    fp=fopen("new.txt","w");
    printf("Sending message successful....!\n");
    while(1){
        memset(smsg,'\0',sizeof(smsg));
        if(recv(sockdesc,smsg,sizeof(smsg),0)<0){
            printf("Receving message failed....!\n");
            return -1;
        }
        if(strcmp(smsg,"error")==0){
            printf("file not found....!\n");
            return -1;
        }
        if(strcmp(smsg,"complete")==0){
            printf("transfer is done....!\n");
            break;
        }
        fprintf(fp,"%s",smsg);
        printf("%s",smsg);
    }
    fclose(fp);

}
