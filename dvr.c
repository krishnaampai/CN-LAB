#include <stdio.h>

struct router
{
    int cost[20];
    int from[20];
} routingTable[10];

int main()
{
    int costmat[20][20];
    int n, i, j, k;
    int otherShorterPathExists;

    printf("Enter the number of routers : ");
    scanf("%d", &n);

    printf("Enter the cost matrix :\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &costmat[i][j]);

            routingTable[i].cost[j] = costmat[i][j];
            routingTable[i].from[j] = j;
        }
    }

    do
    {
        otherShorterPathExists = 0;

        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                for (k = 0; k < n; k++)
                {
                    if (routingTable[i].cost[j] > costmat[i][k] + routingTable[k].cost[j])
                    {
                        routingTable[i].cost[j] =
                            routingTable[i].cost[k] +
                            routingTable[k].cost[j];

                        routingTable[i].from[j] = k;

                        otherShorterPathExists = 1;
                    }
                }
            }
        }

    } while (otherShorterPathExists != 0);

    for (i = 0; i < n; i++)
    {
        printf("\n\nFor router %d\n", i + 1);

        for (j = 0; j < n; j++)
        {
            printf("Router %d via %d distance %d\n",
                   j + 1,
                   routingTable[i].from[j] + 1,
                   routingTable[i].cost[j]);
        }
    }

    printf("\n");

    return 0;
}
