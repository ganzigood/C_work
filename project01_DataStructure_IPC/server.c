#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include <sys/socket.h>
#include <sys/un.h>

#define MAX_BUF 2048

typedef struct __client_context{
    int cliend_addr;
}client_context;
/*
typedef struct __send_msg {
    char* servermsg;
    char* clientmsg;
}sendmsg;
*/

void* client_handler(void *arg) {

    client_context context;
    context.cliend_addr = *((int*)arg);

    free((int*)arg);
    
  //  sendmsg message;

    int ret;
    char buffer[MAX_BUF];
    while(1) {
        int ret = read(context.cliend_addr, buffer, MAX_BUF-1);
        if(ret == -1 || ret ==0) {
            break;
        } 
        write(STDOUT_FILENO, buffer, ret);
    }

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

  // ----------- 1. Create socket object ------------------
  int server_sd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (server_sd == -1) {
    fprintf(stderr, "Could not create socket: %s\n",
            strerror(errno));
    exit(1);
  }

  // ----------- 2. Bind the socket file ------------------

  // Delete the previously created socket file if it exists.
  unlink(sock_file);

  // Prepare the address
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

  // ----------- 3. Prepare backlog ------------------
  result = listen(server_sd, 10);
  if (result == -1) {
    close(server_sd);
    fprintf(stderr, "Could not set the backlog: %s\n",
            strerror(errno));
    exit(1);
  }

  // ----------- 4. Start accepting clients ---------
  accept_forever(server_sd);

  return 0;
}
