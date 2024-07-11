#ifndef WEBSERVER_HTTP_H
#define WEBSERVER_HTTP_H

#include <string>
#include <map>

class Http {
		struct Request{
				std::string method;
				std::string path;
				std::string version;
				std::map<std::string, std::string> headers;
				std::string body;
				std::map<std::string, std::string> params;
				std::string other;
		};

		struct Response{
				std::string version;
				int status_code;
				std::string status_message;
				std::map<std::string, std::string> headers;
				std::string body;
				std::string other;
		};
};

#endif //WEBSERVER_HTTP_H
