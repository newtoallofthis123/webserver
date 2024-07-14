//
// Created by noobscience on 7/11/24.
//

#include "http.h"

#include <sstream>

std::string Http::test_response(const std::string& body) {
  std::stringstream response_stream;
  response_stream << "HTTP/1.1 200 OK\r\n";
  response_stream << "Content-Type: text/html\r\n";
  response_stream << "Content-Length: " << body.length() << "\r\n";
  response_stream << "Connection: close\r\n\r\n";
  response_stream << body;
  return response_stream.str();
}

Request Http::build_request(const std::string& request) {
  Request req;
  std::istringstream iss(request);
  std::string line;

  // Parse the request line
  if (std::getline(iss, line)) {
    std::istringstream lineStream(line);
    lineStream >> req.method >> req.path >> req.version;
  }

  // Parse headers
  while (std::getline(iss, line) && !line.empty()) {
    auto colonPos = line.find(':');
    if (colonPos != std::string::npos) {
      std::string key = line.substr(0, colonPos);
      std::string value = line.substr(colonPos + 1);

      // Trim leading and trailing whitespace
      key.erase(0, key.find_first_not_of(" \t"));
      key.erase(key.find_last_not_of(" \t") + 1);
      value.erase(0, value.find_first_not_of(" \t"));
      value.erase(value.find_last_not_of(" \t") + 1);

      req.headers[key] = value;
    }
  }

  // Parse body (if any)
  std::string bodyLine;
  while (std::getline(iss, bodyLine)) {
    req.body += bodyLine + "\n";
  }
  if (!req.body.empty()) {
    req.body.pop_back();
  }

  return req;
}