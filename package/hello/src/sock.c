#include "sock.h"
#include "pb_decode.h"
#include "message.pb.h"
#include "pb.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define PORT 1234
#define MAX_BUF 128

static char* bin2hex(const unsigned char* input, size_t len)
{
    char* result;
    char* hexits = "0123456789ABCDEF";

    if (input == NULL || len <= 0)
        return NULL;

    int resultlength = (len * 3) + 1;

    result = (char*)malloc(resultlength);
    memset(result, 0, resultlength);

    for (size_t i = 0; i < len; i++) {
        result[i * 3] = hexits[input[i] >> 4];
        result[(i * 3) + 1] = hexits[input[i] & 0x0F];
        result[(i * 3) + 2] = ' ';
    }
    return result;
}

static void err_n_die(const char* fmt, ...)
{
    int errno_save;
    va_list valist;

    errno_save = errno;

    va_start(valist, fmt);
    vfprintf(stdout, fmt, valist);
    fprintf(stdout, "\n");
    fflush(stdout);

    if (errno_save != 0) {
        fprintf(stdout, "errno = %d : %s\n", errno_save, strerror(errno_save));
        fprintf(stdout, "\n");
        fflush(stdout);
    }
    va_end(valist);
    exit(1);
}

static void deserializeMessage(Message* message, unsigned char* recvBuf, const unsigned int messageSize)
{
    /* If you want to write multiple messages to a single file or stream, it is up to you
     * to keep track of where one message ends and the next begins. The Protocol Buffer wire
     * format is not self-delimiting, so protocol buffer parsers cannot determine where a
     * message ends on their own. The easiest way to solve this problem is to write the
     * size of each message before you write the message itself. When you read the messages
     * back in, you read the size, then read the bytes into a separate buffer, then parse
     * from that buffer. (If you want to avoid copying bytes to a separate buffer, check
     * out the CodedInputStream class (in both C++ and Java) which can be told to limit
     * reads to a certain number of bytes.)
     * https://developers.google.com/protocol-buffers/docs/techniques
    */

    pb_istream_t stream = pb_istream_from_buffer(recvBuf, messageSize);

    int status = pb_decode(&stream, Message_fields, message);
    if (!status) {
        printf("Decoding failed: %s\n", PB_GET_ERROR(&stream));
    } else {
        printf("Success decoding\n");
        printf("    timestamp: %ld\n", message->timestamp);
        printf("    temperature: %f\n", message->temperature);
        printf("    pressure: %f\n", message->pressure);
        printf("    humidity: %f\n", message->humidity);
    }
    fflush(stdout);
}

int conn()
{
    // look at libiio for better c sockets code
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    unsigned char sendBuff[MAX_BUF];
    unsigned char recvBuff[MAX_BUF];

    if ( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
        err_n_die("Error socket create!");
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    if ( bind(listenfd,(struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        err_n_die("bind error");
    }

    if (listen(listenfd, 10) < 0) {
        err_n_die("connect failed");
    }

    while(1) {
        unsigned int recvSize = 0;
        unsigned int messageSize = 0;
        struct sockaddr_in addr;
        socklen_t addr_len;

        printf("Waiting for connection on port %d\n", PORT);
        fflush(stdout);

        connfd = accept(listenfd, NULL, NULL);
        memset(recvBuff, 0, MAX_BUF);
        while ( (recvSize = read(connfd, recvBuff + recvSize, MAX_BUF - recvSize)) > 0 ) {
            fprintf(stdout, "received: %s; %s recvSize: %d\n", recvBuff, bin2hex(recvBuff, recvSize), recvSize);
            if (recvSize > sizeof(messageSize) && !messageSize) {
                memcpy(&messageSize, recvBuff, sizeof(messageSize));
                fprintf(stdout, "message size: %d\n", messageSize);
                fflush(stdout);
            }

            if (sizeof(messageSize) + messageSize == recvSize) {
                Message message = Message_init_zero;
                deserializeMessage(&message, recvBuff + sizeof(messageSize), messageSize);
                break;
            }
        }

        if (recvSize < 0) {
            err_n_die("read error!");
        }

        snprintf((char*)sendBuff, sizeof(sendBuff), "OK Hello \r\n");
        write(connfd, (char*)sendBuff, strlen((char*)sendBuff));
        close(connfd);
    }
}
