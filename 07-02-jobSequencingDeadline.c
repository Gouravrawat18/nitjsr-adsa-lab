#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int id;
    int deadline;
    int profit;

}job;
int compareJobs(const void *a,const void *b){
    job *jobA=(job*)a;
    job *jobB=(job*)b;
    return jobB->profit-jobA->profit;
}
void jobsequencing(job jobs[],int n){
    qsort(jobs,n,sizeof(job),comparejobs);

    int maxDeadline=0;
    for(int i=0;i<n;i++){
        if(jobs[i].deadline>maxDeadline)
        maxDeadline=jobs[i].deadline;

    }
    int *slot=(int*)malloc(maxDeadline *sizeof(int));
    for(int i=0;i<maxDeadline;i++)
    slot[i]=-1;

    int totalProfit =0;
    for(int i=0;i<n;i++){
        for(int j=(jobs[i].deadline<maxDeadline?jobs[i].deadline:maxDeadline)-1;j>=0;j--){
            if(slot[j]==-1){
                slot[j]=jobs[i].id;
                totalProfit=jobs[i].profit;
                break;
            }
        }
    }
    printf("schedule jobs:");
    for(int i=0;i<maxDeadline;i++){
        if(slot[i]!=-1){
            printf("%d",slot[i]);
        }
        printf("\n total Profit:%d\n", totalProfit);
        free(slot);
    }
    
}
int main(){
        job jobs[]={{1,2,100},{2,1,19},{3,2,27},{4,1,25}};
        int n=sizeof(jobs)/sizeof(jobs[0]);
        jobsequencing(jobs,n);
        return 0;
    }