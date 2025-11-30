#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 7

int min(int a,int b){return a<b?a:b;}

void SCCUtil(int u,int disc[],int low[],bool stackMember[],int stack[],int *top,int graph[V][V],int *time){
    disc[u]=low[u]=++(*time);
    stackMember[u]=true;
    stack[++(*top)]=u;
    for(int v=0;v<V;v++){
        if(graph[u][v]){
            if(disc[v]==-1){
                SCCUtil(v,disc,low,stackMember,stack,top,graph,time);
                low[u]=min(low[u],low[v]);
            } else if(stackMember[v]) low[u]=min(low[u],disc[v]);
        }
    }
    int w=0;
    if(low[u]==disc[u]){
        printf("SCC: ");
        while(stack[*top]!=u){
            w=stack[(*top)--];
            printf("%d ",w);
            stackMember[w]=false;
        }
        w=stack[(*top)--];
        printf("%d\n",w);
        stackMember[w]=false;
    }
}

void findSCCs(int graph[V][V]){
    int disc[V],low[V],stack[V],top=-1,time=0;
    bool stackMember[V];
    for(int i=0;i<V;i++){disc[i]=-1;low[i]=-1;stackMember[i]=false;}
    for(int i=0;i<V;i++) if(disc[i]==-1) SCCUtil(i,disc,low,stackMember,stack,&top,graph,&time);
}

void APBUtil(int u,bool visited[],int disc[],int low[],int parent[],bool ap[],int graph[V][V],int *time){
    visited[u]=true;
    disc[u]=low[u]=++(*time);
    int children=0;
    for(int v=0;v<V;v++){
        if(graph[u][v]){
            if(!visited[v]){
                children++;
                parent[v]=u;
                APBUtil(v,visited,disc,low,parent,ap,graph,time);
                low[u]=min(low[u],low[v]);
                if(parent[u]==-1 && children>1) ap[u]=true;
                if(parent[u]!=-1 && low[v]>=disc[u]) ap[u]=true;
                if(low[v]>disc[u]) printf("Bridge: %d - %d\n",u,v);
            } else if(v!=parent[u]) low[u]=min(low[u],disc[v]);
        }
    }
}

void findAPB(int graph[V][V]){
    bool visited[V]={0},ap[V]={0};
    int disc[V],low[V],parent[V],time=0;
    for(int i=0;i<V;i++){disc[i]=-1;low[i]=-1;parent[i]=-1;}
    for(int i=0;i<V;i++) if(!visited[i]) APBUtil(i,visited,disc,low,parent,ap,graph,&time);
    printf("Articulation Points: ");
    for(int i=0;i<V;i++) if(ap[i]) printf("%d ",i);
    printf("\n");
}

int main(){
    int directed[V][V]={
        {0,1,0,0,0,0,0},
        {0,0,1,0,0,0,0},
        {1,0,0,0,0,0,0},
        {0,0,0,0,1,0,0},
        {0,0,0,0,0,1,0},
        {0,0,0,1,0,0,0},
        {0,0,0,0,0,0,0}
    };
    int undirected[V][V]={
        {0,1,1,0,0,0,0},
        {1,0,1,1,0,0,0},
        {1,1,0,0,0,0,0},
        {0,1,0,0,1,1,0},
        {0,0,0,1,0,1,0},
        {0,0,0,1,1,0,1},
        {0,0,0,0,0,1,0}
    };
    printf("Strongly Connected Components (Directed Graph):\n");
    findSCCs(directed);
    printf("\nBridges and Articulation Points (Undirected Graph):\n");
    findAPB(undirected);
    return 0;
}
