#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

#define BUF_SIZE 256

int main(int argc, char *argv[])
{
    struct sockaddr_in server, client;
    char str[50], msg[20];

    if (argc != 2)
        printf("Input format not correct");

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
        printf("Error in socket()");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));

    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0)
        printf("Error in bind()\n");

    socklen_t client_len = sizeof(client);

    printf("Server waiting...\n");
    sleep(3);

    /* Receive first message */
    recvfrom(sockfd, str, 100, 0, (struct sockaddr *)&client, &client_len);
    printf("Got message from client: %s\n", str);

    /* Send greeting */
    strcpy(str, "220 127.0.0.1");
    sendto(sockfd, str, sizeof(str), 0, (struct sockaddr *)&client, sizeof(client));

    /* HELO */
    recvfrom(sockfd, str, sizeof(str), 0, (struct sockaddr *)&client, &client_len);
    printf("%s\n", str);

    strcpy(str, "250 ok");
    sendto(sockfd, str, sizeof(str), 0, (struct sockaddr *)&client, sizeof(client));

    /* MAIL FROM */
    recvfrom(sockfd, str, sizeof(str), 0, (struct sockaddr *)&client, &client_len);
    printf("%s\n", str);

    strcpy(str, "250 ok");
    sendto(sockfd, str, sizeof(str), 0, (struct sockaddr *)&client, sizeof(client));

    /* RCPT TO */
    recvfrom(sockfd, str, sizeof(str), 0, (struct sockaddr *)&client, &client_len);
    printf("%s\n", str);

    strcpy(str, "250 ok");
    sendto(sockfd, str, sizeof(str), 0, (struct sockaddr *)&client, sizeof(client));

    /* DATA */
    recvfrom(sockfd, str, sizeof(str), 0, (struct sockaddr *)&client, &client_len);
    printf("%s\n", str);

    strcpy(str, "354 Go ahead");
    sendto(sockfd, str, sizeof(str), 0, (struct sockaddr *)&client, sizeof(client));

    /* Receive mail body */
    recvfrom(sockfd, msg, sizeof(msg), 0, (struct sockaddr *)&client, &client_len);
    printf("Mail body received: %s\n", msg);

    /* QUIT */
    recvfrom(sockfd, str, sizeof(str), 0, (struct sockaddr *)&client, &client_len);

    strcpy(str, "221 OK");
    sendto(sockfd, str, sizeof(str), 0, (struct sockaddr *)&client, sizeof(client));

    close(sockfd);
    return 0;
}
