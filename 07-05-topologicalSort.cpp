#include <stdio.h>
#include <stdbool.h>

#define V 6

void dfs(int v,int visited[],int stack[],int *top,int graph[V][V]){
    visited[v]=1;
    for(int i=0;i<V;i++)
        if(graph[v][i] && !visited[i])
            dfs(i,visited,stack,top,graph);
    stack[++(*top)]=v;
}

void topologicalSort(int graph[V][V]){
    int visited[V]={0},stack[V],top=-1;
    for(int i=0;i<V;i++)
        if(!visited[i])
            dfs(i,visited,stack,&top,graph);
    printf("Topological Order: ");
    while(top>=0)
        printf("%d ",stack[top--]);
    printf("\n");
}

int main(){
    int graph[V][V]={
        {0,1,1,0,0,0},
        {0,0,0,1,1,0},
        {0,0,0,1,0,0},
        {0,0,0,0,0,1},
        {0,0,0,0,0,1},
        {0,0,0,0,0,0}
    };
    topologicalSort(graph);
    return 0;
}
