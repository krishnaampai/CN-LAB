#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>

typedef struct packet
{
    char data[1024];
} Packet;

typedef struct frame
{
    int frame_kind;
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

    int frame_id = 0;

    Frame frame_send, frame_recv;

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
    	  len = sizeof(server);
        frame_send.sq_no = frame_id;

        printf("Enter data: ");
        scanf("%s", buf);

        strcpy(frame_send.packet.data, buf);

        sendto(sock_desc, &frame_send, sizeof(Frame), 0,
               (struct sockaddr *)&server, len);

        printf("[+] Frame Sent\n");

       

        int n = recvfrom(sock_desc, &frame_recv, sizeof(Frame), 0,
                         (struct sockaddr *)&server, &len);

        if (n > 0 && frame_recv.ack == frame_id + 1)
        {
            printf("[+] ACK Received\n");

            frame_id++;
        }
        else
        {
            printf("[-] Timeout... Resending Frame\n");
        }
    }

    close(sock_desc);

    return 0;
}
