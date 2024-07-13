//
// Created by noobscience on 7/11/24.
//

#ifndef WEBSERVER_SERVER_H
#define WEBSERVER_SERVER_H

#include <netinet/in.h>
#include <sys/socket.h>

#include <mutex>
#include <thread>
#include <vector>

// Just for testing sake
#include "src/http.h"

class Server {
 private:
  int port{};
  sockaddr_in address{};
  int server_fd{};
  int new_socket{};
  size_t value_read{};
  int address_len = sizeof address;
  std::vector<std::thread> threads;
  std::mutex mtx;
  Http http;

 public:
  explicit Server(int port);

  void start();

  void handle(int client_socket);

  ~Server();
};

#endif  // WEBSERVER_SERVER_H
