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

    if(sock_desc == -1)
        printf("Error in socket creation!");

    /* Server details */
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = htons(3003);

    /* Connect */
    k = connect(sock_desc,
                (struct sockaddr *)&client,
                sizeof(client));

    if(k == -1)
        printf("Error in connecting!");

    /* Get filename */
    printf("Enter filename: ");

    scanf("%s", buf);

    /* Send filename */
    k = send(sock_desc, buf, 100, 0);

    if(k == -1)
        printf("Error in sending");

    printf("\nFile content:\n");

    /* Receive file */
    while(recv(sock_desc, buf, 100, 0) > 0){

        printf("%s", buf);
    }

    close(sock_desc);

    return 0;
}
