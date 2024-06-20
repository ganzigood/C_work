#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

#include <sys/socket.h>
#include <sys/un.h>

#define MAX_BUF 2048

typedef struct __server_context{
    int server_addr;
}server_context;

/*
typedef struct __send_msg {
    char* servermsg;
    char* clientmsg;
}sendmsg;
*/


void stream_client_loop(int conn_sd) {
    
    server_context context;
    context.server_addr = conn_sd;
    
    char buffer[MAX_BUF];
    while (1) {
        int n = read(context.server_addr, buffer, sizeof(buffer));
        if (n <=0){
            fprintf(stderr,"read error\n");
            break;
        }
        write(STDOUT_FILENO, buffer, n);    
        
        
        scanf(" %s", buffer);

        int ret = write(context.server_addr, buffer, strlen(buffer));
        if (ret == -1) {
            fprintf(stderr, "Error while writing! %s\n",
            strerror(errno));
            break;
        }
    }
    printf("Bye.\n");
}

int main(int argc, char** argv) {
    char sock_file[] = "/tmp/datastruct_project.sock";

  // 소켓 객체 만들기

    int conn_sd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (conn_sd == -1) {
        fprintf(stderr, "Could not create socket: %s\n",
        strerror(errno));
        exit(1);
    }

  // 서버프로세스에 접속하는 과정

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, sock_file, sizeof(addr.sun_path) - 1);

    int result = connect(conn_sd,
                (struct sockaddr*)&addr, sizeof(addr));
    if (result == -1) {
        close(conn_sd);
        fprintf(stderr, "Could no connect: %s\n", strerror(errno));
        exit(1);
    }

    stream_client_loop(conn_sd);

    return 0;
}
