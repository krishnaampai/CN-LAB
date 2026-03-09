#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
    char buf[100], msg[100];
    int k;
    socklen_t len;

    int sock_desc;
    struct sockaddr_in server, client;

    sock_desc = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_desc == -1)
        printf("Error in socket creation");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(2500);   // fixed port

    k = bind(sock_desc, (struct sockaddr *)&server, sizeof(server));
    if (k == -1)
        printf("Error in binding");

    len = sizeof(client);

    printf("Server waiting...\n");

    /* Greeting */
    k = recvfrom(sock_desc, buf, 100, 0, (struct sockaddr *)&client, &len);
    printf("Message from client: %s\n", buf);

    strcpy(buf, "220 SMTP Ready");
    sendto(sock_desc, buf, 100, 0, (struct sockaddr *)&client, sizeof(client));

    /* HELO */
    recvfrom(sock_desc, buf, 100, 0, (struct sockaddr *)&client, &len);
    printf("%s\n", buf);

    strcpy(buf, "250 OK");
    sendto(sock_desc, buf, 100, 0, (struct sockaddr *)&client, sizeof(client));

    /* MAIL FROM */
    recvfrom(sock_desc, buf, 100, 0, (struct sockaddr *)&client, &len);
    printf("%s\n", buf);

    strcpy(buf, "250 OK");
    sendto(sock_desc, buf, 100, 0, (struct sockaddr *)&client, sizeof(client));

    /* RCPT TO */
    recvfrom(sock_desc, buf, 100, 0, (struct sockaddr *)&client, &len);
    printf("%s\n", buf);

    strcpy(buf, "250 OK");
    sendto(sock_desc, buf, 100, 0, (struct sockaddr *)&client, sizeof(client));

    /* DATA */
    recvfrom(sock_desc, buf, 100, 0, (struct sockaddr *)&client, &len);
    printf("%s\n", buf);

    strcpy(buf, "354 Start Mail Input");
    sendto(sock_desc, buf, 100, 0, (struct sockaddr *)&client, sizeof(client));

    /* Mail body */
    recvfrom(sock_desc, msg, 100, 0, (struct sockaddr *)&client, &len);
    printf("Mail body received: %s\n", msg);

    /* QUIT */
    recvfrom(sock_desc, buf, 100, 0, (struct sockaddr *)&client, &len);

    strcpy(buf, "221 Closing Connection");
    sendto(sock_desc, buf, 100, 0, (struct sockaddr *)&client, sizeof(client));

    close(sock_desc);
    return 0;
}
