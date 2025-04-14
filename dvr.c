#include<stdio.h>
#include<stdlib.h>

struct node{
    unsigned dist[20];
    unsigned from[20];
}rt[20];

int main(){
    int costmat[20][20],i,j,k,nodes,count=0;
    printf("Enter the no of nodes:");
    scanf("%d",&nodes);
    printf("Enter the cost matrix:\n");
    for(i=0;i<nodes;i++){
        for(j=0;j<nodes;j++){
            scanf("%d",&costmat[i][j]);
            costmat[i][i]=0;
            rt[i].dist[j]=costmat[i][j];
            rt[i].from[j]=j;
        }
    }
    do{
    count=0;
    for(i=0;i<nodes;i++){
        for(j=0;j<nodes;j++){
            for(k=0;k<nodes;k++){
                if(rt[i].dist[j]>costmat[i][k]+rt[k].dist[j]){
                    rt[i].dist[j]=rt[i].dist[k]+rt[k].dist[j];
                    rt[i].from[j]=k;
                    count++;
                }
            }
        }
    }
    }while(count>0);
    for(i=0;i<nodes;i++){
        printf("Routing table for %d\n",i);
        for(j=0;j<nodes;j++){
            printf("node %d via %d and distance%d\n",j,rt[i].from[j],rt[i].dist[j]);
        }
    }
}
