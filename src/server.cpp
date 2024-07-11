#include <iostream>
#include <csignal>
#include "server.h"

std::atomic<bool> Server::running{true};

Server::Server(int port) {
 this->port = port;
 this->address.sin_family = AF_INET;
 this->address.sin_addr.s_addr = INADDR_ANY;
 this->address.sin_port = htons(port);

 if ((this->server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
	std::cerr << "Socket failed" << std::endl;
	exit(EXIT_FAILURE);
 }

 if (bind(this->server_fd, (struct sockaddr *) &this->address, sizeof(this->address)) < 0) {
	std::cerr << "Bind failed" << std::endl;
	exit(EXIT_FAILURE);
 }

 std::signal(SIGINT, Server::handleSignal);
}

Server::~Server() {
 close(server_fd);

 for (std::thread &t: threads) {
	if (t.joinable()) {
	 t.join();
	}
 }
}

void Server::start() {
 if (listen(this->server_fd, 3) < 0) {
	std::cerr << "Listen failed" << std::endl;
	exit(EXIT_FAILURE);
 }

 std::cout << "Server started on port " << this->port << std::endl;

 while (running) {
	int client_socket;
	if ((client_socket = accept(this->server_fd, (struct sockaddr *) &this->address, (socklen_t *) &this->address_len)) <
			0) {
	 std::cerr << "Accept failed" << std::endl;
	 exit(EXIT_FAILURE);
	}

	std::lock_guard<std::mutex> lock(mtx);

	threads.emplace_back(&Server::handle, this, client_socket);
 }
 for (std::thread &t: threads)
	if (t.joinable())
	 t.join();
 close(server_fd);
}

void Server::handle(int client_socket) {
 char buffer[1024] = {0};

 while ((value_read = read(client_socket, buffer, 1024)) > 0) {
	buffer[value_read] = '\0';
	std::cout << "Received: " << buffer << std::endl;
	send(client_socket, buffer, value_read, 0);
 }

 close(client_socket);
}

void Server::handleSignal(int signal) {
 if (signal == SIGINT || signal == SIGTERM) {
	std::cout << "Signal received. Shutting down server..." << std::endl;
	running = false;
	exit(EXIT_SUCCESS);
 }
}