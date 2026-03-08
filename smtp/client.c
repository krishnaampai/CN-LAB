#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>

#define BUF_SIZE 256

int main(int argc, char *argv[])
{
    struct sockaddr_in server;
    char str[50] = "hi";
    char mail_f[50], mail_to[50], msg[20];
    char c;
    int t = 0;

    socklen_t l = sizeof(server);

    if (argc != 3)
        printf("Input format not correct");

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
        printf("Error in socket()");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[2]));

    /* Initial message */
    sendto(sockfd, str, sizeof(str), 0, (struct sockaddr *)&server, sizeof(server));

    recvfrom(sockfd, str, sizeof(str), 0, (struct sockaddr *)&server, &l);
    printf("Greeting message: %s\n", str);

    /* HELO */
    strcpy(str, "HELO 127.0.0.1");
    sendto(sockfd, str, sizeof(str), 0, (struct sockaddr *)&server, sizeof(server));

    recvfrom(sockfd, str, sizeof(str), 0, (struct sockaddr *)&server, &l);
    printf("Server: %s\n", str);

    /* MAIL FROM */
    printf("Enter FROM address: ");
    scanf("%s", mail_f);

    strcpy(str, "MAIL FROM ");
    strcat(str, mail_f);

    sendto(sockfd, str, sizeof(str), 0, (struct sockaddr *)&server, sizeof(server));

    recvfrom(sockfd, str, sizeof(str), 0, (struct sockaddr *)&server, &l);

    /* RCPT TO */
    printf("Enter TO address: ");
    scanf("%s", mail_to);

    strcpy(str, "RCPT TO ");
    strcat(str, mail_to);

    sendto(sockfd, str, sizeof(str), 0, (struct sockaddr *)&server, sizeof(server));

    recvfrom(sockfd, str, sizeof(str), 0, (struct sockaddr *)&server, &l);

    /* DATA */
    strcpy(str, "DATA");
    sendto(sockfd, str, sizeof(str), 0, (struct sockaddr *)&server, sizeof(server));

    recvfrom(sockfd, str, sizeof(str), 0, (struct sockaddr *)&server, &l);

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

    sendto(sockfd, msg, sizeof(msg), 0, (struct sockaddr *)&server, sizeof(server));

    /* QUIT */
    strcpy(str, "QUIT");
    sendto(sockfd, str, sizeof(str), 0, (struct sockaddr *)&server, sizeof(server));

    recvfrom(sockfd, str, sizeof(str), 0, (struct sockaddr *)&server, &l);

    printf("Connection closed\n");

    close(sockfd);
    return 0;
}
