#include<stdio.h>
#include<stdlib.h>

int compare(const void *a,const void *b){
        return(*(int*)b-*(int*)a);
}

int minCoinsGreedy(int coins[],int n, int amount){
    qsort(coins,n,sizeof(int),compare);
    int count =0;
    printf("Coins used to make amount %d: ", amount);

    for (int i=0;i<n;i++){
        while(amount>=coins[i]){
            amount-=coins[i];
            count++;
            printf("%d ", coins[i]);
        }
        if(amount==0){
            break;
        }
        
    }
    printf("\n");
    return count;
}

int main(){
    int coins[]={1,2,5,10,20,50,100,500,1000};
    int n = sizeof(coins)/sizeof(coins[0]);
    int amount =78;
    printf("Minimum no. of coins required for amount %d:%d\n",amount,minCoinsGreedy(coins,n,amount));
    amount =39;
    printf("Minimum no. of coins required for amount %d:%d\n",amount,minCoinsGreedy(coins,n,amount));
    return 0;
}