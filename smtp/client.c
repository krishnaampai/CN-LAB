#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
    char buf[100], msg[100];
    char mail_f[50], mail_to[50];
    int k, t = 0;
    char c;

    int sock_desc;
    socklen_t len;

    struct sockaddr_in server;

    sock_desc = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_desc == -1)
        printf("Error in socket creation");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(2500);   // same port as server

    len = sizeof(server);

    /* Initial message */
    strcpy(buf, "hi");

    k = sendto(sock_desc, buf, 100, 0, (struct sockaddr *)&server, sizeof(server));
    if (k == -1)
        printf("Error in sending");

    k = recvfrom(sock_desc, buf, 100, 0, (struct sockaddr *)&server, &len);
    printf("Server: %s\n", buf);

    /* HELO */
    strcpy(buf, "HELO 127.0.0.1");

    sendto(sock_desc, buf, 100, 0, (struct sockaddr *)&server, sizeof(server));

    recvfrom(sock_desc, buf, 100, 0, (struct sockaddr *)&server, &len);
    printf("Server: %s\n", buf);

    /* MAIL FROM */
    printf("Enter FROM address: ");
    scanf("%s", mail_f);

    strcpy(buf, "MAIL FROM ");
    strcat(buf, mail_f);

    sendto(sock_desc, buf, 100, 0, (struct sockaddr *)&server, sizeof(server));

    recvfrom(sock_desc, buf, 100, 0, (struct sockaddr *)&server, &len);
    printf("Server: %s\n", buf);

    /* RCPT TO */
    printf("Enter TO address: ");
    scanf("%s", mail_to);

    strcpy(buf, "RCPT TO ");
    strcat(buf, mail_to);

    sendto(sock_desc, buf, 100, 0, (struct sockaddr *)&server, sizeof(server));

    recvfrom(sock_desc, buf, 100, 0, (struct sockaddr *)&server, &len);
    printf("Server: %s\n", buf);

    /* DATA */
    strcpy(buf, "DATA");

    sendto(sock_desc, buf, 100, 0, (struct sockaddr *)&server, sizeof(server));

    recvfrom(sock_desc, buf, 100, 0, (struct sockaddr *)&server, &len);
    printf("Server: %s\n", buf);

    /* Mail body */
    printf("Enter mail body ($ to end): ");

    while (1)
    {
        c = getchar();
        if (c == '$')
        {
            msg[t] = '\0';
            break;
        }
        msg[t++] = c;
    }

    sendto(sock_desc, msg, 100, 0, (struct sockaddr *)&server, sizeof(server));

    /* QUIT */
    strcpy(buf, "QUIT");

    sendto(sock_desc, buf, 100, 0, (struct sockaddr *)&server, sizeof(server));

    recvfrom(sock_desc, buf, 100, 0, (struct sockaddr *)&server, &len);

    printf("Server: %s\n", buf);
    printf("Connection closed\n");

    close(sock_desc);

    return 0;
}
