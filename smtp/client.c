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

    struct sockaddr_in server;

    // Create socket
    sock_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (sock_desc == -1)
        printf("Error in socket creation");

    // Server configuration
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(2500);

    // Connect to server
    k = connect(sock_desc,
                (struct sockaddr *)&server,
                sizeof(server));

    if(k == -1)
        printf("Error in connection");

    /* Initial message */
    strcpy(buf, "hi");

    send(sock_desc, buf, 100, 0);

    recv(sock_desc, buf, 100, 0);

    printf("Server: %s\n", buf);

    /* HELO */
    strcpy(buf, "HELO 127.0.0.1");

    send(sock_desc, buf, 100, 0);

    recv(sock_desc, buf, 100, 0);

    printf("Server: %s\n", buf);

    /* MAIL FROM */
    printf("Enter FROM address: ");

    scanf("%s", mail_f);

    strcpy(buf, "MAIL FROM ");

    strcat(buf, mail_f);

    send(sock_desc, buf, 100, 0);

    recv(sock_desc, buf, 100, 0);

    printf("Server: %s\n", buf);

    /* RCPT TO */
    printf("Enter TO address: ");

    scanf("%s", mail_to);

    strcpy(buf, "RCPT TO ");

    strcat(buf, mail_to);

    send(sock_desc, buf, 100, 0);

    recv(sock_desc, buf, 100, 0);

    printf("Server: %s\n", buf);

    /* DATA */
    strcpy(buf, "DATA");

    send(sock_desc, buf, 100, 0);

    recv(sock_desc, buf, 100, 0);

    printf("Server: %s\n", buf);

    /* Mail body */
    printf("Enter mail body ($ to end): ");

    getchar();

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

    send(sock_desc, msg, 100, 0);

    /* QUIT */
    strcpy(buf, "QUIT");

    send(sock_desc, buf, 100, 0);

    recv(sock_desc, buf, 100, 0);

    printf("Server: %s\n", buf);

    printf("Connection closed\n");

    close(sock_desc);

    return 0;
}
