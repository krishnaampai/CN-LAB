#include <stdio.h>

int main(){

    int n, src, next_hop;
    int cost[10][10], visited[10];
    int distance[10], next[10];

    printf("Enter no. of nodes: ");
    scanf("%d",&n);

    printf("Enter cost matrix:(enter 999 for infinity)\n");

    for(int i =0; i<n; i++){
        for(int j =0; j<n; j++){

            scanf("%d",&cost[i][j]);
        }
    }

    printf("Enter src: ");
    scanf("%d",&src);

    // initialization
    for(int i =0; i<n; i++){

        distance[i] = cost[src][i];
        visited[i] =0;

        if(i != src && distance[i] != 999)
            next[i] = i;

        else
            next[i] = -1;
    }

    visited[src] =1;

    int count =1;

    while(count < n-1){

        int minDistance = 999;

        next_hop = -1;

        // find nearest node
        for(int i =0; i<n; i++){

            if(!visited[i] &&
               distance[i] < minDistance){

                minDistance  = distance[i];
                next_hop = i;
            }
        }

        if(next_hop == -1){
            break;
        }

        visited[next_hop] = 1;

        // update distances
        for(int i =0; i<n; i++){

            if(!visited[i] &&
               cost[next_hop][i] != 999 &&
               distance[i] >
               distance[next_hop] + cost[next_hop][i]){

                distance[i] =
                    distance[next_hop] + cost[next_hop][i];

                next[i] = next[next_hop];
            }
        }

        count++;
    }

    // display
    printf("\nRouting table of %d\n",src);

    printf("Router\tDistance\tNext Hop\n");

    for(int i =0; i<n; i++){

        if(distance[i] == 999){

            printf("%d\t999\t\t-\n",i);
        }

        else{

            printf("%d\t%d\t\t%d\n",
                   i,
                   distance[i],
                   next[i]);
        }
    }

    return 0;
}
