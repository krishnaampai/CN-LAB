#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char buf[100];
    int k;
    int sock_desc;

    struct sockaddr_in client;

    /* Create socket */
    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_desc == -1)
        printf("Error in socket creation!");

    /* Server details */
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = htons(3003);

    /* Connect to server */
    k = connect(sock_desc, (struct sockaddr *)&client, sizeof(client));
    if (k == -1)
        printf("Error in connecting to server!");

    printf("Enter data to be send: ");
    fgets(buf, 100, stdin);

    /* Send data */
    k = send(sock_desc, buf, 100, 0);
    if (k == -1)
        printf("Error in sending!");

    close(sock_desc);

    return 0;
}
