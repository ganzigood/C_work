#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>

#include <sys/socket.h>
#include <sys/un.h>

#include "List_Stack.c"

#define MAX_BUF 2048


typedef struct __client_context{
    int client_addr;
}client_context;

void* stack_service(client_context context) {
    int ret;
    char buffer[MAX_BUF]; 
    char* buf;
    ListStack mystack;
    InitListStack(&mystack);

    while(1){
        
        int fd = open("/home/sodami/Documents/Work_Space/C_work/project01_DataStructure_IPC/stack_service_info.txt", O_RDONLY);
        if (fd <0){
            fprintf(stderr,"open error\n");
            exit(1);
        }
        int n = read(fd, buffer, sizeof(buffer));
        if (n <=0){
            fprintf(stderr,"read error\n");
            exit(1);
        }
        write(context.client_addr,buffer,n);

        ret = read(context.client_addr, buffer, strlen(buffer));
        if(ret == -1 || ret ==0) {
            break;
        }
        
        printf("\n"); 
        write(STDOUT_FILENO, buffer, ret);
        
        switch(buffer[0]) {
            case '1' :
                strcpy(buffer,"스택에 입력할 정수형 데이터를 입력하세요 : ");
                write(context.client_addr,buffer,strlen(buffer));

                ret = read(context.client_addr, buffer, strlen(buffer) );
                
                Push(&mystack,buf);
                
                break;
            case '2' :
                buf = Peek(&mystack);
                
                fprintf(stdout,"%s",buf);

                write(context.client_addr, buf, strlen(buf));

                break;
            case '3' :
                break;
            default :
                return NULL;
                break;
        }    
    }
    return NULL;
}


void* client_service(client_context context) {
    int ret;
    char buffer[MAX_BUF];
    
    while(1) {
        
        int fd = open("/home/sodami/Documents/Work_Space/C_work/project01_DataStructure_IPC/client_service_info.txt", O_RDONLY);
        if (fd <0){
            fprintf(stderr,"open error\n");
            exit(1);
        }
        int n = read(fd, buffer, sizeof(buffer));
        if (n <=0){
            fprintf(stderr,"read error\n");
            exit(1);
        }
        
    
        
        write(context.client_addr,buffer,n);

        int ret = read(context.client_addr, buffer, strlen(buffer));
        if(ret == -1 || ret ==0) {
            break;
        }
        
        printf("\n"); 
        write(STDOUT_FILENO, buffer, ret);


        
        switch(buffer[0]) {
            case '1' :
                stack_service(context);
                break;
            case '2' :
                break;
            case '3' :
                break;
            case '4' :
                break;
            default :
                close(context.client_addr);
                break;
        }    
    }
    return NULL;
}


void* client_handler(void *arg) {

    client_context context;
    context.client_addr = *((int*)arg);

    free((int*)arg);
    
    client_service(context);

    return NULL;
}


void accept_forever(int server_sd) {
  while (1) {
    int client_sd = accept(server_sd, NULL, NULL);
    if (client_sd == -1) {
      close(server_sd);
      fprintf(stderr, "Could not accept the client: %s\n",
              strerror(errno));
      exit(1);
    }
    pthread_t client_handler_thread;
    int* arg = (int *)malloc(sizeof(int));
    *arg = client_sd;
    int result = pthread_create(&client_handler_thread, NULL,
            &client_handler, arg);
    if (result) {
      close(client_sd);
      close(server_sd);
      free(arg);
      fprintf(stderr, "Could not start the client handler thread.\n");
      exit(1);
    }
  }
}


int main(int argc, char** argv) {
    char sock_file[] = "/tmp/datastruct_project.sock";

  // 소켓객체 생성
    int server_sd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_sd == -1) {
        fprintf(stderr, "Could not create socket: %s\n",
        strerror(errno));
        exit(1);
    }

  // 소켓 객체를 파일로

  // 기존의 링크를 끊기
    unlink(sock_file);

  // 주소 생성
    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, sock_file, sizeof(addr.sun_path) - 1);

    int result = bind(server_sd,
        (struct sockaddr*)&addr, sizeof(addr));
    if (result == -1) {
        close(server_sd);
        fprintf(stderr, "Could not bind the address: %s\n",
        strerror(errno));
        exit(1);
    }

  // 접속대기
    result = listen(server_sd, 10);
    if (result == -1) {
        close(server_sd);
        fprintf(stderr, "Could not set the backlog: %s\n",
        strerror(errno));
        exit(1);
    }

  // 접속하면 실행
    accept_forever(server_sd);

    return 0;
}
