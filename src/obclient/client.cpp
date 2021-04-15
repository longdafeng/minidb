// __CR__
// Copyright (c) 2021 LongdaFeng All Rights Reserved
//
// This software contains the intellectual property of LongdaFeng
// or is licensed to LongdaFeng from third parties.  Use of this
// software and the intellectual property contained therein is
// expressly limited to the terms and conditions of the License Agreement
// under which it is provided by or on behalf of LongdaFeng.
// __CR__
//
// Created by Longda on 2021
//

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "common/defs.h"

#define MAX_MEM_BUFFER_SIZE 8192
#define PORT_DEFAULT 16880

using namespace common;

int main(int argc, char *argv[]) {
  char *serverHost = (char *)LOCAL_HOST;
  if (argc >= 2) {
    serverHost = argv[1];
  }

  int sockfd, sendbytes;
  // char send[MAXLINE];

  char sendBuf[MAX_MEM_BUFFER_SIZE];
  // char buf[MAXDATASIZE];
  struct hostent *host;
  struct sockaddr_in serv_addr;

  if ((host = gethostbyname(serverHost)) == NULL) {
    perror("gethostbyname");
    exit(1);
  }
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket error \n");
    exit(1);
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT_DEFAULT);
  serv_addr.sin_addr = *((struct in_addr *)host->h_addr);
  bzero(&(serv_addr.sin_zero), 8);

  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) ==
      -1) {
    perror("Failed to connect \n");
    exit(1);
  }

  while (fgets(sendBuf, MAX_MEM_BUFFER_SIZE, stdin) != NULL) {
    if ((sendbytes = send(sockfd, sendBuf, strlen(sendBuf) + 1, 0)) == -1) {
      perror("send error \n");
      exit(1);
    }

    memset(sendBuf, 0, sizeof(sendBuf));

    int len = recv(sockfd, sendBuf, MAX_MEM_BUFFER_SIZE, 0);
    if (len < 0) {
      printf("Close connection");
      break;
    }

    for (int i = 0; i < len; i++) {
      printf("%c", sendBuf[i]);
    }
  }
  close(sockfd);

  return 0;
}
