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
    socklen_t len;

    FILE *fp;

    int sock_desc, temp_sock_desc;

    struct sockaddr_in server, client;

    /* Create socket */
    sock_desc = socket(AF_INET, SOCK_STREAM, 0);

    if(sock_desc == -1)
        printf("Error in socket creation");

    /* Server configuration */
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(3003);

    /* Bind */
    k = bind(sock_desc,
             (struct sockaddr *)&server,
             sizeof(server));

    if(k == -1)
        printf("Error in binding");

    /* Listen */
    k = listen(sock_desc, 5);

    if(k == -1)
        printf("Error in listening");

    len = sizeof(client);

    /* Accept connection */
    temp_sock_desc =
        accept(sock_desc,
               (struct sockaddr *)&client,
               &len);

    if(temp_sock_desc == -1)
        printf("Error in temporary socket creation");

    /* Receive filename */
    k = recv(temp_sock_desc, buf, 100, 0);

    if(k == -1)
        printf("Error in receiving");

    printf("File requested: %s\n", buf);

    /* Open file */
    fp = fopen(buf, "r");

    if(fp == NULL){

        strcpy(buf, "File not found");

        send(temp_sock_desc, buf, 100, 0);
    }

    else{

        while(fgets(buf, 100, fp) != NULL){

            send(temp_sock_desc, buf, 100, 0);
        }

        fclose(fp);

        printf("File sent successfully\n");
    }

    close(temp_sock_desc);
    close(sock_desc);

    return 0;
}
