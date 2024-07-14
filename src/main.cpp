#include <string>

#include "server.h"

int main(int argc, char **argv) {
  int port;
  if (argc == 2) {
    port = std::stoi(argv[1]);
  } else {
    port = 5000;
  }

  Server server(port, "/home/noobscience/Projects/diy/webserver/test");
  server.start();
}
