#ifndef WEBSERVER_HTTP_H
#define WEBSERVER_HTTP_H

#include <map>
#include <string>
#include <vector>

struct Request {
  std::string method;
  std::string path;
  std::string version;
  std::map<std::string, std::string> headers;
  std::string body;
  std::map<std::string, std::string> params;
  std::string other;
};
struct Response {
  std::string version;
  int status_code;
  std::string status_message;
  std::map<std::string, std::string> headers;
  std::string body;
  std::string other;
};

class Http {
 public:
  static constexpr auto default_http_response =
      "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 0\r\n";

  static std::string test_response(const std::string &body = "");

  static Request parseRequest(const std::string &request);

  static std::vector<std::string> split(const std::string &str, char delim);
};

#endif  // WEBSERVER_HTTP_H
