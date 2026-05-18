#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

typedef struct packet
{
    char data[1024];
} Packet;

typedef struct frame
{
    int sq_no;
    int ack;
    Packet packet;
} Frame;

int main()
{
    int sock_desc;

    struct sockaddr_in server, client;

    socklen_t len;

    Frame frame_recv, frame_send;

    int received[100] = {0};

    sock_desc = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(2000);

    bind(sock_desc, (struct sockaddr *)&server, sizeof(server));

    srand(time(0));

    printf("Server waiting...\n");

    while (1)
    {
        len = sizeof(client);

        recvfrom(sock_desc, &frame_recv, sizeof(Frame), 0,
                 (struct sockaddr *)&client, &len);

        if (received[frame_recv.sq_no] == 0)
        {
            printf("[+] Frame %d Received: %s\n",
                   frame_recv.sq_no,
                   frame_recv.packet.data);

            received[frame_recv.sq_no] = 1;
        }
        else
        {
            printf("[-] Duplicate Frame %d\n",
                   frame_recv.sq_no);
        }

        int x = rand() % 2;

        if (x == 0)
        {
            frame_send.ack = frame_recv.sq_no;

            sendto(sock_desc, &frame_send, sizeof(Frame), 0,
                   (struct sockaddr *)&client, len);

            printf("[+] ACK %d Sent\n",
                   frame_send.ack);
        }
        else
        {
            printf("[-] ACK Lost\n");
        }
    }

    close(sock_desc);

    return 0;
}
