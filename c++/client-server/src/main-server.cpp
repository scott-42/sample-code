//
//  main.cpp
//  server
//
//  Created by Scott Gustafson on 7/1/16.
//  Copyright © 2016 Garlic Software LLC. All rights reserved.
//

// Simple networking code is adapted from the asio sample code for the simple echo tcp server code.
// spawn/echo_server.cpp
// see https://github.com/boostorg/asio/blob/f2fbbd824c1fafa67c1b9c7ee6e4d2649b343a46/example/cpp11/spawn/echo_server.cpp

#include <iostream>
#include <sstream>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/detached.hpp>
#include <thread>
#include "config.h"
#include "prime.h"

using boost::asio::ip::tcp;

class session : public std::enable_shared_from_this<session> {
private:
	tcp::socket socket;
	boost::asio::steady_timer timer;
	boost::asio::strand<boost::asio::io_context::executor_type> strand;

public:
	explicit session(boost::asio::io_context& io_context, tcp::socket socket) : socket(std::move(socket)), timer(io_context), strand(io_context.get_executor()) {}
	
	void go() {
		auto self(shared_from_this());
		boost::asio::spawn(strand, [this, self](boost::asio::yield_context yield) {
			try {
				char data[128];
				for (;;) {
					timer.expires_from_now(std::chrono::seconds(10));
					std::size_t n = socket.async_read_some(boost::asio::buffer(data), yield);
					// this is not built to accept an int that is larger than the 32 bit value so this is safe to truncate
					if (n == 128) {
						n = 127;
					}
					data[n] = '\0';
					std::stringstream ss(data);
					unsigned int value = 0;
					ss >> value;
					boost::asio::async_write(socket, boost::asio::buffer(prime::is_prime(value) ? "1" : "0", 1), yield);
				}
			}
			catch (std::exception& e) {
				socket.close();
				timer.cancel();
			}
		}, boost::asio::detached);
		
		boost::asio::spawn(strand, [this, self](boost::asio::yield_context yield) {
			while (socket.is_open()) {
				boost::system::error_code ignored_ec;
				timer.async_wait(yield[ignored_ec]);
				if (timer.expiry() <= boost::asio::steady_timer::clock_type::now())
					socket.close();
			}
		}, boost::asio::detached);
	}
};

int main(int argc, char* argv[]) {
	try {
		boost::asio::io_context io_context;
		boost::asio::spawn(io_context, [&](boost::asio::yield_context yield) {
			tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), std::atoi(port_number.c_str())));

			for (;;) {
				boost::system::error_code ec;
				tcp::socket socket(io_context);
				acceptor.async_accept(socket, yield[ec]);
				if (!ec)
					std::make_shared<session>(io_context, std::move(socket))->go();
			}
		},
        [](std::exception_ptr e) {
        	if (e)
            	std::rethrow_exception(e);
        });
		
		// for sample purposes, we are using two threads. This can be increased based on some requirements change
		std::thread thread1{[&io_context](){ io_context.run(); }};
		std::thread thread2{[&io_context](){ io_context.run(); }};
		thread1.join();
		thread2.join();
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}
	
	return 0;
}
