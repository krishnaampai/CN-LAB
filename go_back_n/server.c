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

    int frame_id = 0;

    Frame frame_recv, frame_send;

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

        if (frame_recv.sq_no == frame_id)
        {
            printf("[+] Frame Received: %s\n",
                   frame_recv.packet.data);

            frame_send.ack = frame_id + 1;

            int x = rand() % 2;

            if (x == 0)
            {
                sendto(sock_desc, &frame_send, sizeof(Frame), 0,
                       (struct sockaddr *)&client, len);

                printf("[+] ACK Sent\n");

                frame_id++;
            }
            else
            {
                printf("[-] ACK Lost\n");
            }
        }
        else
        {
            printf("[-] Discarded Frame\n");
        }
    }

    close(sock_desc);

    return 0;
}
