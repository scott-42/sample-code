//
//  main.cpp
//  server
//
//  Created by Scott Gustafson on 7/1/16.
//  Copyright © 2016 Garlic Software LLC. All rights reserved.
//

// Simple networking code is adapted from the asio sample code for the simple echo tcp server code.
// spawn/echo_server.cpp

#include <iostream>
#include <sstream>
#include <asio/io_service.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/spawn.hpp>
#include <asio/steady_timer.hpp>
#include <asio/write.hpp>
#include <thread>
#include "config.h"
#include "prime.h"

using asio::ip::tcp;

class session : public std::enable_shared_from_this<session> {
private:
	tcp::socket socket;
	asio::steady_timer timer;
	asio::io_service::strand strand;

public:
	explicit session(tcp::socket socket) : socket(std::move(socket)), timer(socket.get_io_service()), strand(socket.get_io_service()) {}
	
	void go() {
		auto self(shared_from_this());
		asio::spawn(strand, [this, self](asio::yield_context yield) {
				try {
					char data[128];
					for (;;) {
						timer.expires_from_now(std::chrono::seconds(10));
						std::size_t n = socket.async_read_some(asio::buffer(data), yield);
						// this is not built to accept an int that is larger than the 32 bit value so this is safe to truncate
						if (n == 128) {
							n = 127;
						}
						data[n] = '\0';
						std::stringstream ss(data);
						unsigned int value = 0;
						ss >> value;
						asio::async_write(socket, asio::buffer(prime::is_prime(value) ? "1" : "0", 1), yield);
					}
				}
				catch (std::exception& e) {
					socket.close();
					timer.cancel();
				}
			});
		
		asio::spawn(strand, [this, self](asio::yield_context yield) {
				while (socket.is_open()) {
					asio::error_code ignored_ec;
					timer.async_wait(yield[ignored_ec]);
					if (timer.expires_from_now() <= std::chrono::seconds(0))
						socket.close();
				}
			});
	}

};

int main(int argc, char* argv[]) {
	try {
		asio::io_service io_service;
		asio::spawn(io_service, [&](asio::yield_context yield) {
				tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), std::atoi(port_number.c_str())));

				for (;;) {
					asio::error_code ec;
					tcp::socket socket(io_service);
					acceptor.async_accept(socket, yield[ec]);
					if (!ec)
						std::make_shared<session>(std::move(socket))->go();
				}
			});
		
		// for sample purposes, we are using two threads. This can be increased based on some requirements change
		std::thread thread1{[&io_service](){ io_service.run(); }};
		std::thread thread2{[&io_service](){ io_service.run(); }};
		thread1.join();
		thread2.join();
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}
	
	return 0;
}
