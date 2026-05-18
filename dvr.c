#include <stdio.h>

int main(){

	int cost[10][10],dist[10][10],next[10][10];
	int n;	
	
	printf("Enter no. of routers: ");
	scanf("%d",&n);
	
	printf("enter cost matrix:(enter 999 for inifinity) \n");
	for(int i =0;i<n;i++){
		for(int j =0;j<n;j++){
			scanf("%d",&cost[i][j]);
			dist[i][j] = cost[i][j];
			next[i][j] = j;
		}
	}
	
	int shorter_exists = 1;
	while(shorter_exists){
		shorter_exists =0;
		for(int i =0;i<n;i++){
			for(int j =0;j<n;j++){
				for(int k=0;k<n;k++){
					if(dist[i][j] > dist[i][k] + dist[k][j]){
						dist[i][j] =dist[i][k] + dist[k][j];
						next[i][j] = next[i][k];
						shorter_exists =1;
					}
				}
			}
		}
		
	}
	
	//dispaly
	for(int i =0;i<n;i++){
		printf("\nRouter %d\n",i+1);
		for(int j =0;j<n;j++){
			printf("Distance to router %d is %d via %d\n",j+1,dist[i][j],next[i][j] +1);
		}
		printf("\n");
	}
	return 0;
	
	
}
