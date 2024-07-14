#ifndef WEBSERVER_HTTP_H
#define WEBSERVER_HTTP_H

#include <map>
#include <string>

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

  Response(int status_code, const std::string &body = "");
  std::string to_string();
};

class Http {
 public:
  static constexpr auto default_http_response =
      "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 0\r\n";

  static std::string test_response(const std::string &body = "");

  static Request build_request(const std::string &request);
  static Response build_response(int status_code, const std::string &body = "");
};

#endif  // WEBSERVER_HTTP_H
