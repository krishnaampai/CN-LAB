#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>

#define WINDOW_SIZE 4

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
    char buf[1024];

    int sock_desc;

    struct sockaddr_in server;

    socklen_t len;

    int base = 0;
    int next = 0;

    Frame frames[100];

    Frame frame_recv;

    sock_desc = socket(AF_INET, SOCK_DGRAM, 0);

    struct timeval tv;

    tv.tv_sec = 3;
    tv.tv_usec = 0;

    setsockopt(sock_desc, SOL_SOCKET, SO_RCVTIMEO,
               &tv, sizeof(tv));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(2000);

    while (1)
    {
        while (next < base + WINDOW_SIZE)
        {
            frames[next].sq_no = next;

            printf("Enter data: ");
            scanf("%s", buf);

            strcpy(frames[next].packet.data, buf);

            sendto(sock_desc, &frames[next], sizeof(Frame), 0,
                   (struct sockaddr *)&server, sizeof(server));

            printf("[+] Frame %d Sent\n", next);

            next++;
        }

        len = sizeof(server);

        int n = recvfrom(sock_desc, &frame_recv, sizeof(Frame), 0,
                         (struct sockaddr *)&server, &len);

        if (n > 0)
        {
            printf("[+] ACK %d Received\n",
                   frame_recv.ack);

            base = frame_recv.ack;
        }
        else
        {
            printf("[-] Timeout\n");

            printf("[+] Resending Frames...\n");

            for (int i = base; i < next; i++)
            {
                sendto(sock_desc, &frames[i], sizeof(Frame), 0,
                       (struct sockaddr *)&server, sizeof(server));

                printf("[+] Frame %d Resent\n", i);
            }
        }
    }

    close(sock_desc);

    return 0;
}
