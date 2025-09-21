// # include<stdio.h>
// #include<limits.h>
// #include<stdbool.h>

// # define Max_Vertices 100
// # define INF 10000

// int minDistance(int dist[], bool sptSet[], int vertices){

//     int min = INT_MAX, minIndex;
//     for(int v=0;v<vertices;v++){
//         if(!sptSet[v]&& dist[v]<min){
//             min = dist[v];
//             minIndex =v;
//         }
//     }
//     return minIndex;
// }
// void printSolution(int parent[], int j){
//     if(parent[j]==-1){
//         printf("%d",j+1);
//         return;
//     }
//     printSolution(parent,parent[j]);

//     printf("->%d",j+1);
    
// }
// void dijkastra(int graph[Max_Vertices][Max_Vertices],int src,int V){
//     int dist[Max_Vertices];
//     int sptSec[Max_Vertices];
//     int parent[Max_Vertices];

//     for(int i=0;i<V;i++){
//         dist[i]=INF;
//         sptSec[i]=false;
//         parent[i]=-1;
//     }
//     dist [src]=0;
//     for(int count=0;count<V;count++){
//         int u =minDistance(dist,sptSec,V);
//         if(u==-1){
//             break;
//         }
//         sptSec[u]=true;
//         for(int v=0;v<V;v++){
//             if(!sptSec[v]&& graph[u][v]){
//             }
//         }
//     }
// }


#include <stdio.h>
#include <limits.h>

#define V 9

int minDistance(int dist[], int sptSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v], min_index = v;
        }
    }
    return min_index;
}

void dijkstra(int graph[V][V], int src) {
    int dist[V];
    int sptSet[V];
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }
    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = 1;
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    for (int i = 0; i < V; i++) {
        printf("Vertex %d - Distance from source %d: %d\n", i, src, dist[i]);
    }
}

int main() {
    int graph[V][V];
    int src;

    printf("Enter the adjacency matrix (9x9) where 0 means no edge:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter the source vertex (0 to 8): ");
    scanf("%d", &src);

    if (src < 0 || src >= V) {
        printf("Invalid source vertex.\n");
        return 1;
    }

    dijkstra(graph, src);

    return 0;
}
