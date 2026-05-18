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

    int sock_desc, temp_sock_desc;

    struct sockaddr_in server, client;

    // Create socket
    sock_desc = socket(AF_INET, SOCK_STREAM, 0);

    if(sock_desc == -1)
        printf("Error in socket creation");

    // Server configuration
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(2500);

    // Bind
    k = bind(sock_desc,
             (struct sockaddr *)&server,
             sizeof(server));

    if(k == -1)
        printf("Error in binding");

    // Listen
    listen(sock_desc, 5);

    len = sizeof(client);

    // Accept connection
    temp_sock_desc =
        accept(sock_desc,
               (struct sockaddr *)&client,
               &len);

    printf("Server waiting...\n");

    // Greeting
    recv(temp_sock_desc, buf, 100, 0);

    printf("Message from client: %s\n", buf);

    strcpy(buf, "220 SMTP Ready");

    send(temp_sock_desc, buf, 100, 0);

    // HELO
    recv(temp_sock_desc, buf, 100, 0);

    printf("%s\n", buf);

    strcpy(buf, "250 OK");

    send(temp_sock_desc, buf, 100, 0);

    // MAIL FROM
    recv(temp_sock_desc, buf, 100, 0);

    printf("%s\n", buf);

    strcpy(buf, "250 OK");

    send(temp_sock_desc, buf, 100, 0);

    // RCPT TO
    recv(temp_sock_desc, buf, 100, 0);

    printf("%s\n", buf);

    strcpy(buf, "250 OK");

    send(temp_sock_desc, buf, 100, 0);

    // DATA
    recv(temp_sock_desc, buf, 100, 0);

    printf("%s\n", buf);

    strcpy(buf, "354 Start Mail Input");

    send(temp_sock_desc, buf, 100, 0);

    // Mail body
    recv(temp_sock_desc, msg, 100, 0);

    printf("Mail body received: %s\n", msg);

    // QUIT
    recv(temp_sock_desc, buf, 100, 0);

    strcpy(buf, "221 Closing Connection");

    send(temp_sock_desc, buf, 100, 0);

    close(temp_sock_desc);
    close(sock_desc);

    return 0;
}
