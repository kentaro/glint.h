#include <arpa/inet.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

static int interrupted = 0;
void sigterm_action(int signum) {
    interrupted = 1;
    return;
}

int main(int argc, char **argv) {
  int port = 0;
  int sock;
  char *err = "";
  int conn;
  struct sockaddr_storage client;
  unsigned int client_size = sizeof(client);

  if (argc > 1) {
    port = atoi(argv[1]);
  }
  if (port == 0) {
    port = 12345;
  }

  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_port = (in_port_t)htons(port);
  server.sin_addr.s_addr = htonl(INADDR_ANY);

  if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    err = "failed to create a socket";
    goto ERROR;
  }
  if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
    err = "failed to bind";
    goto ERROR;
  }
  if (listen(sock, 1) < 0) {
    err = "failed to listen";
    goto ERROR;
  }

  struct sigaction action;
  action.sa_handler = sigterm_action;
  action.sa_flags = SA_RESETHAND;

  while(interrupted == 0) {
    if ((conn = accept(sock, (struct sockaddr *)&client, &client_size)) < 0) {
      err = "failed to accept";
      goto ERROR;
    }
  }

  if (sigaction(SIGTERM, &action, NULL) != 0) {
    close(sock);
    err = "terminated by SIGTERM";
    goto ERROR;
  }

ERROR:
  fprintf(stderr, "%s\n", err);
  exit(1);
}