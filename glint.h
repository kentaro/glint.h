#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

typedef struct {
  uint16_t port;
  char *cmd;
  char **args;
} glint;

glint *glint_new() {
  glint *self = (glint *)calloc(sizeof(glint), 1);
  return self;
}

void glint_free(glint *self) { free(self); }

uint16_t glint_empty_port() {
  int sock;

  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_port = htons(0);
  server.sin_addr.s_addr = htonl(INADDR_ANY);

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