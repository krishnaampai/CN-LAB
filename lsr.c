#include <stdio.h>

int main(){
	int n,cost[10][10],distance[10];
	int prev[10],src,visited[10],count,next;
	
	printf("Enter no. of nodes: ");
	scanf("%d",&n);
	printf("Enter cost matrix:\n");
	for(int i =0;i<n;i++){
		for(int j =0;j<n;j++){
			scanf("%d",&cost[i][j]); //999 for infinity
		}
	}
	printf ("Enter source node: ");
	scanf("%d",&src);
	
	for(int i =0;i<n;i++){
		distance[i] = cost[src][i];
		visited[i] = 0;
		prev[i] = src;
	}
	visited[src] = 1;
	count = 1;
	while(count < n-1){
		int minDistance = 999;
		for(int i =0;i < n; i++){
			if(distance[i]<minDistance && !visited[i]){
				minDistance = distance[i]; 
				next = i; 
			}
		}
		visited[next] = 1;
		for(int i =0;i<n;i++){
			if(!visited[i]){
				if(minDistance + cost[next][i] < distance[i]){
					distance[i]=minDistance+cost[next][i];
					prev[i] = next;
				}
			}
		}
		count++;	
	}
	for (int i =0;i<n;i++){
		if(i!=src){
			printf("\nDistance to node %d = %d",i,distance[i]);
			printf("\nPath = %d",i);
			int j=i;
			while(j!=src){
				j = prev[j];
				printf(" <- %d",j);
			}
			printf("\n");
		}
	}
	return 0;
}
