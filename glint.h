#pragma once

#include <arpa/inet.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

typedef void (*glint_callback)(char *port);
typedef struct {
  uint16_t port;
  glint_callback cb;
  pid_t pid;
} glint;

glint *glint_new(glint_callback cb) {
  glint *self = (glint *)calloc(sizeof(glint), 1);
  if (self == NULL) {
    return NULL;
  }

  self->cb = cb;
  return self;
}

uint16_t glint_empty_port() {
  int sock;

  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(0);

  if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    perror("failed to create a socket");
    return 0;
  }
  if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
    perror("failed to bind");
    return 0;
  }

  socklen_t len = sizeof(server);
  if (getsockname(sock, (struct sockaddr *)&server, &len) < 0) {
    perror("failed to get socket name");
    return 0;
  }

  close(sock);
  return (uint16_t)ntohs(server.sin_port);
}

bool glint_start(glint *self) {
  self->port = glint_empty_port();
  if (self->port == 0) {
    return false;
  }

  self->pid = fork();

  if (self->pid == -1) {
    perror("failed to fork a process");
    return false;
  } else if (self->pid == 0) {
    // child process
    char port[6];
    snprintf(port, 6, "%d", self->port);
    self->cb(port);
  } else {
    // parent process
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(self->port);

    // wait the port until connection established
    for (int i = 100; i > 0; i--) {
      int sock;
      if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("failed to create a socket");
        false;
      }

      if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        close(sock);
        usleep(100000);
        continue;
      } else {
        close(sock);
        return true;
      }
    }

    return false;
  }

  return true;
}

void glint_stop(glint *self) {
  int status;

  kill(self->pid, SIGTERM);

  if (waitpid(self->pid, &status, 0) < 0) {
    perror("can not wait a child process");
    exit(1);
  }
  if (WIFSIGNALED(status)) {
    printf("child process exited by %d\n", WTERMSIG(status));
  }
}

void glint_free(glint *self) { free(self); }