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

    sock_desc = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_desc == -1)
        printf("Error in socket creation!");

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = htons(2000);

    printf("Enter data to be send: ");
    fgets(buf, 100, stdin);

    k = sendto(sock_desc, buf, 100, 0, (struct sockaddr *)&client, sizeof(client));
    if (k == -1)
        printf("Error in sending!");

    close(sock_desc);

    return 0;
}
